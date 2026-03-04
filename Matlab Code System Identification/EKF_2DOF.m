%% EKF joint + parameter estimation for 2-DOF Quanser manipulator
clear; clc; close all;

%% ===================== USER SETTINGS =====================
Kt1 = 3.018583e+00;          % torque constant joint 1 [Nm/A]
Kt2 = 1.111065;              % torque constant joint 2 [Nm/A]

% Physical constants (KNOWN)
m1 = 1.6537;  l1 = 0.343;  r1 = 0.29;
m2 = 0.9982;  l2 = 0.267;  r2 = 0.175;
bp = m2 * l1 * r2;

% Motor-side parameters (KNOWN from DC motor calibration)
J1_motor = 0.0;   % <-- rotor inertia joint 1 [kg m^2]
J2_motor = 0.0;   % <-- rotor inertia joint 2 [kg m^2]
B1_motor = 0.0;   % <-- rotor viscous friction joint 1 [Nm s/rad]
B2_motor = 0.0;   % <-- rotor viscous friction joint 2 [Nm s/rad]

% Savitzky-Golay filter parameters (for motor dynamics subtraction)
F = 61;
K = 2;

%% ===================== LOAD & PREPARE DATA =====================
S_traj = load('DATA_2DOF/trajectory1.mat');
q_des   = S_traj.q;
qd_des  = S_traj.qd;
qdd_des = S_traj.qdd;

S_res1 = load('DATA_2DOF/shoulder3.mat');
S_res1 = S_res1.torque_control_data_shoulder;
S_res1 = S_res1(1:end-1, :);

S_res2 = load('DATA_2DOF/elbow3.mat');
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

tau_motor = [Kt1 * actual_current_1, Kt2 * actual_current_2];
q_meas    = [q_meas_1, q_meas_2];

%% ===================== SUBTRACT MOTOR DYNAMICS =====================
% Need filtered qd, qdd for motor dynamics subtraction
data_filt = dataset_to_iddata_2dof(t, q_meas, tau_motor, dt, K, F);

tau_load = tau_motor;
tau_load(:,1) = tau_motor(:,1) - J1_motor * data_filt.qdd_filt(1,:).' - B1_motor * data_filt.qd_filt(1,:).';
tau_load(:,2) = tau_motor(:,2) - J2_motor * data_filt.qdd_filt(2,:).' - B2_motor * data_filt.qd_filt(2,:).';

% Use tau_load as the applied torque for EKF
u = tau_load;   % Nx2

%% ===================== EKF SETUP =====================
% State: x = [q1; q2; dq1; dq2; I1; I2; fc1; fc2; b1; b2; v_eps]
nx = 12;

% Initial parameter guess (from NLS or LS)
psi0 = [0.025; 0.005; 0; 0.15; 0.12; 0.23; 0.09; 0.03];

% Parameter bounds (for clamping)
lb_psi = [1e-3; 1e-3; 1e-3; 0; 0; 0; 0; 1e-4];
ub_psi = [0.5; 0.1; 0.5; 0.5; 0.5; 0.5; 0.5; 0.1];

% Initial state: measured positions, zero velocity, psi0
x0 = [q_meas(1,1); q_meas(1,2); 0; 0; psi0];

% Initial covariance
P0 = blkdiag(1e-4*eye(2), ...    % position (well-known from encoder)
             1e-2*eye(2), ...    % velocity (unknown)
             1e-2*eye(nx-4));       % parameters (uncertain)

% Process noise Q
Q = blkdiag(1e-6*eye(2), ...    % position process noise
            1e-4*eye(2), ...    % velocity process noise
            1e-8*eye(nx-4));       % parameter random walk

% Measurement noise R (position-only measurement)
% Encoder resolution ~ 1e-4 rad
sigma_q = 1e-3;   % <-- TUNE: measurement noise std [rad]
R = sigma_q^2 * eye(2);

% Measurement matrix: we only measure [q1; q2]
H = [eye(2), zeros(2, nx-2)];   % 2x11

