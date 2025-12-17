clc; clear all

%% Load motor data
load('motor1VoltageData_1hz')

% Unpack data
time = motorData.time;
voltage = motorData.voltage;
current = motorData.current;
velocity = motorData.velocity;

%% Estimate derivative of current
% Sampling period [s]
% Given: time, voltage, current, velocity, Ts
Ts = time(2) - time(1);
N = numel(time);

% State: x = [ i; idot; v; vdot ]
A = [1, Ts, 0,  0;    % i_{k+1} = i_k + Ts*idot_k
     0,  1, 0,  0;    % idot random-walk (can add input in B)
     0,  0, 1, Ts;    % v_{k+1} = v_k + Ts*vdot_k
     0,  0, 0,  1];   % vdot random-walk
% Input matrix (optionally let voltage affect idot)
b_i = 0;   % try 0 or a small value or 1/L if you know L
B = [0; b_i; 0; 0];

% Measurement matrix (we measure current and velocity)
C = [1, 0, 0, 0;    % measure i
     0, 0, 1, 0];   % measure v

% Initial state estimate (use first sample + finite differences)
idot0 = (current(2)-current(1))/Ts;
vdot0 = (velocity(2)-velocity(1))/Ts;
x0 = [ current(1); idot0; velocity(1); vdot0 ];

% Initial covariance P0 (heuristic)
P0 = diag([ (std(current)*0.1)^2, (std(diff(current))/Ts*0.5)^2, ...
            (std(velocity)*0.1)^2, (std(diff(velocity))/Ts*0.5)^2 ]);

% Measurement noise covariance R (2x2)
% rough empirical estimates (replace with sensor specs if available)
meas_i_var = var(current - movmean(current,5));
meas_v_var = var(velocity - movmean(velocity,5));
if ~isfinite(meas_i_var) || meas_i_var==0, meas_i_var = 1e-6; end
if ~isfinite(meas_v_var) || meas_v_var==0, meas_v_var = 1e-6; end
R = diag([meas_i_var, meas_v_var]);

% Process noise covariance Q (4x4) - tune these
q_i = 1e-8;                    % small noise on integrated current state
q_idot = (std(diff(current))/Ts)^2 * 1e-2;  % noise on derivative of current
q_v = 1e-8;                    % small noise on integrated velocity
q_vdot = (std(diff(velocity))/Ts)^2 * 1e-2; % noise on velocity derivative
% safety defaults
if ~isfinite(q_idot) || q_idot==0, q_idot = 1e-6; end
if ~isfinite(q_vdot) || q_vdot==0, q_vdot = 1e-6; end
Q = diag([q_i, q_idot, q_v, q_vdot]);

% Q = diag([0.0002    0.0087    0.0013    0.0100]);
% R = diag([0.0043    0.0100]);

% Preallocate
x_pred = zeros(4, N);
P_pred = zeros(4,4,N);
x_filt = zeros(4, N);
P_filt = zeros(4,4,N);

% initialize
x_filt(:,1) = x0;
P_filt(:,:,1) = P0;

