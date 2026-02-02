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

% Directory
% data_dir = 'C:\Users\S4236610\Documents\GitHub\Master-Research-Project\Quanser\motor_calibration_data_elbow/'; 
data_dir = 'C:\Users\S4236610\Documents\GitHub\Master-Research-Project\Quanser\motor_calibration_data_shoulder\';

%% File lists (keep exact names)
% mat_files = {
%      'simulink_1Hz_ramp_M2.mat',...
%      'simulink_2Hz_ramp_M2.mat',...
% };
% 
% csv_files = {
%      'teensy_1Hz_ramp_M2.csv',...
%      'teensy_2Hz_ramp_M2.csv',...
% };

mat_files = {
     'simulink_1Hz_ramp_M1.mat',...
     'simulink_2Hz_ramp_M1.mat',...
};

csv_files = {
     'teensy_1Hz_ramp_M1.csv',...
     'teensy_2Hz_ramp_M1.csv',...
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

% Filter parameters
F = 131;
K = 2;

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
    if contains(data_dir, 'elbow')
        p_full =  data(:,4);
    else
        p_full =  data(:,3);
    end
    I = I_full(end-N:end-1);
    p = p_full(end-N:end-1);
    
%   Signal alignment using cross-correlation
    maxLag = 100;

    [c, lags] = xcorr(I - mean(I), tau - mean(tau), maxLag, 'normalized');
    [~, idx] = max(c);
    lag = lags(idx);

    % If lag > 0: I leads tau  -> shift I backward
    % If lag < 0: tau lags I   -> shift tau backward
    if lag > 0
        tau   = tau(1:end+lag);
        I = I(-lag+1:end);
    elseif lag < 0
        I   = I(1:end+lag);
        p   = p(1:end+lag);
        tau = tau(-lag+1:end);
    end
    
    % Compute filtered current and position
    I_filt = sgolayfilt(I, K, F);
    p_filt = sgolayfilt(p, K, F);
    tau = sgolayfilt(tau, K, F);
    
    % Compute filtered derivative of current
    [~, g] = sgolay(K, F);  
    
    d = flipud(g(:,2)) / dt;

    omega     = conv(p_filt, d, 'same');
    omega_dot = conv(omega, d, 'same');
    
    omega     = -omega;
    omega_dot = -omega_dot;
    I_filt = I_filt;
    tau = tau;
    
%     figure
%     hold on
%     plot(tau)
% %     plot(omega_dot)
% %     plot(tau)
%     plot(p)

    % Ensure equal length (safety)
    N = length(I_filt);
    
    tau = tau(300:end-100);
    I_filt = I_filt(300:end-100);
    p_filt = p_filt(300:end-100);
    p = p(300:end-100);
    omega = omega(300:end-100);
    omega_dot = omega_dot(300:end-100); 
    
    
    N = length(I_filt);

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

% Regressor matrix
X = [-train_omega_dot, ...        % inertia term
    -train_omega, ...   % viscous friction
    train_I];           % torque constant

Theta_ols = inv(X' * X)*X'*Y;

J_est  = Theta_ols(1);
B_est  = Theta_ols(2);
Kt_est = Theta_ols(3);

fprintf('\n=== OLS torque model ===\n');
fprintf('J  = %.6e\n', J_est);
fprintf('B  = %.6e\n', B_est);
fprintf('Kt = %.6e\n', Kt_est);

res0 = (Y - X*Theta_ols).^2;
var_est = movmean(res0, round(0.05*length(Y))); % e.g. 5% window
var_est = max(var_est, 1e-5);
W = diag(1./var_est);
Theta_wls = (X'*W*X) \ (X'*W*Y);

J_est    = Theta_wls(1);
B_est    = Theta_wls(2);
Kt_est   = Theta_wls(3);

%% ===================== Dynamic model reconstruction =====================
% Training set
Y_hat_train = -J_est*train_omega_dot + -B_est*train_omega + Kt_est*train_I;

% figure; hold on;
% plot(train_tau);
% plot(Y_hat_train);
% legend('Measured torque','Reconstructed torque');
% xlabel('Samples'); ylabel('Torque [Nm]'); grid on; box on;

mse_train_dyn = mean((train_tau - Y_hat_train).^2);
fprintf('MSE (Training, dynamic model): %.6f\n', mse_train_dyn);

% Test set
Y_hat_test = -J_est*test_omega_dot + -B_est*test_omega + Kt_est*test_I;

% figure; hold on;
% plot(test_tau);
% plot(Y_hat_test);
% legend('Measured torque','Reconstructed torque');
% xlabel('Samples'); ylabel('Torque [Nm]'); grid on; box on;

mse_test_dyn = mean((test_tau - Y_hat_test).^2);
fprintf('MSE (Test, dynamic model): %.6f\n', mse_test_dyn);

%% ===================== Dynamic model reconstruction =====================
% Publication-style comparison plots (train vs test)


figure;
tiledlayout(2,1,'Padding','compact','TileSpacing','compact');


% ---- Training set ----
nexttile; hold on;
plot(train_tau, 'LineWidth', 1.6);
plot(Y_hat_train, '--', 'LineWidth', 2.0);


grid on; box on; axis tight;
xlabel('Samples');
ylabel('Torque $\tau$ (Nm)');
title(sprintf('Training set (1 Hz) -- MSE = %.3e', mse_train_dyn));
legend({'Measured torque','Reconstructed torque'}, ...
'Location','southeast','FontSize',defaultFontSize-2);


hold off;


% ---- Test set ----
nexttile; hold on;
plot(test_tau, 'LineWidth', 1.6);
plot(Y_hat_test, '--', 'LineWidth', 2.0);


grid on; box on; axis tight;
xlabel('Samples');
ylabel('Torque $\tau$ (Nm)');
title(sprintf('Test set (2 Hz) -- MSE = %.3e', mse_test_dyn));
legend({'Measured torque','Reconstructed torque'}, ...
'Location','southeast','FontSize',defaultFontSize-2);


hold off;

% ---- Save high quality ----
set(gcf, 'Units', 'inches', 'Position', [1, 1, 10, 6]);  % Set figure size
exportgraphics(gcf, 'torque_reconstruction_M1.png', 'Resolution', 300);


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
