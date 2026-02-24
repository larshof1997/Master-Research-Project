clc; clear all; close all;

%% ===================== USER SETTINGS =====================
Kt1 = 3.018583e+00;          % torque constant [Nm/A]

% Savitzky-Golay filter parameters
F = 61;                       % frame length (odd integer)
K = 2;                        % polynomial order

% Initial guess: psi = [I; fc; b; v_eps]
psi0 = [0.05; 0.1; 0.03; 5e-2];

% Bounds
lb = [0; 0; 0; 1e-4];
ub = [1; 1; 0.5; 0.5];

%% ===================== LOAD DATA =====================
% Trajectory (desired) — 3000x2 matrices, select joint index
joint_idx = 1;                % 1 = shoulder
S_traj = load('DATA_1DOF/trajectory1.mat');
q_des   = S_traj.q(:, joint_idx);       % desired position
qd_des  = S_traj.qd(:, joint_idx);      % desired velocity
qdd_des = S_traj.qdd(:, joint_idx);     % desired acceleration

% Results (measured) — Simulink logs one extra sample, so drop the last row
S_res = load('DATA_1DOF/results1.mat');
S_res = S_res.torque_control_data_shoulder;
S_res = S_res(1:end-1, :);   % trim to match trajectory length

desired_current = S_res(:,1);
actual_current  = S_res(:,2);
voltage         = S_res(:,3);
q_meas          = S_res(:,4);

% Check lengths match
N = numel(q_meas);
assert(numel(q_des) == N, 'trajectory1 and results1 must have same length');

% Time vector (assuming same dt as trajectory)
% Adjust if your .mat files contain a time vector
dt = 1e-3;                    % <-- SET YOUR SAMPLE TIME HERE
t  = (0:N-1).' * dt;

%% ===================== CONVERT CURRENT TO TORQUE =====================

i_filt = sgolayfilt(actual_current, K, F);
tau_meas = Kt1 * i_filt;

%% ===================== FILTER & DIFFERENTIATE =====================
% Filter measured position
q_filt = sgolayfilt(q_meas, K, F);


figure;
hold on;
plot(q_des)
plot(q_filt)


% Velocity via central difference, then filter
qd_raw = zeros(N,1);
qd_raw(1)       = (q_filt(2) - q_filt(1)) / dt;
qd_raw(2:N-1)   = (q_filt(3:N) - q_filt(1:N-2)) / (2*dt);
qd_raw(N)       = (q_filt(N) - q_filt(N-1)) / dt;
qd_filt1 = sgolayfilt(qd_raw, K, F);

[~, g] = sgolay(K, F);  
qd_filt = conv(q_filt, factorial(1)/(-dt) * g(:,2), 'same');

figure;
hold on;
plot(qd_des)
plot(qd_filt)
plot(qd_filt1)


% Acceleration via central difference, then filter
% qdd_raw = zeros(N,1);
% qdd_raw(1)       = (qd_filt(2) - qd_filt(1)) / dt;
% qdd_raw(2:N-1)   = (qd_filt(3:N) - qd_filt(1:N-2)) / (2*dt);
% qdd_raw(N)       = (qd_filt(N) - qd_filt(N-1)) / dt;
% qdd_filt = sgolayfilt(qdd_raw, K, F);

qdd_filt = conv(q_filt, factorial(1)/(-dt) * g(:,2), 'same');

figure;
hold on;
plot(qdd_des)
plot(qdd_filt)

%% ===================== PACK DATA STRUCT =====================
data.q_filt   = q_filt.';      % 1 x N
data.qd_filt  = qd_filt.';
data.qdd_filt = qdd_filt.';
data.tau_meas = tau_meas.';
data.dt       = dt;

%% ===================== NONLINEAR LEAST SQUARES =====================
opts = optimoptions('lsqnonlin', ...
    'Display',                 'iter', ...
    'SpecifyObjectiveGradient', true, ...
    'MaxFunctionEvaluations',   1e5, ...
    'FunctionTolerance',        1e-9, ...
    'StepTolerance',            1e-9);

fun = @(psi) residualsEL_1dof(psi, data);
[psi_hat, ~, res, exitflag, out] = lsqnonlin(fun, psi0, lb, ub, opts);

%% ===================== DISPLAY RESULTS =====================
fprintf('\n========== Identified Parameters ==========\n');
fprintf('  I     = %.6f  [kg m^2]\n', psi_hat(1));
fprintf('  fc    = %.6f  [Nm]\n',     psi_hat(2));
fprintf('  b     = %.6f  [Nm s/rad]\n', psi_hat(3));
fprintf('  v_eps = %.6f  [rad/s]\n',  psi_hat(4));
fprintf('===========================================\n');

%% ===================== SIMULATE IDENTIFIED MODEL =====================
I_hat     = psi_hat(1);
fc_hat    = psi_hat(2);
b_hat     = psi_hat(3);
v_eps_hat = psi_hat(4);

