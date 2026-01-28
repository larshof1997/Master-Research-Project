% Motor torque identification + publication-quality plots
% Integrated version: data loading, OLS model, and train/test plots

clear all; close all; clc;

%% ---------- Visual style defaults (LaTeX-friendly, larger fonts) ----------
set(groot, 'defaultTextInterpreter','latex');
set(groot, 'defaultAxesTickLabelInterpreter','latex');
set(groot, 'defaultLegendInterpreter','latex');

defaultFontSize   = 20;
defaultLineWidth  = 1.6;
defaultMarkerSize = 36;   % scatter SizeData

set(groot, 'defaultAxesFontSize', defaultFontSize);
set(groot, 'defaultLineLineWidth', defaultLineWidth);

%% Directory
data_dir = '/Users/lars/Documents/GitHub/Master-Research-Project/Quanser/motor_calibration_data/';

%% File lists (keep exact names)
mat_files = {
%     'simulink_01V_1Hz.mat',...
     'simulink_025V_1Hz.mat',...
     'simulink_05V_1Hz.mat',...
     'simulink_025V_2Hz.mat',...
     'simulink_05V_2Hz.mat'
};

csv_files = {
     'teensy_025V_1Hz.csv',...
     'teensy_05V_1Hz.csv',...
     'teensy_025V_2Hz.csv',...
     'teensy_05V_2Hz.csv',...
};

%% Hold out
test_freq = '2Hz';
train_idx = ~contains(mat_files, test_freq);
test_idx  = ~train_idx;

%% Torque calibration (ADC -> Nm)
a = 1.121303e-03;
b = -5.774345e-01;

train_I = [];  train_tau = [];  train_omega = []; train_omega_dot = [];
test_I  = [];  test_tau  = [];  test_omega  = []; test_omega_dot  = [];

%% Filter parameters (Savitzky–Golay)
F = 61;  % frame length (odd)
K = 2;   % polynomial order

for i = 1:length(mat_files)
    %% Load torque (Teensy)
    csv_data = dlmread(fullfile(data_dir, csv_files{i}), ',', 0, 0);
    adc = csv_data(:,2);
    tau = a * adc + b;

    dt = 0.01;
    N  = length(tau);

    %% Load current & position (Simulink)
    S     = load(fullfile(data_dir, mat_files{i}));
    vars  = fieldnames(S);
    data  = S.(vars{1});

    I_full = data(:,2);
    p_full = data(:,3);

    I = I_full(end-N:end-1);
    p = p_full(end-N:end-1);

    %% Filtering
    I_filt = sgolayfilt(I,   K, F);
    p_filt = sgolayfilt(p,   K, F);
    tau    = sgolayfilt(tau, K, F);

    %% Velocity and acceleration
    [~, g] = sgolay(K, F);
    omega      = conv(p_filt, factorial(1)/(-dt) * g(:,2), 'same');
    omega_dot  = conv(omega,  factorial(1)/(-dt) * g(:,2), 'same');

    %% Trim transients
    tau        = tau(300:end-100);
    I_filt     = I_filt(300:end-100);
    p_filt     = p_filt(300:end-100);
    omega      = omega(300:end-100);
    omega_dot  = omega_dot(300:end-100);

    %% Split train / test
    if train_idx(i)
        train_I         = [train_I;         I_filt];
        train_tau       = [train_tau;       tau];
        train_omega     = [train_omega;     omega];
        train_omega_dot = [train_omega_dot; omega_dot];
    else
        test_I          = [test_I;          I_filt];
        test_tau        = [test_tau;        tau];
        test_omega      = [test_omega;      omega];
        test_omega_dot  = [test_omega_dot;  omega_dot];
    end
end

%% ===================== OLS torque model =====================
Y = train_tau;
X = [train_omega_dot, ...   % inertia
     train_omega,     ...   % viscous friction
     train_I];              % torque constant

Theta_ols = (X' * X) \ (X' * Y);

J_est  = Theta_ols(1);
B_est  = Theta_ols(2);
Kt_est = Theta_ols(3);

fprintf('\n=== OLS torque model ===\n');
fprintf('J  = %.6e\n', J_est);
fprintf('B  = %.6e\n', B_est);
fprintf('Kt = %.6e\n', Kt_est);

