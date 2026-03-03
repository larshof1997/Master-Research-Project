% Motor torque identification – two-stage approach
% Stage 1: Kt from stall experiment (qdot ≈ 0)
% Stage 2: J, B, Fc from dynamic experiments with Kt fixed

clear all; close all; clc;

%% ---------- Visual style defaults (LaTeX-friendly, larger fonts) ----------
set(groot, 'defaultTextInterpreter','latex');
set(groot, 'defaultAxesTickLabelInterpreter','latex');
set(groot, 'defaultLegendInterpreter','latex');

defaultFontSize   = 20;
defaultLineWidth  = 1.6;
defaultMarkerSize = 36;

set(groot, 'defaultAxesFontSize', defaultFontSize);
set(groot, 'defaultLineLineWidth', defaultLineWidth);

% Directory
data_dir = 'C:\Users\S4236610\Documents\GitHub\Master-Research-Project\Quanser\motor_calibration_data_elbow/';

%% ===================== STAGE 1: Kt from stall tests =====================
stall_mat_files = {
    'simulink_1Hz_ramp_stall_M2.mat',...
    'simulink_2Hz_ramp_stall_M2.mat',...
};

stall_csv_files = {
    'teensy_1Hz_ramp_stall_M2.csv',...
    'teensy_2Hz_ramp_stall_M2.csv',...
};

% Hold out 2Hz stall for test
stall_test_freq  = '2Hz';
stall_train_idx  = ~contains(stall_mat_files, stall_test_freq);
stall_test_idx   = ~stall_train_idx;

% Torque calibration (ADC -> Nm)
a = 1.121303e-03;
b = -5.774345e-01;

% Filter parameters
F = 131;
K = 2;
dt = 0.01;

% Current threshold for valid Kt samples
I_thresh = 0.05;

train_I_stall   = [];  train_tau_stall   = [];
test_I_stall    = [];  test_tau_stall    = [];

for i = 1:length(stall_mat_files)
    % Load torque (Teensy)
    csv_data = dlmread(fullfile(data_dir, stall_csv_files{i}), ',', 0, 0);
    adc = csv_data(:,2);
    tau = a * adc + b;
    N = length(tau);

    % Load current (Simulink)
    S = load(fullfile(data_dir, stall_mat_files{i}));
    vars = fieldnames(S);
    data = S.(vars{1});

    I_full = data(:,2);
    I = I_full(end-N:end-1);

    % Align via cross-correlation
    maxLag = 100;
    [c, lags] = xcorr(I - mean(I), tau - mean(tau), maxLag, 'normalized');
    [~, idx] = max(c);
    lag = lags(idx);

    if lag > 0
        tau = tau(1:end+lag);
        I   = I(-lag+1:end);
    elseif lag < 0
        I   = I(1:end+lag);
        tau = tau(-lag+1:end);
    end

    % Filter
    I   = sgolayfilt(I, K, F);
    tau = sgolayfilt(tau, K, F);

    % Trim edges
    I   = I(300:end-100);
    tau = tau(300:end-100);

    % Split
    if stall_train_idx(i)
        train_I_stall   = [train_I_stall;   I];
        train_tau_stall = [train_tau_stall;  tau];
    else
        test_I_stall    = [test_I_stall;     I];
        test_tau_stall  = [test_tau_stall;   tau];
    end
end

% Kt from training stall data
valid  = abs(train_I_stall) > I_thresh;
Kt_est = mean(train_tau_stall(valid) ./ train_I_stall(valid));

fprintf('\n=== Stage 1: Stall test ===\n');
fprintf('Kt = %.6e  (from 1 Hz stall)\n', Kt_est);

% Train fit
mse_stall_train = mean((train_tau_stall - Kt_est * train_I_stall).^2);
fprintf('MSE (Stall train): %.6e\n', mse_stall_train);

% Test fit
mse_stall_test = mean((test_tau_stall - Kt_est * test_I_stall).^2);
fprintf('MSE (Stall test):  %.6e\n', mse_stall_test);

% Stall plots
figure;
tiledlayout(2,1,'Padding','compact','TileSpacing','compact');

nexttile; hold on;
plot(train_tau_stall, 'LineWidth', 1.6);
plot(Kt_est * train_I_stall, '--', 'LineWidth', 2.0);
grid on; box on; axis tight;
xlabel('Samples'); ylabel('Torque $\tau$ (Nm)');
title(sprintf('Stall train (1 Hz) -- MSE = %.3e', mse_stall_train));
legend({'Measured','$K_t \cdot I$'}, 'Location','best');

nexttile; hold on;
plot(test_tau_stall, 'LineWidth', 1.6);
plot(Kt_est * test_I_stall, '--', 'LineWidth', 2.0);
grid on; box on; axis tight;
xlabel('Samples'); ylabel('Torque $\tau$ (Nm)');
title(sprintf('Stall test (2 Hz) -- MSE = %.3e', mse_stall_test));
legend({'Measured','$K_t \cdot I$'}, 'Location','best');

