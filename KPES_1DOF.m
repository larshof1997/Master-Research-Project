%% ================================================================
%  1DOF KPES Controller with Momentum Observer
%  Adapted from 2DOF code — see simplifications noted throughout
%  ================================================================
%
%  Model:  I*qdd + b*qd = tau   (friction absorbed into damping)
%
%  For 1DOF with CONSTANT M = I:
%    T  = 1/sqrt(I),  Ti = sqrt(I)
%    S  = 0           (because dM/dq = 0)
%    Sbar = 0
%    D_tilde = T*b*T = b/I
%    G_tilde = T*1   = 1/sqrt(I)
%    dpd/dq  = 0     (because M is constant)
%    gradV   = 0     (no gravity)
%
%  Observer jump condition simplifies to: phi/sqrt(I) >= kappa
%  which is satisfied once and never needs to jump again.
%  ================================================================

clear all; clc; close all;

%% ===================== IDENTIFIED PARAMETERS =====================
% Replace these with your actual identified values
I_hat = 0.039;       % [kg m^2] identified inertia
b_hat = 0.02;        % [Nm s/rad] identified viscous damping
% NOTE: Coulomb friction (fc, v_eps) is NOT in the controller model.
%       It acts as an unmodeled disturbance that the feedback rejects.

%% ===================== DERIVED CONSTANTS =====================
T_val  = 1 / sqrt(I_hat);       % transformation scalar
Ti_val = sqrt(I_hat);            % inverse transformation
D_tilde = b_hat / I_hat;        % transformed damping
G_tilde = 1 / sqrt(I_hat);      % transformed input gain

%% ===================== CONTROLLER PARAMETERS =====================
alpha = 0.2;         % interconnection gain
Kp    = 6;           % position error gain (scalar)
Kd    = 10;          % momentum error gain (scalar)

%% ===================== OBSERVER PARAMETERS =====================
kappa = 0.1;

% For constant M, the jump condition is: phi*T >= kappa
% So we need phi >= kappa / T = kappa * sqrt(I).
% Initialize phi to satisfy this directly — no runtime jumps needed.
phi_init = kappa * Ti_val + 0.01;   % slightly above threshold

%% ===================== TIME & TRAJECTORY =====================
dt    = 0.001;       % match your Simulink sample time
t_end = 3;
t = (0:dt:t_end)';
N = numel(t);

% Load your desired trajectory (1DOF column from trajectory1.mat)
% S_traj = load('DATA_1DOF/trajectory1.mat');
% joint_idx = 1;
% qd_traj   = S_traj.q(:,joint_idx);
% dqd_traj  = S_traj.qd(:,joint_idx);
% ddqd_traj = S_traj.qdd(:,joint_idx);

% Placeholder sinusoidal trajectory for testing
qd_traj   = sin(2*pi*0.5*t);
dqd_traj  = 2*pi*0.5*cos(2*pi*0.5*t);
ddqd_traj = -(2*pi*0.5)^2*sin(2*pi*0.5*t);

%% ===================== SIMULATION =====================
% State: x = [q; dq]
x_sim  = zeros(N, 2);
x_sim(1,:) = [0.5, 0];   % initial condition (away from trajectory)

% Observer state
xp  = 0;
phi = phi_init;

% Logging
u_log   = zeros(N, 1);
qe_log  = zeros(N, 1);
pe_log  = zeros(N, 1);
phat_log = zeros(N, 1);