%% ===================== Train/Test linear fit (for plots) =====================
% Simple static fit: tau = Kt * I + tau0 (used ONLY for visualization)
p_lin = polyfit(train_I, train_tau, 1);
Kt    = p_lin(1);
tau0  = p_lin(2);

pred_train = polyval(p_lin, train_I);
pred_test  = polyval(p_lin, test_I);

rmse_train = sqrt(mean((train_tau - pred_train).^2));
rmse_test  = sqrt(mean((test_tau  - pred_test ).^2));

mdl.RMSE = rmse_train; %#ok<STRNU>

%% ===================== Publication-style plots =====================
figure;
tiledlayout(1,2,'Padding','compact','TileSpacing','compact');

% ---- Training: scatter + fit line ----
nexttile; hold on;
s = scatter(train_I, train_tau, defaultMarkerSize, 'filled', ...
    'MarkerFaceAlpha', 0.45);

xfit = linspace(min(train_I), max(train_I), 200)';
yfit = Kt * xfit + tau0;
ph = plot(xfit, yfit, 'r-', 'LineWidth', 2.2);

xlabel('Current $I$ (A)');
ylabel('Torque $\\tau$ (Nm)');
title(sprintf('Train (1 Hz) -- RMSE = %.4f Nm', mdl.RMSE));

grid on; box on; axis tight;
legend([s ph], {'Data points', ...
    sprintf('$\\tau = %.6f I %+ .6f$', Kt, tau0)}, ...
    'Location','best','FontSize',defaultFontSize-2);

hold off;

% ---- Test: scatter + prediction ----
nexttile; hold on;
s2 = scatter(test_I, test_tau, defaultMarkerSize, 'filled', ...
    'MarkerFaceAlpha', 0.45);

[test_I_sorted, idx] = sort(test_I);
plot(test_I_sorted, pred_test(idx), 'r-', 'LineWidth', 2.2);

xlabel('Current $I$ (A)');
ylabel('Torque $\\tau$ (Nm)');
title(sprintf('Test (2 Hz) -- RMSE = %.4f Nm', rmse_test));

grid on; box on; axis tight;
legend('Test data','Prediction','Location','best', ...
    'FontSize',defaultFontSize-2);

hold off;

%% ===================== Dynamic model reconstruction =====================
% Training set
Y_hat_train = J_est*train_omega_dot + B_est*train_omega + Kt_est*train_I;

figure; hold on;
plot(train_tau);
plot(Y_hat_train);
legend('Measured torque','Reconstructed torque');
xlabel('Samples'); ylabel('Torque [Nm]'); grid on; box on;

mse_train_dyn = mean((train_tau - Y_hat_train).^2);
fprintf('MSE (Training, dynamic model): %.6f\n', mse_train_dyn);

% Test set
Y_hat_test = J_est*test_omega_dot + B_est*test_omega + Kt_est*test_I;

figure; hold on;
plot(test_tau);
plot(Y_hat_test);
legend('Measured torque','Reconstructed torque');
xlabel('Samples'); ylabel('Torque [Nm]'); grid on; box on;

mse_test_dyn = mean((test_tau - Y_hat_test).^2);
fprintf('MSE (Test, dynamic model): %.6f\n', mse_test_dyn);

%% ===================== Helper function =====================
function tau_smooth = kalman_filter_tau(tau, dt)
    N = length(tau);

    F = [1 dt; 0 1];
    H = [1 0];

    Q = [1e-7 0; 0 1e-7];
    R = 0.01;

    x = [tau(1); 0];
    P = eye(2);

    x_filt = zeros(2, N);
    P_filt = zeros(2, 2, N);

    for k = 1:N
        % Predict
        x_pred = F * x;
        P_pred = F * P * F' + Q;

        % Update
        Kk = P_pred * H' / (H * P_pred * H' + R);
        x  = x_pred + Kk * (tau(k) - H * x_pred);
        P  = (eye(2) - Kk * H) * P_pred;

        x_filt(:,k)   = x;
        P_filt(:,:,k)= P;
    end

    tau_smooth = x_filt(1,:)';
end
