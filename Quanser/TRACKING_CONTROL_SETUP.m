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

dt = 0.001;

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


L2 = 4.8190e-02;
R2 = 4.0364e+00;
ke2 = 7.9830e-03;

J2 = 6.530040e-04;
B2 = 4.505757e-02;
Kt2 = 1.111065;

%%Torque control gains
kp1 = 2;
ki1 = 0;
kd1 = 0;

kp2 = 0.5;
ki2 = 0;
kd2 = 0;

%Current saturation
i_sat1 = 0.92;
i_sat2 = 1.2;

%%EULER LAGRANGE MATRICES
% m1 = 1.6537;  l1 = 0.343;  r1 = 0.29;
% m2 = 0.9982;  l2 = 0.267;  r2 = 0.175;
% I1_hat  = 0.017859;
% I2_hat  = 0.020765;
b1_hat  = 0.396193;
b2_hat  = 0.195026;
a1_hat = 0.092202;
a2_hat = 0.023242;
b_hat  = 0.027542;

kp_traj = zeros(2,2);
ki_traj = zeros(2,2);
kd_traj = zeros(2,2);

%% Load desired trajectory 
sleep = 2;

t_end = 10;
n_pad = round(sleep/dt);
t = (0:dt:t_end)';

%control input perubation
a1 = 0;
a2 = 0;
f=2;
u_pert   = [a1*sin(2*pi*f*t), a2*sin(2*pi*f*t)];

qd   = [sin(t), cos(2*t)];
dqd  = [cos(t), -2*sin(2*t)];
ddqd = [-sin(t), -4*cos(2*t)];

u_pert   = [zeros(n_pad, 2); u_pert];
qd   = [zeros(n_pad, 2); qd];
dqd  = [zeros(n_pad, 2); dqd];
ddqd = [zeros(n_pad, 2); ddqd];

N = length(qd);
t = (0:dt:t_end + sleep)';

u_pert_ts   = timeseries(u_pert, t);
qd_ts   = timeseries(qd, t);
dqd_ts  = timeseries(dqd, t);
ddqd_ts = timeseries(ddqd, t);


%% KPES Controller parameters
alpha = 0.1827;
Kp = 1.7373 * eye(2);
Kd = diag([12,5]);


% Observer parameters
kappa = 0.8564;
% Observer initial conditions
xp  = [0 0];
phi = 0;

%% Cruz 2021 controller parameters
P1_cruz = 6.46;
P2_cruz = 1.72;
D1_cruz = 3.83; 
D2_cruz = 0.88;
A_f_cruz  = 7.36 * eye(2);
r1_cruz = 1.50;



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



