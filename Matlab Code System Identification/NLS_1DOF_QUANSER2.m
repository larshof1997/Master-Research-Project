clc; clear all; close all;

%% ===================== USER SETTINGS =====================
Kt1 = 3.018583e+00;          % torque constant [Nm/A]
joint_idx = 1;                % which column of trajectory to use

% psi = [I; fc; b; v_eps]
psi0 = [0.017224; 0.206530; 0.1; 0.1];

v_eps = 1e-3;  % smoothing speed [rad/s] for tanh for Linear LS
lb = [0; 0; 0; 0];
ub = [0.5; 0.5; 0.5; 0.5];

% Savitzky-Golay filter parameters
F = 61;
K = 2;

%% ===================== LOAD & PREPARE DATA =====================
% Trajectory (desired) — Nx2 matrices
S_traj = load('DATA_1DOF/trajectory1.mat');
q_des   = S_traj.q(:, joint_idx);
qd_des  = S_traj.qd(:, joint_idx);
qdd_des = S_traj.qdd(:, joint_idx);

% Results (measured) — Simulink logs one extra sample, trim
S_res = load('DATA_1DOF/results3.mat');
S_res = S_res.torque_control_data_shoulder;
S_res = S_res(1:end-1, :);

desired_current = S_res(:,1);
actual_current  = S_res(:,2);
voltage         = S_res(:,3);
q_meas          = S_res(:,4);

N = numel(q_meas);
assert(numel(q_des) == N, 'trajectory1 and results1 must have same length');

% Time vector
dt = 1e-2;                    % <-- SET YOUR SAMPLE TIME HERE
t  = (0:N-1).' * dt;

% Convert current to torque
tau_meas = Kt1 * actual_current;

%% ===================== CONVERT TO ID DATA FORMAT =====================
data = dataset_to_iddata_1dof(t, q_meas, tau_meas, dt, K, F);

%% ===================== IDENTIFICATION =====================

% --- Linear LS (viscous only) ---
psi_hat_lin_visc = estimate_theta_ls_viscous_1dof(data, v_eps);
fprintf('\n===== Linear LS (viscous only) =====\n');
fprintf('  I   = %.6f\n', psi_hat_lin_visc(1));
fprintf('  b   = %.6f\n', psi_hat_lin_visc(2));

% --- Linear LS (viscous + Coulomb, v_eps fixed) ---
psi_hat_lin = estimate_theta_ls_1dof(data, v_eps);
fprintf('\n===== Linear LS (viscous + Coulomb) =====\n');
fprintf('  I   = %.6f\n', psi_hat_lin(1));
fprintf('  fc  = %.6f\n', psi_hat_lin(2));
fprintf('  b   = %.6f\n', psi_hat_lin(3));

% --- Nonlinear LS ---
opts = optimoptions('lsqnonlin', ...
    'Display','iter', ...
    'SpecifyObjectiveGradient', true, ...
    'MaxFunctionEvaluations', 1e5, ...
    'FunctionTolerance', 1e-9, ...
    'StepTolerance', 1e-9);

fun = @(psi) residualsEL_analytic_1dof(psi, data);
[psi_hat, ~, res, exitflag, out] = lsqnonlin(fun, psi0, lb, ub, opts);

fprintf('\n===== Nonlinear LS =====\n');
fprintf('  I     = %.6f  [kg m^2]\n',   psi_hat(1));
fprintf('  fc    = %.6f  [Nm]\n',        psi_hat(2));
fprintf('  b     = %.6f  [Nm s/rad]\n',  psi_hat(3));
fprintf('  v_eps = %.6f  [rad/s]\n',     psi_hat(4));

%% ===================== CHECK RESULTS: SIMULATE =====================
I_hat     = psi_hat(1);
fc_hat    = psi_hat(2);
b_hat     = psi_hat(3);
v_eps_hat = psi_hat(4);

% State: x = [q; qd]
x_hat = zeros(N, 2);
x_hat(1,:) = [q_meas(1), 0];   % same initial condition