set(gcf, 'Units','inches', 'Position',[1 1 10 6]);
exportgraphics(gcf, 'stall_test_M2.png', 'Resolution', 300);

%% ===================== STAGE 2: J, B, Fc from dynamic data =====================
mat_files = {
    'simulink_1Hz_ramp_M2.mat',...
    'simulink_2Hz_ramp_M2.mat',...
};

csv_files = {
    'teensy_1Hz_ramp_M2.csv',...
    'teensy_2Hz_ramp_M2.csv',...
};

% Hold out
test_freq = '2Hz';
train_idx = ~contains(mat_files, test_freq);
test_idx  = ~train_idx;

train_I = []; train_tau = []; train_omega = []; train_omega_dot = [];
test_I  = []; test_tau  = []; test_omega  = []; test_omega_dot  = [];

for i = 1:length(mat_files)
    % Load torque (Teensy)
    csv_data = dlmread(fullfile(data_dir, csv_files{i}), ',', 0, 0);
    adc = csv_data(:,2);
    tau = a * adc + b;
    N = length(tau);

    % Load current & position (Simulink)
    S = load(fullfile(data_dir, mat_files{i}));
    vars = fieldnames(S);
    data = S.(vars{1});

    I_full = data(:,2);
    if contains(data_dir, 'elbow')
        p_full = data(:,4);
    else
        p_full = data(:,3);
    end
    I = I_full(end-N:end-1);
    p = p_full(end-N:end-1);

    % Signal alignment
    maxLag = 100;
    [c, lags] = xcorr(I - mean(I), tau - mean(tau), maxLag, 'normalized');
    [~, idx] = max(c);
    lag = lags(idx);

    if lag > 0
        tau = tau(1:end+lag);
        I   = I(-lag+1:end);
        p   = p(-lag+1:end);
    elseif lag < 0
        I   = I(1:end+lag);
        p   = p(1:end+lag);
        tau = tau(-lag+1:end);
    end

    % Filter
    I_filt = sgolayfilt(I, K, F);
    p_filt = sgolayfilt(p, K, F);
    tau    = sgolayfilt(tau, K, F);

    % Derivatives via SG filter
    [~, g] = sgolay(K, F);
    d = flipud(g(:,2)) / dt;

    omega     = conv(p_filt, d, 'same');
    omega_dot =  conv(omega,  d, 'same');

    % Trim edges
    tau       = tau(300:end-100);
    I_filt    = I_filt(300:end-100);
    omega     = -omega(300:end-100);
    omega_dot = omega_dot(300:end-100);

    % Split
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

%% OLS for J, B, Fc with Kt fixed
Y_dyn = train_tau - Kt_est * train_I;

X_dyn = [-train_omega_dot, ...      % J
         -train_omega];              % B (viscous)

Theta_dyn = (X_dyn' * X_dyn) \ (X_dyn' * Y_dyn);

J_est  = Theta_dyn(1);
B_est  = Theta_dyn(2);


fprintf('\n=== Stage 2: Dynamic model (Kt fixed) ===\n');
fprintf('J  = %.6e\n', J_est);
fprintf('B  = %.6e\n', B_est);
fprintf('Kt = %.6e  (from stall test)\n', Kt_est);

%% ===================== Reconstruction & plots =====================
Y_hat_train = -J_est*train_omega_dot - B_est*train_omega + Kt_est*train_I;

Y_hat_test  = -J_est*test_omega_dot - B_est*test_omega + Kt_est*test_I;

mse_train = mean((train_tau - Y_hat_train).^2);
mse_test  = mean((test_tau  - Y_hat_test ).^2);

fprintf('\nMSE (Train): %.6e\n', mse_train);
fprintf('MSE (Test):  %.6e\n', mse_test);

figure;
tiledlayout(2,1,'Padding','compact','TileSpacing','compact');

% Training
nexttile; hold on;
plot(train_tau, 'LineWidth', 1.6);
plot(Y_hat_train, '--', 'LineWidth', 2.0);
grid on; box on; axis tight;
xlabel('Samples'); ylabel('Torque $\tau$ (Nm)');
title(sprintf('Training set (1 Hz) -- MSE = %.3e', mse_train));
legend({'Measured','Reconstructed'}, 'Location','southeast', ...
       'FontSize', defaultFontSize-2);

% Test
nexttile; hold on;
plot(test_tau, 'LineWidth', 1.6);
plot(Y_hat_test, '--', 'LineWidth', 2.0);
grid on; box on; axis tight;
xlabel('Samples'); ylabel('Torque $\tau$ (Nm)');
title(sprintf('Test set (2 Hz) -- MSE = %.3e', mse_test));
legend({'Measured','Reconstructed'}, 'Location','southeast', ...
       'FontSize', defaultFontSize-2);

set(gcf, 'Units','inches', 'Position',[1 1 10 6]);
exportgraphics(gcf, 'torque_reconstruction_M2.png', 'Resolution', 300);