% Kalman filter forward pass (vector measurements)
for k = 1:N-1
    % predict
    x_pred(:,k+1) = A * x_filt(:,k) + B * voltage(k);
    P_pred(:,:,k+1) = A * P_filt(:,:,k) * A' + Q;
    
    % update using measurement y = [current; velocity] at k+1
    y = [ current(k+1); velocity(k+1) ];
    S = C * P_pred(:,:,k+1) * C' + R;
    K = (P_pred(:,:,k+1) * C') / S;
    x_filt(:,k+1) = x_pred(:,k+1) + K * (y - C * x_pred(:,k+1));
    P_filt(:,:,k+1) = (eye(4) - K * C) * P_pred(:,:,k+1);
end

% Rauch-Tung-Striebel smoother (backward)
x_smooth = zeros(4, N);
P_smooth = zeros(4,4,N);
x_smooth(:,N) = x_filt(:,N);
P_smooth(:,:,N) = P_filt(:,:,N);

for k = N-1:-1:1
    % smoother gain
    % protect from singular P_pred by small regularization if needed
    % J = P_filt(:,:,k) * A' / P_pred(:,:,k+1);
    J = P_filt(:,:,k) * A' * pinv(P_pred(:,:,k+1));  % safer numerically
    x_smooth(:,k) = x_filt(:,k) + J * (x_smooth(:,k+1) - x_pred(:,k+1));
    P_smooth(:,:,k) = P_filt(:,:,k) + J * (P_smooth(:,:,k+1) - P_pred(:,:,k+1)) * J';
end

% Extract smoothed signals
i_smooth   = x_smooth(1, :)';
idot_smooth= x_smooth(2, :)';
v_smooth   = x_smooth(3, :)';
vdot_smooth= x_smooth(4, :)';

% Plot results
figure('Name','Current & Velocity smoothing','NumberTitle','off','Units','normalized','Position',[.05 .05 .9 .7]);

subplot(3,1,1);
plot(time, current, '.-','DisplayName','measured i'); hold on;
plot(time, i_smooth, '-','LineWidth',1.5,'DisplayName','smoothed i');
xlabel('time [s]'); ylabel('Current [A]'); legend; grid on;
title('Current: measured vs smoothed');

subplot(3,1,2);
plot(time, idot_smooth, '-','LineWidth',1.5,'DisplayName','smoothed di/dt (Kalman+RTS)');
xlabel('time [s]'); ylabel('di/dt [A/s]'); legend; grid on;
title('Current derivative');

subplot(3,1,3);
plot(time, velocity, '.-','DisplayName','measured v'); hold on;
plot(time, v_smooth, '-','LineWidth',1.5,'DisplayName','smoothed v');
xlabel('time [s]'); ylabel('Velocity'); legend; grid on;
title('Velocity: measured vs smoothed');

%% Define matrices as required for least squares solution
% Output data
Y = voltage;

% Input data
X = [idot_smooth, i_smooth, v_smooth];

% Evaluate estimate
Theta_opt = inv(X'*X)*X'*Y;

%% Compute and plot the estimated outputs
% This is the reconstructed voltage
Y_hat = Theta_opt(1)*idot_smooth + Theta_opt(2)*i_smooth + Theta_opt(3)*v_smooth;

% Plot the original supplied voltage and reconstructed voltage
figure;
plot(time, voltage, time, Y_hat)
legend('Supplied voltage', 'Reconstructed voltage')
xlabel('Time [s]')
ylabel('Voltage [V]')

% ---- Compute MSE for training dataset ----
mse_train = mean((voltage - Y_hat).^2);
fprintf('MSE (Training dataset, 1 Hz): %.6f\n', mse_train);

%% Load second dataset for validation
load('motor1VoltageData_2hz')

% Unpack data
time = motorData.time;
voltage = motorData.voltage;
current = motorData.current;
velocity = motorData.velocity;

%% Estimate derivative of current
% Sampling period [s]
% Given: time, voltage, current, velocity, Ts
Ts = time(2) - time(1);
N = numel(time);

% State: x = [ i; idot; v; vdot ]
A = [1, Ts, 0,  0;    % i_{k+1} = i_k + Ts*idot_k
     0,  1, 0,  0;    % idot random-walk (can add input in B)
     0,  0, 1, Ts;    % v_{k+1} = v_k + Ts*vdot_k
     0,  0, 0,  1];   % vdot random-walk
% Input matrix (optionally let voltage affect idot)
b_i = 0;   % try 0 or a small value or 1/L if you know L
B = [0; b_i; 0; 0];

% Measurement matrix (we measure current and velocity)
C = [1, 0, 0, 0;    % measure i
     0, 0, 1, 0];   % measure v

% Initial state estimate (use first sample + finite differences)
idot0 = (current(2)-current(1))/Ts;
vdot0 = (velocity(2)-velocity(1))/Ts;
x0 = [ current(1); idot0; velocity(1); vdot0 ];

% Initial covariance P0 (heuristic)
P0 = diag([ (std(current)*0.1)^2, (std(diff(current))/Ts*0.5)^2, ...
            (std(velocity)*0.1)^2, (std(diff(velocity))/Ts*0.5)^2 ]);

% Measurement noise covariance R (2x2)
% rough empirical estimates (replace with sensor specs if available)
meas_i_var = var(current - movmean(current,5));
meas_v_var = var(velocity - movmean(velocity,5));
if ~isfinite(meas_i_var) || meas_i_var==0, meas_i_var = 1e-6; end
if ~isfinite(meas_v_var) || meas_v_var==0, meas_v_var = 1e-6; end
R = diag([meas_i_var, meas_v_var]);

% Process noise covariance Q (4x4) - tune these
q_i = 1e-8;                    % small noise on integrated current state
q_idot = (std(diff(current))/Ts)^2 * 1e-2;  % noise on derivative of current
q_v = 1e-8;                    % small noise on integrated velocity
q_vdot = (std(diff(velocity))/Ts)^2 * 1e-2; % noise on velocity derivative
% safety defaults
if ~isfinite(q_idot) || q_idot==0, q_idot = 1e-6; end
if ~isfinite(q_vdot) || q_vdot==0, q_vdot = 1e-6; end
Q = diag([q_i, q_idot, q_v, q_vdot]);

% Preallocate
x_pred = zeros(4, N);
P_pred = zeros(4,4,N);
x_filt = zeros(4, N);
P_filt = zeros(4,4,N);

% initialize
x_filt(:,1) = x0;
P_filt(:,:,1) = P0;

% Kalman filter forward pass (vector measurements)
for k = 1:N-1
    % predict
    x_pred(:,k+1) = A * x_filt(:,k) + B * voltage(k);
    P_pred(:,:,k+1) = A * P_filt(:,:,k) * A' + Q;
    
    % update using measurement y = [current; velocity] at k+1
    y = [ current(k+1); velocity(k+1) ];
    S = C * P_pred(:,:,k+1) * C' + R;
    K = (P_pred(:,:,k+1) * C') / S;
    x_filt(:,k+1) = x_pred(:,k+1) + K * (y - C * x_pred(:,k+1));
    P_filt(:,:,k+1) = (eye(4) - K * C) * P_pred(:,:,k+1);
end

% Rauch-Tung-Striebel smoother (backward)
x_smooth = zeros(4, N);
P_smooth = zeros(4,4,N);
x_smooth(:,N) = x_filt(:,N);
P_smooth(:,:,N) = P_filt(:,:,N);

for k = N-1:-1:1
    % smoother gain
    % protect from singular P_pred by small regularization if needed
    % J = P_filt(:,:,k) * A' / P_pred(:,:,k+1);
    J = P_filt(:,:,k) * A' * pinv(P_pred(:,:,k+1));  % safer numerically
    x_smooth(:,k) = x_filt(:,k) + J * (x_smooth(:,k+1) - x_pred(:,k+1));
    P_smooth(:,:,k) = P_filt(:,:,k) + J * (P_smooth(:,:,k+1) - P_pred(:,:,k+1)) * J';
end

% Extract smoothed signals
i_smooth   = x_smooth(1, :)';
idot_smooth= x_smooth(2, :)';
v_smooth   = x_smooth(3, :)';
vdot_smooth= x_smooth(4, :)';

% Plot results
figure('Name','Current & Velocity smoothing','NumberTitle','off','Units','normalized','Position',[.05 .05 .9 .7]);

subplot(3,1,1);
plot(time, current, '.-','DisplayName','measured i'); hold on;
plot(time, i_smooth, '-','LineWidth',1.5,'DisplayName','smoothed i');
xlabel('time [s]'); ylabel('Current [A]'); legend; grid on;
title('Current: measured vs smoothed');

subplot(3,1,2);
plot(time, idot_smooth, '-','LineWidth',1.5,'DisplayName','smoothed di/dt (Kalman+RTS)');
xlabel('time [s]'); ylabel('di/dt [A/s]'); legend; grid on;
title('Current derivative');

subplot(3,1,3);
plot(time, velocity, '.-','DisplayName','measured v'); hold on;
plot(time, v_smooth, '-','LineWidth',1.5,'DisplayName','smoothed v');
xlabel('time [s]'); ylabel('Velocity'); legend; grid on;
title('Velocity: measured vs smoothed');

%% Define matrices as required for least squares solution
% Output data
Y = voltage;

% Input data
X = [idot_smooth, i_smooth, v_smooth];

% Evaluate estimate
Theta_opt = inv(X'*X)*X'*Y;

%% Compute and plot the estimated outputs
% This is the reconstructed voltage
Y_hat = Theta_opt(1)*idot_smooth + Theta_opt(2)*i_smooth + Theta_opt(3)*v_smooth;

% Plot the original supplied voltage and reconstructed voltage
figure;
plot(time, voltage, time, Y_hat)
legend('Supplied voltage', 'Reconstructed voltage')
xlabel('Time [s]')
ylabel('Voltage [V]')

% ---- Compute MSE for training dataset ----
mse_val = mean((voltage - Y_hat).^2);
fprintf('MSE (Validation dataset, 2 Hz): %.6f\n', mse_val);
