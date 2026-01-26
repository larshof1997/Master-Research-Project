clear all; close all; clc;

% Directory
data_dir = 'C:\Users\S4236610\Documents\GitHub\Master-Research-Project\Quanser\motor_calibration_data\';

% File lists (keep exact names)
mat_files = {
%       'simulink_01V_1Hz.mat',...
     'simulink_025V_1Hz.mat',...
     'simulink_05V_1Hz.mat',...
     'simulink_025V_2Hz.mat',...
     'simulink_05V_2Hz.mat'
};
% 
csv_files = {
     'teensy_025V_1Hz.csv',...
     'teensy_05V_1Hz.csv',...
     'teensy_025V_2Hz.csv',...
     'teensy_05V_2Hz.csv',...
% %      'teensy_V03_f05_stall.csv'
};

% Hold out
test_freq = '2Hz';
train_idx = ~contains(mat_files, test_freq);
test_idx  = ~train_idx;

% Torque calibration
a = 1.121303e-03;
b = -5.774345e-01;

train_I = [];  train_tau = [];  train_omega = []; train_omega_dot = []; 
test_I  = [];  test_tau  = [];  test_omega = []; test_omega_dot = []; 

% Filter parameters
F = 61;
K = 2;

for i = 1:length(mat_files)
    % Load torque (teensy)
    csv_data = dlmread(fullfile(data_dir, csv_files{i}), ',', 0, 0);  % change to 1,0 if header
    adc = csv_data(:,2);
    tau = a * adc + b;
  
    dt = 0.01;
    N = length(tau);
    
    % Load current (simulink)
    S = load(fullfile(data_dir, mat_files{i}));
    vars = fieldnames(S);
    data = S.(vars{1});
    I_full = data(:,2);
    p_full =  data(:,3);
    I = I_full(end-N:end-1);
    p = p_full(end-N:end-1);
    
    % Compute filtered current and position
    I_filt = sgolayfilt(I, K, F);
    p_filt = sgolayfilt(p, K, F);
    tau = sgolayfilt(tau, K, F);
    
    % Compute filtered derivative of current
    [~, g] = sgolay(K, F);  
    omega = conv(p_filt, factorial(1)/(-dt) * g(:,2), 'same');
    omega_dot = conv(omega, factorial(1)/(-dt) * g(:,2), 'same');
    
%     % Signal alignment using cross-correlation
%     maxLag = 500;
% 
%     [c, lags] = xcorr(I - mean(I), tau - mean(tau), maxLag, 'normalized');
%     [~, idx] = max(c);
%     lag = lags(idx);
% 
%     % If lag > 0: I leads tau  -> shift I backward
%     % If lag < 0: tau lags I   -> shift tau backward
%     if lag > 0
%         tau   = tau(1:end+lag);
%         I = I(-lag+1:end);
%     elseif lag < 0
%         I   = I(1:end+lag);
%         tau = tau(-lag+1:end);
%     end

    % Ensure equal length (safety)
    N = length(I_filt);
    
    tau = tau(300:end-100);
    I_filt = I_filt(300:end-100);
    p_filt = p_filt(300:end-100);
    p = p(300:end-100);
    omega = omega(300:end-100);
    omega_dot = omega_dot(300:end-100);
    
    N = length(I_filt);
%     
%     figure;
%     hold on
%     plot(I_filt)
%     plot(tau)
%     hold off
%     
%     figure;
%     hold on
%     plot(p)
%     plot(p_filt)
%     hold off
%     
%     
%     
%     figure;
%     hold on
%     plot(p_filt)
%     plot(omega)
%     plot(omega_dot)
%     hold off
    
    if train_idx(i)
        train_I   = [train_I;   I_filt];
        train_tau = [train_tau; tau];
        train_omega = [train_omega; omega];
        train_omega_dot = [train_omega_dot; omega_dot];

    else
        test_I    = [test_I;    I_filt];
        test_tau  = [test_tau;  tau];
        test_omega = [test_omega; omega];
        test_omega_dot = [test_omega_dot; omega_dot];
    end
end

% Output
Y = train_tau;

% Regressor matrix
X = [train_omega_dot, ...        % inertia term
    train_omega, ...   % viscous friction
    train_I];           % torque constant

Theta_ols = (X' * X) \ (X' * Y);

J_est    = Theta_ols(1);
B_est    = Theta_ols(2);
Kt_est   = Theta_ols(3);

fprintf('\n=== OLS torque model ===\n');
fprintf('J     = %.6e\n', J_est);
fprintf('B     = %.6e\n', B_est);
fprintf('Kt    = %.6e\n', Kt_est);

res0 = (Y - X*Theta_ols).^2;
var_est = movmean(res0, round(0.05*length(Y))); % e.g. 5% window
var_est = max(var_est, 1e-7);
W = diag(1./var_est);
Theta_wls = (X'*W*X) \ (X'*W*Y);

% J_est    = Theta_wls(1);
% B_est    = Theta_wls(2);
% Kt_est   = Theta_wls(3);

%% Compute and plot the estimated outputs
% This is the reconstructed torque
Y_hat = J_est*train_omega_dot + B_est * train_omega + Kt_est*train_I;

% Plot the original supplied voltage and reconstructed voltage
figure;
hold on;
plot(train_tau)
plot(Y_hat)
hold off;
legend('Measured torque', 'Reconstructed torque')
xlabel('Time [s]')
ylabel('Torque [Nm]')

% ---- Compute MSE for training dataset ----
mse_train = mean((train_tau - Y_hat).^2);
fprintf('MSE (Training dataset, 1 Hz): %.6f\n', mse_train);

%% Compute and plot the estimated outputs on test set
% This is the reconstructed torque
Y_hat = J_est*test_omega_dot + B_est * test_omega + Kt_est*test_I;

% Plot the original supplied voltage and reconstructed voltage
figure;
hold on;
plot(test_tau)
plot(Y_hat)
hold off;
legend('Measured torque', 'Reconstructed torque')
xlabel('Time [s]')
ylabel('Torque [Nm]')

% ---- Compute MSE for training dataset ----
mse_train = mean((test_tau - Y_hat).^2);
fprintf('MSE (Test dataset, 1 Hz): %.6f\n', mse_train);


function tau_smooth = kalman_filter_tau(tau, dt)

    N = length(tau);

    % State matrices
    F = [1 dt; 
         0  1];
    H = [1 0];

    % ---- TUNING PARAMETERS ----
    Q = [1e-7 0;
         0    1e-7];   % process noise (smoothness)
    R = 0.01;          % measurement noise
    % ---------------------------

     % Allocate storage
    x_filt = zeros(2, N);
    P_filt = zeros(2, 2, N);
    x_pred = zeros(2, N);
    P_pred = zeros(2, 2, N);

    % Initial conditions
    x = [tau(1); 0];
    P = eye(2);

    % Forward Kalman filter
    for k = 1:N
        % Prediction
        x_pred(:,k) = F * x;
        P_pred(:,:,k) = F * P * F' + Q;

        % Update
        K = P_pred(:,:,k) * H' / (H * P_pred(:,:,k) * H' + R);
        x = x_pred(:,k) + K * (tau(k) - H * x_pred(:,k));
        P = (eye(2) - K * H) * P_pred(:,:,k);

        % Store
        x_filt(:,k) = x;
        P_filt(:,:,k) = P;
    end

    % RTS backward smoothing
    x_smooth = x_filt;
    P_smooth = P_filt;

 
    % Output: smoothed torque
    tau_smooth = x_smooth(1,:)';
end