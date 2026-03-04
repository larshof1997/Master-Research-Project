clc; clear all; close all;

%% ===================== USER SETTINGS =====================
Kt1 = 3.018583e+00;
Kt2 = 1.111065;

J1_motor  = 2.030252e-02;
B1_motor  = 9.233265e-02;
J2_motor  = 6.530040e-04;
B2_motor  = 4.505757e-02;

v_eps = 0.034872;  % smoothing speed [rad/s] for tanh (fixed in Linear LS)

% Bounds for NLS: psi = [a1; a2; bp; fc1; fc2; b1; b2; v_eps]
lb = [1e-3; 1e-3; 0; 0; 0; 0; 0; 1e-4];
ub = [1;    1;    0.5; 0.5; 0.5; 0.5; 0.5; 0.5];

% Savitzky-Golay filter parameters
F = 61;
K = 2;

%% ===================== LOAD & PREPARE DATA =====================
S_traj = load('DATA_2DOF/trajectory.mat');
q_des   = S_traj.q;
qd_des  = S_traj.qd;
qdd_des = S_traj.qdd;

S_res1 = load('DATA_2DOF/shoulder4.mat');
S_res1 = S_res1.torque_control_data_shoulder;
S_res1 = S_res1(1:end-1, :);

S_res2 = load('DATA_2DOF/elbow4.mat');
S_res2 = S_res2.torque_control_data_elbow;
S_res2 = S_res2(1:end-1, :);

actual_current_1 = S_res1(:,2);
q_meas_1         = S_res1(:,4);

actual_current_2 = S_res2(:,2);
q_meas_2         = S_res2(:,4);

N = numel(q_meas_1);
assert(size(q_des,1) == N, 'trajectory and results must have same length');

dt = 1e-2;
t  = (0:N-1).' * dt;

tau_meas = [Kt1 * actual_current_1, Kt2 * actual_current_2];
q_meas   = [q_meas_1, q_meas_2];

%% ===================== CONVERT TO ID DATA FORMAT =====================
data = dataset_to_iddata_2dof(t, q_meas, tau_meas, dt, K, F);

% tau_load = tau_motor - J*qdd - B*qd
% data.tau_meas(1,:) = data.tau_meas(1,:) - J1_motor * data.qdd_filt(1,:) - B1_motor * data.qd_filt(1,:);
% data.tau_meas(2,:) = data.tau_meas(2,:) - J2_motor * data.qdd_filt(2,:) - B2_motor * data.qd_filt(2,:);

% Filter torque (same SG params as position)
% data.tau_meas(1,:) = sgolayfilt(data.tau_meas(1,:), K, F);
% data.tau_meas(2,:) = sgolayfilt(data.tau_meas(2,:), K, F);


% Update Nx2 version for simulation/plotting
tau_meas(:,1) = data.tau_meas(1,:).';
tau_meas(:,2) = data.tau_meas(2,:).';

%% ===================== LINEAR LS (viscous only, a1 a2 bp free) =====================
psi_hat_lin = estimate_theta_ls_2dof(data);
fprintf('\n===== Linear LS (viscous only) =====\n');
fprintf('  a1 = %.6f\n', psi_hat_lin(1));
fprintf('  a2 = %.6f\n', psi_hat_lin(2));
fprintf('  bp = %.6f\n', psi_hat_lin(3));
fprintf('  b1 = %.6f\n', psi_hat_lin(4));
fprintf('  b2 = %.6f\n', psi_hat_lin(5));

fprintf('\n  det(M) check LS: a1*a2 = %.6f > bp^2 = %.6f ? %s\n', ...
    psi_hat_lin(1)*psi_hat_lin(2), psi_hat_lin(3)^2, ...
    mat2str(psi_hat_lin(1)*psi_hat_lin(2) > psi_hat_lin(3)^2));