for k = 1:N-1
    % --- Current state ---
    q_k  = x_sim(k, 1);
    dq_k = x_sim(k, 2);

    % --- Observer: estimate transformed momentum from position ---
    phat_k = xp + phi * q_k;           % scalar

    % Jump check (should not trigger if phi_init is set correctly)
    while (phi * T_val - kappa) <= 0
        xp  = xp - kappa * q_k;
        phi = phi + kappa;
        phat_k = xp + phi * q_k;
    end

    % --- Desired trajectory at step k ---
    qd_k   = qd_traj(k);
    dqd_k  = dqd_traj(k);
    ddqd_k = ddqd_traj(k);

    % --- Desired transformed momentum ---
    pd_k = Ti_val * dqd_k;             % sqrt(I) * dqd

    % --- Error coordinates ---
    qe_k = q_k - qd_k;
    pe_k = phat_k - pd_k;
    z_k  = qe_k + alpha * pe_k;

    % --- KPES feedback (S=0 for 1DOF constant M) ---
    %  v = alpha*(S - D_tilde - Kd)*Kp*z - T*Kp*z - Kd*pe
    %  v = -alpha*(D_tilde + Kd)*Kp*z - T*Kp*z - Kd*pe
    v_k = -alpha * (D_tilde + Kd) * Kp * z_k ...
          - T_val * Kp * z_k ...
          - Kd * pe_k;

    % --- Passive output ---
    %  dHe/dqe = Kp * z
    %  dHe/dpe = pe + alpha*Kp*z
    %  ye = -T * (dHe_dqe + phi * dHe_dpe)   [since dpd/dq = 0]
    dHe_dqe = Kp * z_k;
    dHe_dpe = pe_k + alpha * Kp * z_k;
    ye_k = -T_val * (dHe_dqe + phi * dHe_dpe);

    % --- Passive interconnection ---
    uo_k = -ye_k / G_tilde;            % -G_tilde^{-1} * ye

    % --- Feedforward ---
    %  u_ff = G_tilde^{-1} * (D_tilde*pd + Ti*ddqd + v)
    %  [since S=0, gradV=0, dpd/dq=0]
    u_ff = (1/G_tilde) * (D_tilde * pd_k + Ti_val * ddqd_k + v_k);

    % --- Total control ---
    u_k = -uo_k + u_ff;
    u_log(k) = u_k;

    % --- Observer flow (RK4) ---
    %  dxp = -(D_tilde + phi*T)*phat - T*gradV + G_tilde*(u + uo)
    %  dxp = -(D_tilde + phi*T)*phat + G_tilde*(u + uo)   [gradV=0]
    obs_rhs = @(xp_) -(D_tilde + phi*T_val) * (xp_ + phi*q_k) ...
                      + G_tilde * (u_k + uo_k);

    ok1 = obs_rhs(xp);
    ok2 = obs_rhs(xp + 0.5*dt*ok1);
    ok3 = obs_rhs(xp + 0.5*dt*ok2);
    ok4 = obs_rhs(xp + dt*ok3);
    xp = xp + (dt/6)*(ok1 + 2*ok2 + 2*ok3 + ok4);

    % --- Plant dynamics (RK4) ---
    %  I*qdd + b*qd = u  =>  qdd = (u - b*qd) / I
    plant_rhs = @(x_) [x_(2); (u_k - b_hat*x_(2)) / I_hat];

    pk1 = plant_rhs(x_sim(k,:)');
    pk2 = plant_rhs(x_sim(k,:)' + 0.5*dt*pk1);
    pk3 = plant_rhs(x_sim(k,:)' + 0.5*dt*pk2);
    pk4 = plant_rhs(x_sim(k,:)' + dt*pk3);
    x_sim(k+1,:) = x_sim(k,:) + (dt/6)*(pk1 + 2*pk2 + 2*pk3 + pk4)';

    % --- Store ---
    phat_log(k) = phat_k;
    qe_log(k)   = qe_k;
    pe_log(k)    = pe_k;
end

%% ===================== PLOTS =====================
set(groot,'defaultTextInterpreter','latex');
set(groot,'defaultAxesTickLabelInterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');

figure('Color','w');
subplot(3,1,1); hold on; grid on;
plot(t, x_sim(:,1), 'b', 'LineWidth',1.5);
plot(t, qd_traj, 'r--', 'LineWidth',1.2);
ylabel('$q$ [rad]'); legend('actual','desired');
title('Position tracking');

subplot(3,1,2); hold on; grid on;
semilogy(t, abs(qe_log), 'b', 'LineWidth',1.2);
ylabel('$|q_e|$'); title('Tracking error (log scale)');

subplot(3,1,3); hold on; grid on;
plot(t, u_log, 'b', 'LineWidth',1.2);
ylabel('$\tau$ [Nm]'); xlabel('Time [s]');
title('Control torque');


%% ================================================================
%  SIMULINK IMPLEMENTATION
%  ================================================================
%
%  ARCHITECTURE (all blocks are MATLAB Function blocks):
%
%  ┌──────────────┐
%  │  Trajectory   │──> qd, dqd, ddqd
%  │  (From WS)    │
%  └──────────────┘
%           │
%           v
%  ┌──────────────────────────────────────────────────┐
%  │              KPES Controller Block                │
%  │                                                   │
%  │  Inputs:  q_meas, qd, dqd, ddqd, xp, phi        │
%  │  Outputs: tau_cmd, xp_next, uo                    │
%  │                                                   │
%  └──────────────────────────────────────────────────┘
%           │
%           v
%  ┌──────────────┐
%  │  tau_cmd / Kt │──> current command to motor
%  └──────────────┘
%
%  Observer state (xp) is fed back via Unit Delay (z^{-1}).
%  phi is constant after initialization (no jumps needed for 1DOF).
%
%  ================================================================


%% ================================================================
%  SIMULINK MATLAB FUNCTION BLOCKS
%  Copy each function below into a separate MATLAB Function block
%  ================================================================

%% --- Block 1: KPES_controller_1dof ---
%  Inputs:  q_meas (scalar), qd (scalar), dqd (scalar), ddqd (scalar),
%           xp_prev (scalar from Unit Delay)
%  Outputs: tau_cmd (scalar), xp_next (scalar), uo (scalar)

function [tau_cmd, xp_next, uo] = KPES_controller_1dof(q_meas, qd, dqd, ddqd, xp_prev, dt)
    % --- Identified parameters (EDIT THESE) ---
    I_hat = 0.039;
    b_hat = 0.02;

    % --- Derived constants ---
    T_val   = 1 / sqrt(I_hat);
    Ti_val  = sqrt(I_hat);
    D_tilde = b_hat / I_hat;
    G_tilde = 1 / sqrt(I_hat);

    % --- Controller gains (EDIT THESE) ---
    alpha = 0.2;
    Kp    = 6;
    Kd    = 10;

    % --- Observer ---
    kappa = 0.1;
    phi   = kappa * Ti_val + 0.01;    % constant for 1DOF

    % Estimated transformed momentum
    phat = xp_prev + phi * q_meas;

    % Desired transformed momentum
    pd = Ti_val * dqd;

    % --- Errors ---
    qe = q_meas - qd;
    pe = phat - pd;
    z  = qe + alpha * pe;

    % --- KPES feedback (S=0) ---
    v = -alpha * (D_tilde + Kd) * Kp * z ...
        - T_val * Kp * z ...
        - Kd * pe;

    % --- Passive output ---
    dHe_dqe = Kp * z;
    dHe_dpe = pe + alpha * Kp * z;
    ye = -T_val * (dHe_dqe + phi * dHe_dpe);

    % --- Passive interconnection ---
    uo = -ye / G_tilde;

    % --- Feedforward ---
    u_ff = (1/G_tilde) * (D_tilde * pd + Ti_val * ddqd + v);

    % --- Total control ---
    tau_cmd = -uo + u_ff;

    % --- Observer update (Euler for Simulink, or use RK4 subsystem) ---
    dxp = -(D_tilde + phi * T_val) * phat + G_tilde * (tau_cmd + uo);
    xp_next = xp_prev + dt * dxp;
end


%% --- Block 2: Feedforward only (for comparison / debugging) ---
function tau_ff = feedforward_1dof(dqd, ddqd)
    I_hat = 0.039;
    b_hat = 0.02;
    tau_ff = I_hat * ddqd + b_hat * dqd;
end


%% --- Block 3: Convert torque to current ---
function i_cmd = torque_to_current(tau_cmd)
    Kt1 = 3.018583;
    i_cmd = tau_cmd / Kt1;
end