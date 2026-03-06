%
%% SETUP_2DSFL_ROBOT
%
% Controller Design File for Quanser's 2-DOF Serial Flexible Link (2DSFL)
% Plant.
% SETUP_2DSFL_ROBOT sets the system parameters.
% It also designs two LQR controllers to minimize both flexible link
% oscillations. A decoupled approach is used.
%
% Copyright (C) 2011 Quanser Consulting Inc.
% Quanser Consulting Inc.
%
clear all
%

dt = 0.01;

%% Watchdogs
% Turn on or off all four limit switches of the system. When enabled, it
% makes the controller stop as soon as one limit switch gets triggered.
% set it to 1 (to enable), or 0 (to disable)
LIMIT_SWITCHES_ENABLE = 1;  % all four limit switches are enabled
% LIMIT_SWITCHES_ENABLE = 0; % CAUTION: all four limit switches are disabled
% Turn on or off the safety watchdog on the oscillations of the first flexible link: 
% set it to 1 (to enable), or 0 (to disable)
% DTH1_LIM_ENABLE = 1;       % safety watchdog #1 turned ON
DTH1_LIM_ENABLE = 0;      % safety watchdog #1 turned OFF
% Safety Limits on the oscillations of the first flexible link (deg)
DTH1_MAX = 5.0;            % first flexible link maximum safety oscillation
DTH1_MIN = - DTH1_MAX;        % first flexible link minimum safety oscillation
% Turn on or off the safety watchdog on the oscillations of the second flexible link: 
% set it to 1 (to enable), or 0 (to disable)
DTH2_LIM_ENABLE = 1;       % safety watchdog #2 turned ON
% DTH2_LIM_ENABLE = 0;      % safety watchdog #2 turned OFF
% Safety Limits on the oscillations of the second flexible link (deg)
DTH2_MAX = 7.5;            % second flexible link maximum safety oscillation
DTH2_MIN = - DTH2_MAX;        % second flexible link minimum safety oscillation
%
%% System Analysis
% flag to carry out some system analysis for stage #1
SYS_ANALYSIS_1 = 'NO';
% SYS_ANALYSIS_1 = 'YES';
% flag to carry out some system analysis for stage #2
SYS_ANALYSIS_2 = 'NO';
% SYS_ANALYSIS_2 = 'YES';
%
%% Modeling
% Load 2DSLF model parameters
[L1, T1, J11, J12, B11, B12, Ks1, Ktg1, Kg1, L2, T2, J22, J21, B22, B21, Ks2, Ktg2, Kg2  ] = config_2dslf();
% Load sensor calibration gains
[K1_strain_b, K1_defl_b, K2_strain_b, K2_defl_b, KE_D1, KE_D2] = config_2dslf_sensors(L1, T1, L2, T2, Kg1, Kg2);
% For the following state vector: X1 = [ theta11; theta12; theta11_dot; theta12_dot ]
% State-Space Matrices for Stage 1: A1, B1, C1, and D1
%

%% Torque calibration parameters
%Electrical Parameters
L1 = 4.7544e-02;
R1 = 4.2737;
ke1 = 6.8470e-02;

J1 = 2.030252e-02;
B1 = 9.233265e-02;
Kt1 = 3.018583e+00;


L2 = 4.1682e-02;
R2 = 4.0151;
ke2 = 2.7453e-03;

J2 = 8.538833e-04;
B2 = 8.577738e-02;
Kt2 = 1.553175e+00;

%%Torque control gains
kp1 = 1.5;
ki1 = 0;
kd1 = 0;

kp2 = 3;
ki2 = 0;
kd2 = 0.8;

%Current saturation
i_sat1 = 0.92;
i_sat2 = 1.2;

%%EULER LAGRANGE MATRICES
m1 = 1.6537;  l1 = 0.343;  r1 = 0.29;
m2 = 0.9982;  l2 = 0.267;  r2 = 0.175;
I1_hat  = 0.014618;
I2_hat  = 0.0081;
fc1_hat = 0.146280;
fc2_hat = 0;
b1_hat  = 0.192970;
b2_hat  = 0.0248;
v_eps_hat = 0.076700;
a1_hat = m1 * r1^2 + m2 * l1^2 + I1_hat;
a2_hat = m2 * r2^2 + I2_hat;
b_hat  = m2 * l1 * r2;

kp_traj = zeros(2,2);
ki_traj = zeros(2,2);
kd_traj = zeros(2,2);

load('trajectory.mat');

N_delay = round(1/dt);   % samples in 1 second

% --- Prepend zeros in time direction ---
q   = [zeros(N_delay, size(q,2));   q(1:end-N_delay, :)];
qd  = [zeros(N_delay, size(qd,2));  qd(1:end-N_delay, :)];
qdd = [zeros(N_delay, size(qdd,2)); qdd(1:end-N_delay, :)];

% --- Original code unchanged ---
t = (0:length(q)-1)' * dt;

