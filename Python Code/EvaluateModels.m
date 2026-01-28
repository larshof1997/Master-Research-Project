clc; clear all;
%% Check results
%Load dataset
S = load('planar_2dof_dataset_no_noise_linear_friction.mat');
dataset = S.dataset;

% Choose a run to vaidate on (change this index if you like)
run_idx = 9;
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

mse_x = zeros(N,4);
mse_x(:,1:2) = x_true(:,1:2); % initial condition
mse_x(:,3:4) = p_true(:,1:2); % initial condition

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

%% 

mse = computeMSEJointStates(mse_x, x_hat_hnn)

function mse = computeMSEJointStates(x_true, x_hat)
    % Ensure x_hat has the same orientation as x_true
    if size(x_hat,1) == 4 && size(x_hat,2) == size(x_true,1)
        x_hat = x_hat.';  % transpose to N x 4
    elseif size(x_hat,1) ~= size(x_true,1) || size(x_hat,2) ~= 4
        error('x_hat must have size N x 4 or 4 x N, where N = number of samples');
    end

    % True states
    q_true  = x_true(:,1:2);   % [theta1 theta2]
    qd_true = x_true(:,3:4);   % [dtheta1 dtheta2]

    % Estimated states
    q_hat  = x_hat(:,1:2);
    qd_hat = x_hat(:,3:4);

    % Errors
    e_q  = q_true  - q_hat;
    e_qd = qd_true - qd_hat;

    % Per-state MSE
    mse.theta1  = mean(e_q(:,1).^2);
    mse.theta2  = mean(e_q(:,2).^2);
    mse.dtheta1 = mean(e_qd(:,1).^2);
    mse.dtheta2 = mean(e_qd(:,2).^2);

    % Combined MSEs
    mse.theta  = mean(e_q(:).^2);                 % all angle samples
    mse.dtheta = mean(e_qd(:).^2);                % all velocity samples
    mse.total  = mean([e_q(:); e_qd(:)].^2);     % all 4 states together
end


%% Plots: true vs identified model

%% ---------- LaTeX-style plotting setup ----------
set(groot, 'defaultTextInterpreter','latex');
set(groot, 'defaultAxesTickLabelInterpreter','latex');
set(groot, 'defaultLegendInterpreter','latex');

defaultFontSize = 20;
defaultLineWidth = 1.8;

set(groot, 'defaultAxesFontSize', defaultFontSize);
set(groot, 'defaultLineLineWidth', defaultLineWidth);

% ---------- Joint angles: true vs identified ----------
fig_angles = figure('Color','w', 'Position',[200 200 900 400]);
tiledlayout(2,1,'Padding','compact','TileSpacing','compact');

% Joint 1
nexttile;
plot(t, x_true(:,1), 'b', 'DisplayName','true'); hold on;
plot(t, x_hat_hnn(:,1), 'r--', 'DisplayName','identified');
xlabel('Time $[s]$', 'Interpreter','latex');
ylabel('$\theta_1$ [rad]', 'Interpreter','latex');
title('Joint 1 angle', 'Interpreter','latex');
grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

% Joint 2
nexttile;
plot(t, x_true(:,2), 'b', 'DisplayName','true'); hold on;
plot(t, x_hat_hnn(:,2), 'r--', 'DisplayName','identified');
xlabel('Time $[s]$', 'Interpreter','latex');
ylabel('$\theta_2$ [rad]', 'Interpreter','latex');
title('Joint 2 angle', 'Interpreter','latex');
grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

% Save figure
exportgraphics(fig_angles, 'HNN_joint_angles.png', 'Resolution',300, 'BackgroundColor','white');

% ---------- Joint momentum: true vs identified ----------
fig_momentum = figure('Color','w', 'Position',[250 250 900 400]);
tiledlayout(2,1,'Padding','compact','TileSpacing','compact');

% Joint 1
nexttile;
plot(t, p_true(:,1), 'b', 'DisplayName','true'); hold on;
plot(t, x_hat_hnn(:,3), 'r--', 'DisplayName','identified');
xlabel('Time $[s]$', 'Interpreter','latex');
ylabel('$p_1$ [kg m$^2$/s]', 'Interpreter','latex');
title('Joint 1 momentum', 'Interpreter','latex');
grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

% Joint 2
nexttile;
plot(t, p_true(:,2), 'b', 'DisplayName','true'); hold on;
plot(t, x_hat_hnn(:,4), 'r--', 'DisplayName','identified');
xlabel('Time $[s]$', 'Interpreter','latex');
ylabel('$p_2$ [kg m$^2$/s]', 'Interpreter','latex');
title('Joint 2 momentum', 'Interpreter','latex');
grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

% Save figure
exportgraphics(fig_momentum, 'HNN_joint_momentum.png', 'Resolution',300, 'BackgroundColor','white');

% ---------- Joint Torques ----------
fig_tau = figure('Color','w', 'Position',[300 300 900 400]);
tiledlayout(2,1,'Padding','compact','TileSpacing','compact');

% Joint 1
nexttile;
plot(t, tau_applied(:,1), 'b', 'DisplayName','applied'); 
xlabel('Time $[s]$', 'Interpreter','latex');
ylabel('$\tau_1$ [Nm]', 'Interpreter','latex');
title('Joint 1 Torque', 'Interpreter','latex');
grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

% Joint 2
nexttile;
plot(t, tau_applied(:,2), 'b', 'DisplayName','applied'); 
xlabel('Time $[s]$', 'Interpreter','latex');
ylabel('$\tau_2$ [Nm]', 'Interpreter','latex');
title('Joint 2 Torque', 'Interpreter','latex');
grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

% Save figure
exportgraphics(fig_tau, 'HNN_joint_torques.png', 'Resolution',300, 'BackgroundColor','white');