%% ===================== RUN EKF =====================
x_hat = zeros(nx, N);
P_store = zeros(nx, N);   % store diagonal of P for plotting

x_hat(:,1) = x0;
P = P0;
P_store(:,1) = diag(P);

for k = 1:N-1
    uk = u(k,:).';

    % --- Prediction ---
    [x_pred, Fk] = f_discrete_state(x_hat(:,k), uk, dt);
    P_pred = Fk * P * Fk' + Q;

    % --- Measurement update (use measurement at k+1) ---
    z = [q_meas(k+1,1); q_meas(k+1,2)];
    z_hat = H * x_pred;

    S_k = H * P_pred * H' + R;
    K_gain = P_pred * H' / S_k;

    x_upd = x_pred + K_gain * (z - z_hat);
    P = (eye(nx) - K_gain * H) * P_pred;

    % --- Clamp parameters to bounds ---
    psi_k = x_upd(5:end);
    psi_k = max(lb_psi, min(ub_psi, psi_k));
    x_upd(5:end) = psi_k;

    % --- Store ---
    x_hat(:,k+1) = x_upd;
    P_store(:,k+1) = diag(P);
end

%% ===================== RESULTS =====================
psi_hat_ekf = x_hat(5:end, end);

fprintf('\n===== EKF Parameter Estimates (final) =====\n');
fprintf('  a1    = %.6f  [kg m^2]\n',   psi_hat_ekf(1));
fprintf('  a2    = %.6f  [kg m^2]\n',   psi_hat_ekf(2));
fprintf('  bp    = %.6f  [kg m^2]\n',   psi_hat_ekf(3));
fprintf('  fc1   = %.6f  [Nm]\n',       psi_hat_ekf(4));
fprintf('  fc2   = %.6f  [Nm]\n',       psi_hat_ekf(5));
fprintf('  b1    = %.6f  [Nm s/rad]\n', psi_hat_ekf(6));
fprintf('  b2    = %.6f  [Nm s/rad]\n', psi_hat_ekf(7));
fprintf('  v_eps = %.6f  [rad/s]\n',    psi_hat_ekf(8));

%% ===================== MSE (vs filtered measurements) =====================
e_q1  = q_meas(:,1) - x_hat(1,:).';
e_q2  = q_meas(:,2) - x_hat(2,:).';
e_qd1 = data_filt.qd_filt(1,:).' - x_hat(3,:).';
e_qd2 = data_filt.qd_filt(2,:).' - x_hat(4,:).';

fprintf('\n===== EKF State MSE =====\n');
fprintf('  MSE q1  : %.6e\n', mean(e_q1.^2));
fprintf('  MSE q2  : %.6e\n', mean(e_q2.^2));
fprintf('  MSE dq1 : %.6e\n', mean(e_qd1.^2));
fprintf('  MSE dq2 : %.6e\n', mean(e_qd2.^2));

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
plot(t, x_hat(1,:), 'r--', 'DisplayName','EKF');
xlabel('Time $[s]$'); ylabel('$\theta_1$ [rad]');
title('Joint 1 angle'); grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

nexttile;
plot(t, q_meas(:,2), 'b', 'DisplayName','measured');
hold on;
plot(t, x_hat(2,:), 'r--', 'DisplayName','EKF');
xlabel('Time $[s]$'); ylabel('$\theta_2$ [rad]');
title('Joint 2 angle'); grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

exportgraphics(fig_ang, 'ekf_joint_angles.png', 'Resolution', 300, 'BackgroundColor','white');

%% ---------- Joint velocities ----------
fig_vel = figure('Color','w', 'Position',[250 250 900 500]);
tiledlayout(2,1, 'Padding','compact', 'TileSpacing','compact');

nexttile;
plot(t, data_filt.qd_filt(1,:), 'b', 'DisplayName','filtered meas.');
hold on;
plot(t, x_hat(3,:), 'r--', 'DisplayName','EKF');
xlabel('Time $[s]$'); ylabel('$\dot{\theta}_1$ [rad/s]');
title('Joint 1 velocity'); grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

