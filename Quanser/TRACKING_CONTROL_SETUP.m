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
% ke1 = 0;

J1 = 2.030252e-02;
B1 = 9.233265e-02;
Kt1 = 3.018583e+00;


L2 = 4.8190e-02;
R2 = 4.0364e+00;
ke2 = 7.9830e-03;
% ke2 = 0;

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

t_end = 120;
n_pad = round(sleep/dt);
t = (0:dt:t_end)';

%control input perubation
a = 1;
a1 = a;
a2 = a;
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
P1_cruz = 0.7;
P2_cruz = 0.4;
D1_cruz = 0.1; 
D2_cruz = 0.04;
A_f_cruz  = 2 * eye(2);
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




% %% ===================== Rascón gain condition check =====================
% % Conditions from Rascón et al. 2020, Eqs. (17)-(27)
% 
% %% ---------- Bounds from identified EL model ----------
% q2_range = linspace(-pi, pi, 1000);
% lam_max_M = 0; lam_min_M = inf;
% 
% for k = 1:length(q2_range)
%     Mk = M_mat(q2_range(k), a1_hat, a2_hat, b_hat);
%     ev = eig(Mk);
%     lam_max_M = max(lam_max_M, max(ev));
%     lam_min_M = min(lam_min_M, min(ev));
% end
% 
% % Coriolis bound: ||C(q, a)b|| <= kc1 * ||a|| * ||b||
% % Compute numerically by maximizing ||C(q, a)|| / ||a|| over q2 and a
% kc1 = 0;
% for q2 = linspace(-pi, pi, 500)
%     for th = linspace(0, 2*pi, 500)
%         a_vec = [cos(th); sin(th)];  % unit vector
%         Ck = C_mat(q2, a_vec(1), a_vec(2), b_hat);
%         kc1 = max(kc1, norm(Ck, 2));  % induced 2-norm
%     end
% end
% fprintf('kc1 = %.6f  (conservative: %.6f)\n', kc1, 2*abs(b_hat));
% % Mdot, Mddot bounds
% qdot_max  = 5.0;
% qddot_max = 20.0;
% lam_max_Mdot  = 2*abs(b_hat) * qdot_max;
% lam_max_Mddot = 2*abs(b_hat) * (qdot_max^2 + qddot_max);
% 
% % Friction and disturbance
% Fv_diag = [b1_hat; b2_hat];
% Fc_diag = [0; 0];              % no Coulomb friction identified
% omega_bnd = 0.1;               % disturbance bound (includes unmodeled friction)
% qd_dot_bnd = max(vecnorm(dqd, 2, 2));
% 
% % Aggregate uncertainty
% beta = max(Fv_diag)*qd_dot_bnd + max(Fc_diag) + omega_bnd;
% 
% %% ---------- Candidate gains ----------
% K1_R = diag([5, 3]);
% K2_R = diag([10, 8]);
% Delta_R = diag([1, 1]);
% 
% k1d = diag(K1_R); k2d = diag(K2_R); dd = diag(Delta_R);
% 
% %% ---------- Check conditions ----------
% % V > 0
% c_V1 = min(k1d) > max(dd);
% c_V2 = (min(k2d)+min(Fv_diag)) > (0.5*lam_max_Mdot + lam_max_M^2/lam_min_M);
% 
% % Vdot < 0: R matrix (Eq. 27)
% R11 = - 0.25*lam_max_Mddot+min(eig(K2_R));
% R22 = min(Fv_diag) - 2*kc1*qd_dot_bnd - lam_max_M;
% R12 = -kc1*qd_dot_bnd;
% detR = R11*R22 - R12^2;
% 
% c1 = R11 > 0;
% c2 = detR > 0;
% c3 = min(k1d) > beta;
% c4 = min(dd)  > beta;
% 
% fprintf('\n=== Rascón gain conditions ===\n');
% fprintf('V>0:  lmin(K1)>lmax(D):     %.3f > %.3f  %s\n', min(k1d), max(dd), ps(c_V1));
% fprintf('V>0:  lmin(K2)+lmin(Fv)>..  %.3f > %.3f  %s\n', min(k2d)+min(Fv_diag), 0.5*lam_max_Mdot+lam_max_M^2/lam_min_M, ps(c_V2));
% fprintf('Vd:   R11>0:                %.3f          %s\n', R11, ps(c1));
% fprintf('Vd:   R22:                  %.3f          (need >0)\n', R22);
% fprintf('Vd:   det(R)>0:             %.3f          %s\n', detR, ps(c2));
% fprintf('Vd:   lmin(K1)>beta:        %.3f > %.3f  %s\n', min(k1d), beta, ps(c3));
% fprintf('Vd:   lmin(Delta)>beta:     %.3f > %.3f  %s\n', min(dd), beta, ps(c4));
% 
% %% ---------- R22 feasibility ----------
% % R22 = lmin(Fv) - 2*kc1*||dqd|| - lmax(M)
% % Even at ||dqd||=0: R22 = lmin(Fv) - lmax(M)
% R22_static = min(Fv_diag) - lam_max_M;
% if R22_static < 0
%     fprintf('\nR22 < 0 even for stationary references (regulation).\n');
%     fprintf('  lmin(Fv)=%.4f < lmax(M)=%.4f\n', min(Fv_diag), lam_max_M);
%     fprintf('  Lyapunov proof inapplicable to this plant.\n');
% else
%     qd_dot_crit = (min(Fv_diag) - lam_max_M) / (2*kc1);
%     fprintf('\nMax ||dqd|| for R22>0: %.4f rad/s\n', qd_dot_crit);
% end
% 
% fprintf('\n--- Minimum gains (where feasible) ---\n');
% fprintf('K1 > %.4f,  Delta > %.4f\n', beta, beta);
% fprintf('K2 > %.4f  (from Vdot R11)\n', 0.25*lam_max_Mddot);
% fprintf('K2 > %.4f  (from V>0)\n', 0.5*lam_max_Mdot + lam_max_M^2/lam_min_M - min(Fv_diag));
% 
% function s = ps(b), if b, s='PASS'; else, s='FAIL'; end, end