%% ===================== NONLINEAR LS (warm-started from Linear LS) =====================
opts = optimoptions('lsqnonlin', ...
    'Display','iter', ...
    'SpecifyObjectiveGradient', true, ...
    'MaxFunctionEvaluations', 1e5, ...
    'FunctionTolerance', 1e-9, ...
    'StepTolerance', 1e-9);

% Warm-start: [a1; a2; bp; fc1; fc2; b1; b2; v_eps]
psi0_nls = [psi_hat_lin(1);    % a1
            psi_hat_lin(2);    % a2
            psi_hat_lin(3);    % bp
            0.1;               % fc1 (guess)
            0.1;               % fc2 (guess)
            psi_hat_lin(4);    % b1
            psi_hat_lin(5);    % b2
            5e-2];             % v_eps (guess)

fun = @(psi) residualsEL_analytic_2dof(psi, data);
[psi_hat, ~, res, exitflag, out] = lsqnonlin(fun, psi0_nls, lb, ub, opts);

fprintf('\n===== Nonlinear LS =====\n');
fprintf('  a1    = %.6f  [kg m^2]\n',   psi_hat(1));
fprintf('  a2    = %.6f  [kg m^2]\n',   psi_hat(2));
fprintf('  bp    = %.6f  [kg m^2]\n',   psi_hat(3));
fprintf('  fc1   = %.6f  [Nm]\n',       psi_hat(4));
fprintf('  fc2   = %.6f  [Nm]\n',       psi_hat(5));
fprintf('  b1    = %.6f  [Nm s/rad]\n', psi_hat(6));
fprintf('  b2    = %.6f  [Nm s/rad]\n', psi_hat(7));
fprintf('  v_eps = %.6f  [rad/s]\n',    psi_hat(8));

fprintf('\n  det(M) check NLS: a1*a2 = %.6f > bp^2 = %.6f ? %s\n', ...
    psi_hat(1)*psi_hat(2), psi_hat(3)^2, ...
    mat2str(psi_hat(1)*psi_hat(2) > psi_hat(3)^2));

%% ===================== SIMULATE BOTH MODELS =====================

% --- Linear LS parameters (viscous only) ---
a1_lin = psi_hat_lin(1);
a2_lin = psi_hat_lin(2);
bp_lin = psi_hat_lin(3);
b1_lin = psi_hat_lin(4);
b2_lin = psi_hat_lin(5);
fc1_lin   = 0;
fc2_lin   = 0;
v_eps_lin = v_eps;

% --- NLS parameters ---
a1_nls    = psi_hat(1);
a2_nls    = psi_hat(2);
bp_nls    = psi_hat(3);
fc1_nls   = psi_hat(4);
fc2_nls   = psi_hat(5);
b1_nls    = psi_hat(6);
b2_nls    = psi_hat(7);
v_eps_nls = psi_hat(8);

% --- Simulate Linear LS model ---
x_lin = zeros(N, 4);
x_lin(1,:) = [q_meas(1,1), q_meas(1,2), 0, 0];