nexttile;
plot(t, data_filt.qd_filt(2,:), 'b', 'DisplayName','filtered meas.');
hold on;
plot(t, x_hat(4,:), 'r--', 'DisplayName','EKF');
xlabel('Time $[s]$'); ylabel('$\dot{\theta}_2$ [rad/s]');
title('Joint 2 velocity'); grid on; box on;
legend('Location','best', 'FontSize', defaultFontSize-2);

exportgraphics(fig_vel, 'ekf_joint_velocities.png', 'Resolution', 300, 'BackgroundColor','white');

%% ---------- Parameter convergence ----------
psi_names = {'$I_1$','$I_2$','$f_{c1}$','$f_{c2}$','$b_1$','$b_2$','$v_\varepsilon$'};
psi_units = {'[kg m$^2$]','[kg m$^2$]','[Nm]','[Nm]','[Nm s/rad]','[Nm s/rad]','[rad/s]'};

fig_psi = figure('Color','w', 'Position',[300 100 1000 800]);
tiledlayout(4,2, 'Padding','compact', 'TileSpacing','compact');

for i = 1:7
    nexttile;
    plot(t, x_hat(4+i,:), 'r', 'LineWidth', 1.5);
    hold on;
    % Plot 2-sigma envelope
    sig_i = sqrt(P_store(4+i,:));
    fill([t; flipud(t)], ...
         [x_hat(4+i,:).'+2*sig_i.'; flipud(x_hat(4+i,:).'-2*sig_i.')], ...
         'r', 'FaceAlpha', 0.15, 'EdgeColor','none', 'HandleVisibility','off');
    xlabel('Time $[s]$');
    ylabel([psi_names{i}, ' ', psi_units{i}]);
    grid on; box on;
    title(['Parameter ', psi_names{i}]);
end

exportgraphics(fig_psi, 'ekf_parameters.png', 'Resolution', 300, 'BackgroundColor','white');


%% ===================== LOCAL FUNCTIONS =====================

function [x_next, Fk] = f_discrete_state(x, u, dt)
    f = f_cont_state(x, u);
    x_next = x + dt * f;

    A = numJacobian(@(xx) f_cont_state(xx, u), x);
    Fk = eye(numel(x)) + dt * A;
end

function dx = f_cont_state(x, u)
    q   = x(1:2);
    qd  = x(3:4);
    psi = x(5:end);

    a1    = psi(1);
    a2    = psi(2);
    bp    = psi(3);
    fc1   = psi(4);
    fc2   = psi(5);
    b1    = psi(6);
    b2    = psi(7);
    v_eps = psi(8);

    theta2  = q(2);
    c2 = cos(theta2);
    s2 = sin(theta2);

    M = [a1 + a2 + 2*bp*c2,  a2 + bp*c2;
         a2 + bp*c2,          a2];

    C = [-bp*s2*qd(2),           -bp*s2*(qd(1) + qd(2));
          bp*s2*qd(1),            0];

    z1 = qd(1)/v_eps;
    z2 = qd(2)/v_eps;
    tau_f = [b1*qd(1) + fc1*tanh(z1);
             b2*qd(2) + fc2*tanh(z2)];

    ddq = M \ (u - C*qd - tau_f);

    dx = zeros(size(x));
    dx(1:2) = qd;
    dx(3:4) = ddq;
    % parameters: random walk (dpsi/dt = 0)
end

function A = numJacobian(f, x)
    n  = numel(x);
    f0 = f(x);
    m  = numel(f0);
    A  = zeros(m, n);

    epsRel = 1e-6;
    epsAbs = 1e-8;

    for j = 1:n
        h = epsRel * max(1, abs(x(j))) + epsAbs;
        xj = x;
        xj(j) = xj(j) + h;
        fj = f(xj);
        A(:,j) = (fj - f0) / h;
    end
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