q_ts   = timeseries(q', t);
qd_ts  = timeseries(qd', t);
qdd_ts = timeseries(qdd', t);

function M = M_mat(theta2, a1, a2, b)
    c2 = cos(theta2);
    M = [a1 + a2 + 2*b*c2,  a2 + b*c2;
         a2 + b*c2,         a2];
end

function C = C_mat(theta2, dtheta1, dtheta2, b)
    s2 = sin(theta2);
    C = [-b*s2*dtheta2,           -b*s2*(dtheta1 + dtheta2);
          b*s2*dtheta1,            0];
end

function D = D_mat(b1, b2)
    D = [b1,0;
         0,b2];
end

%% ================================================================
%  SIMULINK SETUP GUIDE — 1DOF KPES Controller
%  ================================================================
%
%  STEP 1: Run this script BEFORE opening Simulink to load parameters
%           into the workspace.
%
%  STEP 2: Build the Simulink model as described below.
%  ================================================================

clear all; clc;

%% ===================== LOAD IDENTIFIED PARAMETERS =====================
% Replace with your actual values from identify_1dof.m
I_hat     = 0.039;       % identified inertia
b_hat     = 0.02;        % identified viscous damping
fc_hat    = 0.0;         % Coulomb friction (NOT used in controller)
v_eps_hat = 0.05;        % (NOT used in controller)

%% ===================== DERIVED CONSTANTS =====================
T_val   = 1 / sqrt(I_hat);
Ti_val  = sqrt(I_hat);
D_tilde = b_hat / I_hat;
G_tilde = 1 / sqrt(I_hat);

%% ===================== CONTROLLER GAINS =====================
alpha = 0.2;
Kp    = 6;
Kd    = 10;

%% ===================== OBSERVER =====================
kappa   = 0.1;
phi     = kappa * Ti_val + 0.01;   % constant — no jumps for 1DOF
xp_init = 0;                       % initial observer state

%% ===================== MOTOR =====================
Kt1 = 3.018583;          % torque constant [Nm/A]

%% ===================== SIMULATION =====================
dt = 0.001;               % fixed-step sample time


%
%  KEY NOTES:
%
%  1. The MATLAB Function block should contain the function below.
%     All parameters (I_hat, b_hat, alpha, Kp, Kd, phi, etc.) can
%     be hardcoded inside, OR passed from workspace using the
%     "Parameter" tab in the MATLAB Function block editor.
%
%  2. The Unit Delay block:
%        - Sample time: dt (e.g. 0.001)
%        - Initial condition: 0 (xp_init)
%
%  3. Fixed-step solver (e.g. ode4 or discrete) with step size = dt.
%
%  4. Coulomb friction is NOT modeled in the controller — it acts
%     as a disturbance that the KPES feedback naturally rejects
%     (passivity-based robustness).
%
%  ================================================================

%% ================================================================
%  MATLAB FUNCTION BLOCK CODE — copy this into the block
%  ================================================================
%
%  function [tau_cmd, xp_next, uo] = fcn(q_meas, qd, dqd, ddqd, xp_prev)
%
%      % --- Identified parameters ---
%      I_hat = 0.039;
%      b_hat = 0.02;
%
%      % --- Derived ---
%      T_val   = 1 / sqrt(I_hat);
%      Ti_val  = sqrt(I_hat);
%      D_tilde = b_hat / I_hat;
%      G_tilde = 1 / sqrt(I_hat);
%      Gi      = 1 / G_tilde;           % = sqrt(I_hat)
%
%      % --- Gains ---
%      alpha = 0.2;
%      Kp    = 6;
%      Kd    = 10;
%
%      % --- Observer (constant phi for 1DOF) ---
%      kappa = 0.1;
%      phi   = kappa * Ti_val + 0.01;
%      dt    = 0.001;                    % must match solver step
%
%      % --- Momentum estimate ---
%      phat = xp_prev + phi * q_meas;
%
%      % --- Desired transformed momentum ---
%      pd = Ti_val * dqd;
%
%      % --- Errors ---
%      qe = q_meas - qd;
%      pe = phat - pd;
%      z  = qe + alpha * pe;
%
%      % --- KPES feedback (S=0 for constant M) ---
%      v = -alpha*(D_tilde + Kd)*Kp*z - T_val*Kp*z - Kd*pe;
%
%      % --- Passive output & interconnection ---
%      dHe_dqe = Kp * z;
%      dHe_dpe = pe + alpha * Kp * z;
%      ye = -T_val * (dHe_dqe + phi * dHe_dpe);
%      uo = -Gi * ye;
%
%      % --- Feedforward (S=0, gradV=0, dpd/dq=0) ---
%      u_ff = Gi * (D_tilde*pd + Ti_val*ddqd + v);
%
%      % --- Total ---
%      tau_cmd = -uo + u_ff;
%
%      % --- Observer update (Euler integration) ---
%      dxp = -(D_tilde + phi*T_val)*phat + G_tilde*(tau_cmd + uo);
%      xp_next = xp_prev + dt * dxp;
%
%  end
%
%  ================================================================