for k = 1:N-1
    h     = dt;
    tau_k = tau_meas(k,:).';
    k1 = f_dyn_2dof(x_lin(k,:).',             tau_k, a1_lin, a2_lin, bp_lin, b1_lin, b2_lin, fc1_lin, fc2_lin, v_eps_lin);
    k2 = f_dyn_2dof(x_lin(k,:).' + 0.5*h*k1, tau_k, a1_lin, a2_lin, bp_lin, b1_lin, b2_lin, fc1_lin, fc2_lin, v_eps_lin);
    k3 = f_dyn_2dof(x_lin(k,:).' + 0.5*h*k2, tau_k, a1_lin, a2_lin, bp_lin, b1_lin, b2_lin, fc1_lin, fc2_lin, v_eps_lin);
    k4 = f_dyn_2dof(x_lin(k,:).' + h*k3,     tau_k, a1_lin, a2_lin, bp_lin, b1_lin, b2_lin, fc1_lin, fc2_lin, v_eps_lin);
    x_lin(k+1,:) = (x_lin(k,:).' + (h/6)*(k1 + 2*k2 + 2*k3 + k4)).';
end

% --- Simulate NLS model ---
x_nls = zeros(N, 4);
x_nls(1,:) = [q_meas(1,1), q_meas(1,2), 0, 0];

for k = 1:N-1
    h     = dt;
    tau_k = tau_meas(k,:).';
    k1 = f_dyn_2dof(x_nls(k,:).',             tau_k, a1_nls, a2_nls, bp_nls, b1_nls, b2_nls, fc1_nls, fc2_nls, v_eps_nls);
    k2 = f_dyn_2dof(x_nls(k,:).' + 0.5*h*k1, tau_k, a1_nls, a2_nls, bp_nls, b1_nls, b2_nls, fc1_nls, fc2_nls, v_eps_nls);
    k3 = f_dyn_2dof(x_nls(k,:).' + 0.5*h*k2, tau_k, a1_nls, a2_nls, bp_nls, b1_nls, b2_nls, fc1_nls, fc2_nls, v_eps_nls);
    k4 = f_dyn_2dof(x_nls(k,:).' + h*k3,     tau_k, a1_nls, a2_nls, bp_nls, b1_nls, b2_nls, fc1_nls, fc2_nls, v_eps_nls);
    x_nls(k+1,:) = (x_nls(k,:).' + (h/6)*(k1 + 2*k2 + 2*k3 + k4)).';
end

%% ===================== RECONSTRUCT TORQUES (pointwise) =====================

tau_model_lin = zeros(N,2);
tau_model_nls = zeros(N,2);

for k = 1:N
    q_k   = data.q_filt(:,k);
    qd_k  = data.qd_filt(:,k);
    qdd_k = data.qdd_filt(:,k);

    % Linear LS model torque
    M_l = M_mat(q_k(2), a1_lin, a2_lin, bp_lin);
    C_l = C_mat(q_k(2), qd_k(1), qd_k(2), bp_lin);
    Fv_l = [b1_lin*qd_k(1); b2_lin*qd_k(2)];
    tau_model_lin(k,:) = (M_l*qdd_k + C_l*qd_k + Fv_l).';

    % NLS model torque
    M_n = M_mat(q_k(2), a1_nls, a2_nls, bp_nls);
    C_n = C_mat(q_k(2), qd_k(1), qd_k(2), bp_nls);
    Fv_n = [b1_nls*qd_k(1); b2_nls*qd_k(2)];
    Fc_n = [fc1_nls*tanh(qd_k(1)/v_eps_nls); fc2_nls*tanh(qd_k(2)/v_eps_nls)];
    tau_model_nls(k,:) = (M_n*qdd_k + C_n*qd_k + Fv_n + Fc_n).';
end

%% ===================== MSE =====================
fprintf('\n==================== MSE COMPARISON ====================\n');

fprintf('\n--- Forward simulation MSE ---\n');

e_q1_lin  = q_meas(:,1) - x_lin(:,1);
e_q2_lin  = q_meas(:,2) - x_lin(:,2);
e_qd1_lin = data.qd_filt(1,:).' - x_lin(:,3);
e_qd2_lin = data.qd_filt(2,:).' - x_lin(:,4);

e_q1_nls  = q_meas(:,1) - x_nls(:,1);
e_q2_nls  = q_meas(:,2) - x_nls(:,2);
e_qd1_nls = data.qd_filt(1,:).' - x_nls(:,3);
e_qd2_nls = data.qd_filt(2,:).' - x_nls(:,4);

fprintf('       Linear LS          Nonlinear LS\n');
fprintf('  MSE q1  :   %.6e     %.6e\n',  mean(e_q1_lin.^2),  mean(e_q1_nls.^2));
fprintf('  MSE q2  :   %.6e     %.6e\n',  mean(e_q2_lin.^2),  mean(e_q2_nls.^2));
fprintf('  MSE dq1 :   %.6e     %.6e\n',  mean(e_qd1_lin.^2), mean(e_qd1_nls.^2));
fprintf('  MSE dq2 :   %.6e     %.6e\n',  mean(e_qd2_lin.^2), mean(e_qd2_nls.^2));

fprintf('\n--- Torque reconstruction MSE (pointwise) ---\n');
e_tau1_lin = tau_meas(:,1) - tau_model_lin(:,1);
e_tau2_lin = tau_meas(:,2) - tau_model_lin(:,2);
e_tau1_nls = tau_meas(:,1) - tau_model_nls(:,1);
e_tau2_nls = tau_meas(:,2) - tau_model_nls(:,2);

fprintf('              Linear LS          Nonlinear LS\n');
fprintf('  MSE tau1:   %.6e     %.6e\n', mean(e_tau1_lin.^2), mean(e_tau1_nls.^2));
fprintf('  MSE tau2:   %.6e     %.6e\n', mean(e_tau2_lin.^2), mean(e_tau2_nls.^2));
fprintf('========================================================\n');

%% ===================== PLOTS =====================
set(groot, 'defaultTextInterpreter','latex');
set(groot, 'defaultAxesTickLabelInterpreter','latex');
set(groot, 'defaultLegendInterpreter','latex');

defaultFontSize  = 20;
defaultLineWidth = 1.8;

set(groot, 'defaultAxesFontSize',  defaultFontSize);
set(groot, 'defaultLineLineWidth', defaultLineWidth);

%% ---------- Joint angles ----------
fig_ang = figure('Color','w', 'Position',[200 200 900 500]);
tiledlayout(2,1, 'Padding','compact', 'TileSpacing','compact');

nexttile;
plot(t, q_meas(:,1), 'b', 'DisplayName','measured');
hold on;
plot(t, x_lin(:,1), 'r--', 'DisplayName','Linear LS');
plot(t, x_nls(:,1), 'g-.', 'DisplayName','NLS');
xlabel('Time $[s]$'); ylabel('$\theta_1$ [rad]');
title('Joint 1 angle'); grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

nexttile;
plot(t, q_meas(:,2), 'b', 'DisplayName','measured');
hold on;
plot(t, x_lin(:,2), 'r--', 'DisplayName','Linear LS');
plot(t, x_nls(:,2), 'g-.', 'DisplayName','NLS');
xlabel('Time $[s]$'); ylabel('$\theta_2$ [rad]');
title('Joint 2 angle'); grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

exportgraphics(fig_ang, 'joint_angles_comparison.png', 'Resolution', 300, 'BackgroundColor','white');

%% ---------- Joint velocities ----------
fig_vel = figure('Color','w', 'Position',[250 250 900 500]);
tiledlayout(2,1, 'Padding','compact', 'TileSpacing','compact');

nexttile;
plot(t, data.qd_filt(1,:), 'b', 'DisplayName','filtered meas.');
hold on;
plot(t, x_lin(:,3), 'r--', 'DisplayName','Linear LS');
plot(t, x_nls(:,3), 'g-.', 'DisplayName','NLS');
xlabel('Time $[s]$'); ylabel('$\dot{\theta}_1$ [rad/s]');
title('Joint 1 velocity'); grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

nexttile;
plot(t, data.qd_filt(2,:), 'b', 'DisplayName','filtered meas.');
hold on;
plot(t, x_lin(:,4), 'r--', 'DisplayName','Linear LS');
plot(t, x_nls(:,4), 'g-.', 'DisplayName','NLS');
xlabel('Time $[s]$'); ylabel('$\dot{\theta}_2$ [rad/s]');
title('Joint 2 velocity'); grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

exportgraphics(fig_vel, 'joint_velocities_comparison.png', 'Resolution', 300, 'BackgroundColor','white');

%% ---------- Torque comparison ----------
fig_tau = figure('Color','w', 'Position',[300 300 900 500]);
tiledlayout(2,1, 'Padding','compact', 'TileSpacing','compact');

nexttile;
plot(t, tau_meas(:,1), 'b', 'DisplayName','measured $\tau_1$');
hold on;
plot(t, tau_model_lin(:,1), 'r--', 'DisplayName','Linear LS');
plot(t, tau_model_nls(:,1), 'g-.', 'DisplayName','NLS');
xlabel('Time $[s]$'); ylabel('$\tau_1$ [Nm]');
title('Joint 1 torque'); grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

nexttile;
plot(t, tau_meas(:,2), 'b', 'DisplayName','measured $\tau_2$');
hold on;
plot(t, tau_model_lin(:,2), 'r--', 'DisplayName','Linear LS');
plot(t, tau_model_nls(:,2), 'g-.', 'DisplayName','NLS');
xlabel('Time $[s]$'); ylabel('$\tau_2$ [Nm]');
title('Joint 2 torque'); grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

exportgraphics(fig_tau, 'torque_comparison.png', 'Resolution', 300, 'BackgroundColor','white');


%% ===================== LOCAL FUNCTIONS =====================

function M = M_mat(theta2, a1, a2, b)
    c2 = cos(theta2);
    M = [a1 + a2 + 2*b*c2,  a2 + b*c2;
         a2 + b*c2,          a2];
end

function C = C_mat(theta2, dtheta1, dtheta2, b)
    s2 = sin(theta2);
    C = [-b*s2*dtheta2,           -b*s2*(dtheta1 + dtheta2);
          b*s2*dtheta1,            0];
end

function dx = f_dyn_2dof(x, tau, a1, a2, b, b1, b2, fc1, fc2, v_eps)
    theta2  = x(2);
    dtheta1 = x(3);
    dtheta2 = x(4);

    M = M_mat(theta2, a1, a2, b);
    C = C_mat(theta2, dtheta1, dtheta2, b);

    F_visc = [b1*dtheta1; b2*dtheta2];
    F_coul = [fc1*tanh(dtheta1/v_eps); fc2*tanh(dtheta2/v_eps)];
    tau_fric = F_visc + F_coul;

    ddq = M \ (tau - C*[dtheta1; dtheta2] - tau_fric);
    dx = [dtheta1; dtheta2; ddq(1); ddq(2)];
end

function data = dataset_to_iddata_2dof(t, q_meas, tau_meas, dt, K, F)
    N = size(q_meas, 1);

    data.t        = t(:).';
    data.q_meas   = q_meas.';
    data.tau_meas = tau_meas.';
    data.dt       = dt;

    data.q_filt   = zeros(2, N);
    data.qd_filt  = zeros(2, N);
    data.qdd_filt = zeros(2, N);

    for j = 1:2
        q_filt_j = sgolayfilt(q_meas(:,j), K, F);
        data.q_filt(j,:) = q_filt_j(:).';

        qd_raw = zeros(N,1);
        qd_raw(1) = (q_filt_j(2) - q_filt_j(1)) / dt;
        for k = 2:N-1
            qd_raw(k) = (q_filt_j(k+1) - q_filt_j(k-1)) / (2*dt);
        end
        qd_raw(N) = (q_filt_j(N) - q_filt_j(N-1)) / dt;

        qd_filt_j = sgolayfilt(qd_raw, K, F);
        data.qd_filt(j,:) = qd_filt_j(:).';

        qdd_raw = zeros(N,1);
        qdd_raw(1) = (qd_filt_j(2) - qd_filt_j(1)) / dt;
        for k = 2:N-1
            qdd_raw(k) = (qd_filt_j(k+1) - qd_filt_j(k-1)) / (2*dt);
        end
        qdd_raw(N) = (qd_filt_j(N) - qd_filt_j(N-1)) / dt;

        qdd_filt_j = sgolayfilt(qdd_raw, K, F);
        data.qdd_filt(j,:) = qdd_filt_j(:).';
    end
end

function [r, J] = residualsEL_analytic_2dof(psi, data)
    % psi = [a1; a2; bp; fc1; fc2; b1; b2; v_eps]  (8 params)
    a1    = psi(1);
    a2    = psi(2);
    bp    = psi(3);
    fc1   = psi(4);
    fc2   = psi(5);
    b1    = psi(6);
    b2    = psi(7);
    v_eps = psi(8);

    N = size(data.q_filt, 2);
    r = zeros(2*N, 1);
    J = zeros(2*N, 8);

    for k = 1:N
        q   = data.q_filt(:,k);
        qd  = data.qd_filt(:,k);
        qdd = data.qdd_filt(:,k);
        tau_m = data.tau_meas(:,k);

        qd1  = qd(1);   qd2  = qd(2);
        qdd1 = qdd(1);  qdd2 = qdd(2);

        c2 = cos(q(2));
        s2 = sin(q(2));

        M = [a1 + a2 + 2*bp*c2,  a2 + bp*c2;
             a2 + bp*c2,          a2];

        C = [-bp*s2*qd2,           -bp*s2*(qd1 + qd2);
              bp*s2*qd1,            0];

        z1 = qd1/v_eps;
        z2 = qd2/v_eps;
        F_visc = [b1*qd1; b2*qd2];
        F_coul = [fc1*tanh(z1); fc2*tanh(z2)];
        tau_f  = F_visc + F_coul;

        tau_hat = M*qdd + C*qd + tau_f;
        rk = tau_m - tau_hat;

        idx = 2*(k-1) + (1:2);
        r(idx) = rk;

        % --- Analytic Jacobian dr/dpsi = -d(tau_hat)/dpsi, size 2x8 ---
        Jk = zeros(2,8);

        % d/da1: dM/da1 = [1 0; 0 0]
        Jk(:,1) = -[qdd1; 0];

        % d/da2: dM/da2 = [1 1; 1 1]
        Jk(:,2) = -[qdd1+qdd2; qdd1+qdd2];

        % d/dbp: dM/dbp * qdd + dC/dbp * qd
        Jk(:,3) = -[2*c2*qdd1 + c2*qdd2 - s2*(2*qd1*qd2 + qd2^2);
                     c2*qdd1 + s2*qd1^2];

        % d/dfc1, d/dfc2
        Jk(1,4) = -tanh(z1);
        Jk(2,5) = -tanh(z2);

        % d/db1, d/db2
        Jk(1,6) = -qd1;
        Jk(2,7) = -qd2;

        % d/dv_eps
        sech2_z1 = 1/cosh(z1)^2;
        sech2_z2 = 1/cosh(z2)^2;
        Jk(1,8) =  fc1 * (qd1 / v_eps^2) * sech2_z1;
        Jk(2,8) =  fc2 * (qd2 / v_eps^2) * sech2_z2;

        J(idx,:) = Jk;
    end
end

function theta_hat = estimate_theta_ls_2dof(data)
    % Linear LS: theta = [a1; a2; bp; b1; b2]
    N = size(data.q_filt, 2);
    Y_stack   = zeros(2*N, 5);
    tau_stack = zeros(2*N, 1);

    for k = 1:N
        theta2 = data.q_filt(2,k);
        qd1  = data.qd_filt(1,k);
        qd2  = data.qd_filt(2,k);
        qdd1 = data.qdd_filt(1,k);
        qdd2 = data.qdd_filt(2,k);

        s2 = sin(theta2);
        c2 = cos(theta2);

        rows = (2*k-1):(2*k);

        Y_stack(rows,:) = [qdd1, qdd1+qdd2, 2*c2*qdd1+c2*qdd2-s2*(2*qd1*qd2+qd2^2),  qd1, 0;
                           0,    qdd1+qdd2, c2*qdd1+s2*qd1^2,                           0,   qd2];

        tau_stack(rows) = data.tau_meas(:,k);
    end

    fprintf('\n=== Regressor Conditioning (LS) ===\n');
    fprintf('Condition number: %.2e\n', cond(Y_stack' * Y_stack));
    fprintf('Rank: %d/%d\n', rank(Y_stack, 1e-10), size(Y_stack, 2));

    theta_hat = Y_stack \ tau_stack;
end