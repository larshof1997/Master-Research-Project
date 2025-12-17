%% Load motor data
load('motor1VoltageData_1hz')

% Unpack data
time = motorData.time;
voltage = motorData.voltage;
current = motorData.current;
velocity = motorData.velocity;

%% Estimate derivative of current
% Sampling period [s]
Ts = time(2) - time(1);

% Filter parameters
F = 25;
K = 3;

% Compute filtered current and velocity
current_filtered = sgolayfilt(current, K, F);
velocity_filtered = sgolayfilt(velocity, K, F);

% Compute filtered derivative of current
[b, g] = sgolay(K, F);
dIdt_filtered = conv(current_filtered, factorial(1)/(-Ts) * g(:,2), 'same');

% Plot results

figure(1)
subplot(4,1,1)
plot(time, voltage)
plot(time, voltage)
legend('v_{in}')
xlabel('Time [s]')
ylabel('Voltage [V]')

subplot(4,1,2)
plot(time, velocity,time, velocity_filtered)
legend('Velocity',"Filtered Velocity")
xlabel('Time [s]')
ylabel('Angular velocity [rad/s]')

subplot(4,1,3)
plot(time, current, time, current_filtered)
legend('Current', 'Filtered Current')
xlabel('Time [s]')
ylabel('Current [A]')

subplot(4,1,4)
plot(time, dIdt_filtered)
legend('Derivative of current')
xlabel('Time [s]')
ylabel('dI_a/dt [A/s]')

%% Define matrices as required for least squares solution
% Output data
Y = voltage;

% Input data
X = [dIdt_filtered, current_filtered, velocity_filtered];

% Evaluate estimate
Theta_opt = inv(X'*X)*X'*Y;

%%

res0 = (Y - X*Theta_opt).^2;
var_est = movmean(res0, round(0.05*length(Y))); % e.g. 5% window
var_est = max(var_est, 1e-8);
W = diag(1./var_est);
Theta_wls = (X'*W*X) \ (X'*W*Y);

%% Compute and plot the estimated outputs
% This is the reconstructed voltage
% Y_hat = Theta_opt(1)*dIdt_filtered + Theta_opt(2)*current_filtered + Theta_opt(3)*velocity_filtered;
Y_hat = Theta_wls(1)*dIdt_filtered + Theta_wls(2)*current_filtered + Theta_wls(3)*velocity_filtered;

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
time2 = motorData.time;
voltage2 = motorData.voltage;
current2 = motorData.current;
velocity2 = motorData.velocity;

% Estimate derivative of current
% Sampling period [s]
Ts = time2(2) - time2(1);

% Compute filtered current and velocity
current_filtered2 = sgolayfilt(current2, K, F);
velocity_filtered2 = sgolayfilt(velocity2, K, F);

% Compute filtered derivative of current
[b, g] = sgolay(K, F);
dIdt_filtered2 = conv(current_filtered2, factorial(1)/(-Ts) * g(:,2), 'same');

% Compute and plot the estimated outputs
% This is the reconstructed voltage
Y_hat2 = Theta_opt(1)*dIdt_filtered2 + Theta_opt(2)*current_filtered2 + Theta_opt(3)*velocity_filtered2;

% Plot the original supplied voltage and reconstructed voltage
figure;
plot(time2, voltage2, time2, Y_hat2)
legend('Supplied voltage', 'Reconstructed voltage')
xlabel('Time [s]')
ylabel('Voltage [V]')

% ---- Compute MSE for validation dataset ----
mse_val = mean((voltage2 - Y_hat2).^2);
fprintf('MSE (Validation dataset, 2 Hz): %.6f\n', mse_val);