% State: x = [q; qd]
x_hat = zeros(N, 2);
x_hat(1,:) = [q_meas(1), 0];   % initial condition (adjust qd0 if known)

for k = 1:N-1
    h     = dt;
    tau_k = tau_meas(k);

    k1 = f_dyn_1dof(x_hat(k,:).',   tau_k, I_hat, b_hat, fc_hat, v_eps_hat);
    k2 = f_dyn_1dof(x_hat(k,:).' + 0.5*h*k1, tau_k, I_hat, b_hat, fc_hat, v_eps_hat);
    k3 = f_dyn_1dof(x_hat(k,:).' + 0.5*h*k2, tau_k, I_hat, b_hat, fc_hat, v_eps_hat);
    k4 = f_dyn_1dof(x_hat(k,:).' + h*k3,     tau_k, I_hat, b_hat, fc_hat, v_eps_hat);

    x_hat(k+1,:) = (x_hat(k,:).' + (h/6)*(k1 + 2*k2 + 2*k3 + k4)).';
end

%% ===================== COMPUTE MSE =====================
e_q  = q_meas - x_hat(:,1);
e_qd = qd_filt - x_hat(:,2);
mse_q  = mean(e_q.^2);
mse_qd = mean(e_qd.^2);
fprintf('\nMSE position : %.6e\n', mse_q);
fprintf('MSE velocity : %.6e\n', mse_qd);

%% ===================== PLOTS =====================
set(groot, 'defaultTextInterpreter','latex');
set(groot, 'defaultAxesTickLabelInterpreter','latex');
set(groot, 'defaultLegendInterpreter','latex');
defaultFontSize  = 20;
defaultLineWidth = 1.8;
set(groot, 'defaultAxesFontSize',  defaultFontSize);
set(groot, 'defaultLineLineWidth', defaultLineWidth);

% --- Position comparison ---
fig1 = figure('Color','w', 'Position',[200 200 900 350]);
plot(t, q_meas, 'b', 'DisplayName','measured');
hold on;
plot(t, x_hat(:,1), 'r--', 'DisplayName','identified model');
xlabel('Time $[s]$');
ylabel('$q$ [rad]');
title('Position: measured vs identified');
grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);
exportgraphics(fig1, 'position_comparison.png', 'Resolution', 300);

% --- Velocity comparison ---
fig2 = figure('Color','w', 'Position',[250 250 900 350]);
plot(t, qd_filt, 'b', 'DisplayName','filtered meas.');
hold on;
plot(t, x_hat(:,2), 'r--', 'DisplayName','identified model');
xlabel('Time $[s]$');
ylabel('$\dot{q}$ [rad/s]');
title('Velocity: filtered measured vs identified');
grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);
exportgraphics(fig2, 'velocity_comparison.png', 'Resolution', 300);

% --- Torque comparison ---
fig3 = figure('Color','w', 'Position',[300 300 900 350]);
tau_model = I_hat * qdd_filt + b_hat * qd_filt + fc_hat * tanh(qd_filt / v_eps_hat);
plot(t, tau_meas, 'b', 'DisplayName','measured $\tau$');
hold on;
plot(t, tau_model, 'r--', 'DisplayName','model $\tau$');
xlabel('Time $[s]$');
ylabel('$\tau$ [Nm]');
title('Torque: measured vs model prediction');
grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);
exportgraphics(fig3, 'torque_comparison.png', 'Resolution', 300);


%% ===================== LOCAL FUNCTIONS =====================

function dx = f_dyn_1dof(x, tau, I, b, fc, v_eps)
    % x = [q; qd]
    qd  = x(2);
    qdd = (tau - b*qd - fc*tanh(qd/v_eps)) / I;
    dx  = [qd; qdd];
end

function [r, J] = residualsEL_1dof(psi, data)
    % psi = [I; fc; b; v_eps]
    I     = psi(1);
    fc    = psi(2);
    b     = psi(3);
    v_eps = psi(4);

    N = numel(data.q_filt);
    r = zeros(N, 1);
    J = zeros(N, 4);

    for k = 1:N
        qd  = data.qd_filt(k);
        qdd = data.qdd_filt(k);
        tau_m = data.tau_meas(k);

        z = qd / v_eps;
        th = tanh(z);
        sech2z = 1/cosh(z)^2;

        % Model torque
        tau_hat = I * qdd + b * qd + fc * th;

        % Residual
        rk = tau_m - tau_hat;
        r(k) = rk;

        % Jacobian: d(r)/d(psi) = -d(tau_hat)/d(psi)
        Jk = zeros(1, 4);
        Jk(1) = -qdd;                          % d/dI
        Jk(2) = -th;                            % d/dfc
        Jk(3) = -qd;                            % d/db
        Jk(4) = fc * (qd / v_eps^2) * sech2z;  % d/dv_eps (note: + sign)

        J(k,:) = Jk;
    end
end