clc; clear all;
%% Check results
%Load dataset
S = load('planar_2dof_dataset_no_noise_linear_friction.mat');
dataset = S.dataset;

% Choose a run to vaidate on (change this index if you like)
run_idx = 2;
r = dataset.runs(run_idx);

t  = r.time;               % time vector (Nx1)
dt = t(2) - t(1);
N  = numel(t);

tau_applied = r.u_applied; % Nx2, the torque that actually drove the plant
x_true      = r.x_true;    % Nx4, "real" state: [th1 th2 dth1 dth2]
p_true      = r.p;

%% Physical constants (same as in your simulator)
m1 = 1.6537;  l1 = 0.343;  r1 = 0.29;
m2 = 0.9982;  l2 = 0.267;  r2 = 0.175;

%load python env
pyenv('Version','/Library/Frameworks/Python.framework/Versions/3.11/bin/python3');

% Import your ONNX Python wrapper
% py.importlib.import_module('FFNN');
% import HNN module 
py.importlib.import_module('HNN_predict2');

% Preallocate
x_hat = zeros(N,4);      % [q1 q2 qd1 qd2]
x_hat(1,1:2) = x_true(1,1:2); % initial condition
x_hat(1,3:4) = p_true(1,1:2); % initial condition

x_hat_hnn = zeros(N,4);  % [q1 q2 p1 p2]
x_hat_hnn(1,1:2) = x_true(1,1:2);  % q0
x_hat_hnn(1,3:4) = p_true(1,1:2);  % p0

dt = t(2) - t(1);

% call it
% x_hnn = double([x_true(1,1), x_true(1,2), p_true(1,1), p_true(1,2)]);  % 1x4
% py_out = py.HNN_predict2.predict_next(x_hnn, dt);  % Python object
% % convert to MATLAB double (1x4)
% x_next_hnn = double(py_out);

xd_hat =  zeros(N,2);
xdd_hat =  zeros(N,2);
py.HNN_predict2.load_model();
for k = 1:N-1
    % Predict acceleration from NN
    % x_hat_hnn(k,:);
    x_py = py.HNN_predict2.predict_next(x_hat_hnn(k,:), dt, tau_applied(k,:));

    x_mat = cellfun(@double, cell(x_py.tolist()));
    x_hat_hnn(k+1,:) = x_mat;
end


%% Plots: true vs identified model

figure('Color','w','Name','Joint angles: true vs identified');
subplot(2,1,1); hold on; grid on;
plot(t, x_true(:,1), 'b', 'LineWidth', 1.5);
plot(t, x_hat_hnn(:,1),  'r--', 'LineWidth', 1.5);
xlabel('Time [s]'); ylabel('theta_1 [rad]');
legend('true','identified','Location','best');
title('Joint 1 angle');

subplot(2,1,2); hold on; grid on;
plot(t, x_true(:,2), 'b', 'LineWidth', 1.5);
plot(t, x_hat_hnn(:,2),  'r--', 'LineWidth', 1.5);
xlabel('Time [s]'); ylabel('theta_2 [rad]');
legend('true','identified','Location','best');
title('Joint 2 angle');

figure('Color','w','Name','Joint velocities: true vs identified');
subplot(2,1,1); hold on; grid on;
plot(t, p_true(:,1), 'b', 'LineWidth', 1.5);
plot(t, x_hat_hnn(:,3),  'r--', 'LineWidth', 1.5);
xlabel('Time [s]'); 
legend('true','identified','Location','best');
title('Joint 1 momentum');

subplot(2,1,2); hold on; grid on;
plot(t, p_true(:,2), 'b', 'LineWidth', 1.5);
plot(t, x_hat_hnn(:,4),  'r--', 'LineWidth', 1.5);
xlabel('Time [s]'); 
legend('true','identified','Location','best');
title('Joint 2 momentum');

figure('Color','w','Name','Joint Torques');
subplot(2,1,1); hold on; grid on;
plot(t, tau_applied(:,1), 'b', 'LineWidth', 1.5);
xlabel('Time [s]'); 
legend('true','Location','best');
title('Joint 1 Torque');

subplot(2,1,2); hold on; grid on;
plot(t, tau_applied(:,2), 'b', 'LineWidth', 1.5);
xlabel('Time [s]'); 
legend('true','Location','best');
title('Joint 2 Torque');