for k = 1:N-1
    h     = dt;
    tau_k = tau_meas(k);

    % RK4 integration step using identified parameters
    k1 = f_dyn_1dof(x_hat(k,:).',             tau_k, I_hat, b_hat, fc_hat, v_eps_hat);
    k2 = f_dyn_1dof(x_hat(k,:).' + 0.5*h*k1, tau_k, I_hat, b_hat, fc_hat, v_eps_hat);
    k3 = f_dyn_1dof(x_hat(k,:).' + 0.5*h*k2, tau_k, I_hat, b_hat, fc_hat, v_eps_hat);
    k4 = f_dyn_1dof(x_hat(k,:).' + h*k3,     tau_k, I_hat, b_hat, fc_hat, v_eps_hat);

    x_hat(k+1,:) = (x_hat(k,:).' + (h/6)*(k1 + 2*k2 + 2*k3 + k4)).';
end

%% ===================== MSE =====================
e_q  = q_meas - x_hat(:,1);
e_qd = data.qd_filt(:).' - x_hat(:,2).';
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

%% ---------- Position: measured vs identified ----------
fig1 = figure('Color','w', 'Position',[200 200 900 400]);
plot(t, q_meas, 'b', 'DisplayName','measured');
hold on;
plot(t, x_hat(:,1), 'r--', 'DisplayName','identified');
xlabel('Time $[s]$');
ylabel('$q$ [rad]');
title('Position: measured vs identified');
grid on; box on;
legend('Location','southeast', 'FontSize', defaultFontSize-2);
exportgraphics(fig1, 'position_comparison.png', 'Resolution', 300, 'BackgroundColor','white');

%% ---------- Velocity: filtered measured vs identified ----------
fig2 = figure('Color','w', 'Position',[250 250 900 400]);
plot(t, data.qd_filt, 'b', 'DisplayName','filtered meas.');
hold on;
plot(t, x_hat(:,2), 'r--', 'DisplayName','identified');
xlabel('Time $[s]$');
ylabel('$\dot{q}$ [rad/s]');
title('Velocity: filtered measured vs identified');
grid on; box on;
legend('Location','southeast', 'FontSize', defaultFontSize-2);
exportgraphics(fig2, 'velocity_comparison.png', 'Resolution', 300, 'BackgroundColor','white');

%% ---------- Torque: measured vs model ----------
fig3 = figure('Color','w', 'Position',[300 300 900 400]);
tau_model = I_hat * data.qdd_filt + b_hat * data.qd_filt + fc_hat * tanh(data.qd_filt / v_eps_hat);
plot(t, tau_meas, 'b', 'DisplayName','measured $\tau$');
hold on;
plot(t, tau_model, 'r--', 'DisplayName','model $\tau$');
xlabel('Time $[s]$');
ylabel('$\tau$ [Nm]');
title('Torque: measured vs model prediction');
grid on; box on;
legend('Location','southeast', 'FontSize', defaultFontSize-2);
exportgraphics(fig3, 'torque_comparison.png', 'Resolution', 300, 'BackgroundColor','white');


%% ===================== LOCAL FUNCTIONS =====================

function dx = f_dyn_1dof(x, tau, I, b, fc, v_eps)
    % x = [q; qd]
    qd  = x(2);
    qdd = (tau - b*qd - fc*tanh(qd/v_eps)) / I;
    dx  = [qd; qdd];
end

function data = dataset_to_iddata_1dof(t, q_meas, tau_meas, dt, K, F)
    % Mirrors dataset_to_iddata from 2DOF code, adapted for 1DOF single run
    %
    % Same processing chain:
    %   1. Filter positions with sgolayfilt
    %   2. Central difference -> raw velocities
    %   3. Filter velocities with sgolayfilt
    %   4. Central difference -> raw accelerations
    %   5. Filter accelerations with sgolayfilt

    N = numel(q_meas);

    data.t        = t(:).';         % 1 x N
    data.q_meas   = q_meas(:).';    % 1 x N
    data.tau_meas = tau_meas(:).';   % 1 x N
    data.dt       = dt;

    % --- Step 1: Filter positions ---
    q_filt = sgolayfilt(q_meas(:), K, F);
    data.q_filt = q_filt(:).';      % 1 x N

    % --- Step 2: Velocities via central difference ---
    qd_raw = zeros(N,1);
    qd_raw(1)       = (q_filt(2) - q_filt(1)) / dt;
    for k = 2:N-1
        qd_raw(k) = (q_filt(k+1) - q_filt(k-1)) / (2*dt);
    end
    qd_raw(N)       = (q_filt(N) - q_filt(N-1)) / dt;

    % --- Step 3: Filter velocities ---
    qd_filt = sgolayfilt(qd_raw, K, F);
    data.qd_filt = qd_filt(:).';    % 1 x N

    % --- Step 4: Accelerations via central difference ---
    qdd_raw = zeros(N,1);
    qdd_raw(1)       = (qd_filt(2) - qd_filt(1)) / dt;
    for k = 2:N-1
        qdd_raw(k) = (qd_filt(k+1) - qd_filt(k-1)) / (2*dt);
    end
    qdd_raw(N)       = (qd_filt(N) - qd_filt(N-1)) / dt;

    % --- Step 5: Filter accelerations ---
    qdd_filt = sgolayfilt(qdd_raw, K, F);
    data.qdd_filt = qdd_filt(:).';  % 1 x N
end

function [r, J] = residualsEL_analytic_1dof(psi, data)
    % psi = [I; fc; b; v_eps]
    % Mirrors residualsEL_analytic from 2DOF code, for 1DOF
    I     = psi(1);
    fc    = psi(2);
    b     = psi(3);
    v_eps = psi(4);

    N = size(data.q_filt, 2);
    r = zeros(N, 1);
    J = zeros(N, 4);

    for k = 1:N
        qd    = data.qd_filt(k);
        qdd   = data.qdd_filt(k);
        tau_m = data.tau_meas(k);

        z      = qd / v_eps;
        th     = tanh(z);
        sech2z = 1/cosh(z)^2;

        % Model: tau_hat = I*qdd + b*qd + fc*tanh(qd/v_eps)
        tau_hat = I*qdd + b*qd + fc*th;
        r(k)    = tau_m - tau_hat;

        % Jacobian: dr/dpsi = -d(tau_hat)/dpsi
        J(k,1) = -qdd;                             % d/dI
        J(k,2) = -th;                              % d/dfc
        J(k,3) = -qd;                              % d/db
        J(k,4) =  fc * (qd / v_eps^2) * sech2z;   % d/dv_eps
    end
end

function r = residualsEL_1dof(psi, data)
    % Numeric-only residuals (no Jacobian), mirrors residualsEL from 2DOF
    % psi = [I; fc; b; v_eps]
    I     = psi(1);
    fc    = psi(2);
    b     = psi(3);
    v_eps = psi(4);

    N = size(data.q_filt, 2);
    r = zeros(N, 1);

    for k = 1:N
        qd    = data.qd_filt(k);
        qdd   = data.qdd_filt(k);
        tau_m = data.tau_meas(k);

        tau_hat = I*qdd + b*qd + fc*tanh(qd/v_eps);
        r(k)   = tau_m - tau_hat;
    end
end

function theta_hat = estimate_theta_ls_1dof(data, v_eps)
    % Linear LS with Coulomb friction (v_eps fixed)
    % Mirrors estimate_theta_ls from 2DOF code
    % theta = [I; fc; b]
    % Model: tau = I*qdd + fc*tanh(qd/v_eps) + b*qd

    N = size(data.q_filt, 2);
    Y_stack   = zeros(N, 3);
    tau_stack = zeros(N, 1);

    for k = 1:N
        qd  = data.qd_filt(k);
        qdd = data.qdd_filt(k);

        % Regressor row: [qdd, tanh(qd/v_eps), qd]
        Y_stack(k,:)  = [qdd, tanh(qd/v_eps), qd];
        tau_stack(k)  = data.tau_meas(k);
    end

    % Check conditioning
    fprintf('\n=== Regressor Conditioning (LS with Coulomb) ===\n');
    fprintf('Condition number: %.2e\n', cond(Y_stack' * Y_stack));
    fprintf('Rank: %d/%d\n', rank(Y_stack, 1e-10), size(Y_stack, 2));

    % Solve LS
    theta_hat = Y_stack \ tau_stack;
end

function theta_hat = estimate_theta_ls_viscous_1dof(data, v_eps)
    % Linear LS with viscous friction only
    % Mirrors estimate_theta_ls_viscous from 2DOF code
    % theta = [I; b]
    % Model: tau = I*qdd + b*qd

    N = size(data.q_filt, 2);
    Y_stack   = zeros(N, 2);
    tau_stack = zeros(N, 1);

    for k = 1:N
        qd  = data.qd_filt(k);
        qdd = data.qdd_filt(k);

        % Regressor row: [qdd, qd]
        Y_stack(k,:)  = [qdd, qd];
        tau_stack(k)  = data.tau_meas(k);
    end

    % Check conditioning
    fprintf('\n=== Regressor Conditioning (viscous only) ===\n');
    fprintf('Condition number: %.2e\n', cond(Y_stack' * Y_stack));
    fprintf('Rank: %d/%d\n', rank(Y_stack, 1e-10), size(Y_stack, 2));

    % Solve LS
    theta_hat = Y_stack \ tau_stack;
end