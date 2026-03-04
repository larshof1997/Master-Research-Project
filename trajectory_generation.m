%% GENERATE_ALL_TRAJECTORIES
%  Complete trajectory set for IDIM-OLS / NLS identification of the
%  Quanser 2DSFLE (2-DOF planar manipulator with harmonic drives).
%
%  Parameter vector (consistent with residualsEL_analytic_2dof):
%    psi = [a1, a2, bp, fc1, fc2, b1, b2]   (7 linear params)
%    v_eps is treated as fixed hyperparameter in the regressor.
%
%  TRAINING TRAJECTORIES (10):
%    1.  Fourier-optimised    (T=30s,  Nf=9)
%    2.  Fourier-optimised    (T=15s,  Nf=5  — faster fundamental)
%    3.  Fourier-optimised    (T=45s,  Nf=12 — richer low-freq)
%    4.  Fourier-optimised    (T=20s,  Nf=7  — mid-range)
%    5.  Fourier-optimised    (T=60s,  Nf=15 — very low fundamental)
%    6.  Chirp freq sweep     (0.01–3 Hz, 60s)
%    7.  Constant-velocity    (Coulomb / Stribeck friction)
%    8.  Fast sinusoidal      (multi-amplitude, max 3 Hz, 30s)
%    9.  Slow full-range      (±70° sweep, 80s)
%   10.  Step-staircase       (filtered position steps, 50s)
%
%  TESTING TRAJECTORIES (2):
%   11.  Lissajous AM         (amplitude-modulated, 40s)
%   12.  Fourier-optimised    (T=25s, Nf=8 — unseen during training)
%
%  All trajectories start/end at q = [0, 0] and respect joint limits.

clear; clc; close all;

%% ====================================================================
%  1. GLOBAL SETTINGS
%  ====================================================================
Ts = 0.01;                         % sample time [s]

% Joint limits  [joint1; joint2]
%   J1: Maxon 273759 + HD 100:1    J2: Maxon 118752 + HD 50:1
q_max   = deg2rad([70; 70]);       % [rad]
qd_max  = deg2rad([90; 300]);      % [rad/s]
qdd_max = deg2rad([600; 400]);     % [rad/s^2]

% Design margin (95 % of hard limits for non-Fourier trajectories)
margin = 0.95;
q_lim   = margin * q_max;
qd_lim  = margin * qd_max;
qdd_lim = margin * qdd_max;

v_eps = 0.1;        % tanh smoothing for Coulomb (fixed in regressor)
l1    = 0.3493;     % link-1 length [m]

% --- Fourier optimiser settings ---
run_fourier_opt = false;    % false -> try to load from disk
N_restarts      = 5;       % multi-start restarts per trajectory
use_Dopt        = false;   % false = condition number minimisation
lambda_asym     = 15.0;    % anti-symmetry penalty weight

% Number of linear parameters in regressor
%   psi_linear = [a1, a2, bp, fc1, fc2, b1, b2]
n_param = 7;

fprintf('==========================================================\n');
fprintf('  MULTI-TRAJECTORY GENERATOR  (2-DOF Quanser 2DSFLE)\n');
fprintf('  10 training  +  2 testing  =  12 trajectories\n');
fprintf('==========================================================\n');
fprintf('Ts = %.3f s   margin = %.0f%%\n', Ts, margin*100);
fprintf('Regressor: psi = [a1, a2, bp, fc1, fc2, b1, b2]  (%d params)\n', n_param);
fprintf('J1: q +/-%.0fdeg   qd +/-%.0fdeg/s   qdd +/-%.0fdeg/s^2\n', ...
    rad2deg(q_max(1)), rad2deg(qd_max(1)), rad2deg(qdd_max(1)));
fprintf('J2: q +/-%.0fdeg   qd +/-%.0fdeg/s   qdd +/-%.0fdeg/s^2\n\n', ...
    rad2deg(q_max(2)), rad2deg(qd_max(2)), rad2deg(qdd_max(2)));

N_traj = 12;
trajs  = cell(N_traj, 1);

%% ====================================================================
%  2.  FOURIER-OPTIMISED TRAJECTORIES  (1-5 training, 12 testing)
%  ====================================================================
% Configs: [index, T, Nf, type]
fourier_cfgs = { ...
    1,  30,  9, 'train'; ...
    2,  15,  5, 'train'; ...
    3,  45, 12, 'train'; ...
    4,  20,  7, 'train'; ...
    5,  60, 15, 'train'; ...
   12,  25,  8, 'test'};

for fi = 1:size(fourier_cfgs, 1)
    ti    = fourier_cfgs{fi, 1};
    Tf    = fourier_cfgs{fi, 2};
    Nf    = fourier_cfgs{fi, 3};
    ttype = fourier_cfgs{fi, 4};

    fprintf('--- Traj %2d: Fourier-optimised  T=%ds  Nf=%d  [%s] ---\n', ...
        ti, Tf, Nf, upper(ttype));

    fname = sprintf('traj_%02d_fourier_T%d_Nf%d.mat', ti, Tf, Nf);

    if run_fourier_opt
        [q, qd, qdd, t] = run_fourier_optimiser( ...
            Tf, Nf, Ts, q_max, qd_max, qdd_max, v_eps, n_param, ...
            N_restarts, use_Dopt, lambda_asym);
    elseif isfile(fname)
        tmp = load(fname); q=tmp.q; qd=tmp.qd; qdd=tmp.qdd; t=tmp.t;
        fprintf('  Loaded from %s\n', fname);
    else
        fprintf('  SKIPPED (file not found, optimisation disabled)\n\n');
        continue
    end

    trajs{ti} = make_traj(q, qd, qdd, t, Ts, ...
        sprintf('Fourier T=%ds Nf=%d', Tf, Nf), ttype);
    fprintf('\n');
end

%% ====================================================================
%  3.  CHIRP FREQUENCY SWEEP  0.01 - 3 Hz   (Traj 6)
%  ====================================================================
fprintf('--- Traj  6: Chirp frequency sweep 0.01-3 Hz ---\n');

T6  = 60;
t6  = (0:Ts:T6-Ts)';
N6  = length(t6);
f0  = 0.01;  f1 = 3.0;                  % Hz

q6  = zeros(N6, 2);
qd6 = zeros(N6, 2);
qdd6= zeros(N6, 2);

for jj = 1:2
    % Instantaneous frequency (linear chirp)
    f_t = f0 + (f1 - f0) * t6 / T6;    % [Hz]
    w_t = 2*pi * f_t;                    % [rad/s]

    % Amplitude envelope: respect all limits (qdd binding at high freq)
    A_max = min([ q_lim(jj) * ones(N6,1), ...
                  qd_lim(jj) ./ max(w_t, 1e-6), ...
                  qdd_lim(jj) ./ max(w_t.^2, 1e-6) ], [], 2);
    A_env = A_max .* tukeywin(N6, 0.15);

    % Phase: integral of 2*pi*f(t)
    phi = 2*pi * (f0*t6 + (f1-f0)*t6.^2 / (2*T6));
    if jj == 2
        phi = phi + pi/3;               % offset J2 phase
    end

    % Numerical derivatives (safe for modulated envelope)
    dA    = gradient(A_env, Ts);
    dphi  = gradient(phi, Ts);
    d2A   = gradient(dA, Ts);
    d2phi = gradient(dphi, Ts);

    sp = sin(phi);  cp = cos(phi);
    q6(:,jj)   = A_env .* sp;
    qd6(:,jj)  = dA.*sp + A_env.*cp.*dphi;
    qdd6(:,jj) = d2A.*sp + 2*dA.*cp.*dphi ...
                  - A_env.*sp.*(dphi.^2) + A_env.*cp.*d2phi;
end

trajs{6} = make_traj(q6, qd6, qdd6, t6, Ts, 'Chirp 0.01-3 Hz', 'train');

%% ====================================================================
%  4.  CONSTANT-VELOCITY LOW-SPEED  (Coulomb / Stribeck)   (Traj 7)
%  ====================================================================
fprintf('--- Traj  7: Constant-velocity low-speed (friction) ---\n');

speeds_deg = [2, 5, 10, 15, 20];        % [deg/s]
t_hold     = 2.0;                        % constant-velocity duration [s]
t_trans    = 0.8;                        % 5th-order polynomial transition [s]

[q7, qd7, qdd7, t7] = gen_const_vel_traj( ...
    speeds_deg, t_hold, t_trans, Ts, q_lim);

trajs{7} = make_traj(q7, qd7, qdd7, t7, Ts, ...
    'Constant velocity (friction)', 'train');

%% ====================================================================
%  5.  FAST SINUSOIDAL  MULTI-AMPLITUDE  max 3 Hz   (Traj 8)
%  ====================================================================
fprintf('--- Traj  8: Fast sinusoidal multi-amplitude (max 3 Hz) ---\n');

T8 = 30;
t8 = (0:Ts:T8-Ts)';
N8 = length(t8);

% Frequency / amplitude schedule [freq_Hz, amp_deg]
%   Amplitudes set so that  A*(2*pi*f)^2 < 0.95*qdd_max
%   J1: qdd_lim = 570 deg/s^2   J2: qdd_lim = 380 deg/s^2
sched_j1 = [0.3,55; 0.5,40; 1.0,12; 1.5,5.5; 2.0,3.0; 3.0,1.2];
sched_j2 = [0.3,40; 0.5,25; 1.0, 8; 1.5,3.5; 2.0,2.0; 3.0,0.8];

q8   = zeros(N8, 2);
qd8  = zeros(N8, 2);
qdd8 = zeros(N8, 2);

for jj = 1:2
    if jj == 1, sched = sched_j1; else, sched = sched_j2; end
    n_seg   = size(sched, 1);
    seg_dur = T8 / n_seg;
    seg_N   = round(seg_dur / Ts);

    idx = 1;
    for si = 1:n_seg
        f_hz = sched(si, 1);
        A    = deg2rad(sched(si, 2));
        w    = 2*pi * f_hz;

        i_end = min(idx + seg_N - 1, N8);
        tt    = (0:i_end-idx)' * Ts;

        % Raised-cosine window for smooth transitions
        n_win = length(tt);
        n_tap = min(round(0.25/Ts), floor(n_win/4));
        win   = ones(n_win, 1);
        if n_tap > 1
            taper_up   = 0.5*(1 - cos(pi*(0:n_tap-1)'/n_tap));
            taper_down = 0.5*(1 - cos(pi*(n_tap-1:-1:0)'/n_tap));
            win(1:n_tap)         = taper_up;
            win(end-n_tap+1:end) = taper_down;
        end

        q_seg   = A * win .* sin(w*tt);
        qd_seg  = gradient(q_seg, Ts);
        qdd_seg = gradient(qd_seg, Ts);

        q8(idx:i_end, jj)   = q_seg;
        qd8(idx:i_end, jj)  = qd_seg;
        qdd8(idx:i_end, jj) = qdd_seg;
        idx = i_end + 1;
        if idx > N8, break; end
    end
end

trajs{8} = make_traj(q8, qd8, qdd8, t8, Ts, ...
    'Fast sinusoidal max 3 Hz', 'train');

%% ====================================================================
%  6.  SLOW FULL-RANGE SWEEP  +/-70 deg  (Traj 9)
%  ====================================================================
fprintf('--- Traj  9: Slow full-range sweep +/-70 deg ---\n');

T9 = 80;
t9 = (0:Ts:T9-Ts)';
N9 = length(t9);

A9_1 = q_lim(1);       A9_2 = q_lim(2);
T_j1 = 40;  T_j2 = 56;                    % incommensurate periods
w9_1 = 2*pi/T_j1;      w9_2 = 2*pi/T_j2;

% Raised-cosine taper (3s start/end)
t_ramp = 3.0;
env9   = ones(N9, 1);
ramp_up   = t9 < t_ramp;
ramp_down = t9 > (T9 - t_ramp);
env9(ramp_up)   = 0.5*(1 - cos(pi*t9(ramp_up)/t_ramp));
env9(ramp_down) = 0.5*(1 - cos(pi*(T9 - t9(ramp_down))/t_ramp));

q9  = [A9_1*env9.*sin(w9_1*t9), A9_2*env9.*sin(w9_2*t9)];
qd9  = [gradient(q9(:,1),Ts), gradient(q9(:,2),Ts)];
qdd9 = [gradient(qd9(:,1),Ts), gradient(qd9(:,2),Ts)];

trajs{9} = make_traj(q9, qd9, qdd9, t9, Ts, ...
    'Slow full-range +/-70 deg', 'train');

%% ====================================================================
%  7.  STEP-STAIRCASE TRAJECTORY   (Traj 10)
%  ====================================================================
fprintf('--- Traj 10: Step-staircase ---\n');

T10 = 50;
t10 = (0:Ts:T10-Ts)';
N10 = length(t10);

steps_j1 = [0, 30, -20, 50, -50, 60, -60, 20, -30, 0];
steps_j2 = [0, -40, 40, -20, 60, -60, 30, -50, 10, 0];

q10 = zeros(N10, 2);
for jj = 1:2
    if jj == 1, steps = steps_j1; else, steps = steps_j2; end
    n_steps = length(steps);
    seg_N   = round(N10 / n_steps);

    q_raw = zeros(N10, 1);
    for si = 1:n_steps
        i_s = (si-1)*seg_N + 1;
        i_e = min(si*seg_N, N10);
        q_raw(i_s:i_e) = deg2rad(steps(si));
    end

    wn = 2*pi*1.2;
    [bf, af] = butter(2, min(wn*Ts/pi, 0.99));
    q_filt = filtfilt(bf, af, q_raw);
    q_filt = max(-q_lim(jj), min(q_lim(jj), q_filt));
    q10(:, jj) = q_filt;
end

qd10  = [gradient(q10(:,1),Ts), gradient(q10(:,2),Ts)];
qdd10 = [gradient(qd10(:,1),Ts), gradient(qd10(:,2),Ts)];

trajs{10} = make_traj(q10, qd10, qdd10, t10, Ts, 'Step-staircase', 'train');

%% ====================================================================
%  8.  TESTING -- LISSAJOUS  AMPLITUDE-MODULATED   (Traj 11)
%  ====================================================================
fprintf('--- Traj 11: Lissajous AM  [TEST] ---\n');

T11 = 40;
t11 = (0:Ts:T11-Ts)';
N11 = length(t11);

f_j1 = 0.30;   f_j2 = 0.47;            % irrational ratio ~ 0.638
delta = pi/5;
w_j1 = 2*pi*f_j1;  w_j2 = 2*pi*f_j2;

A1_base = q_lim(1) * 0.75;
A2_base = q_lim(2) * 0.60;
f_mod = 0.05;  w_mod = 2*pi*f_mod;

A1_t = A1_base * (1 + 0.25*sin(w_mod*t11));
A2_t = A2_base * (1 + 0.25*sin(w_mod*t11 + pi/3));

t_tap = 2.0;
env11 = ones(N11, 1);
env11(t11 < t_tap) = 0.5*(1 - cos(pi*t11(t11 < t_tap)/t_tap));
env11(t11 > T11-t_tap) = 0.5*(1 - cos(pi*(T11 - t11(t11 > T11-t_tap))/t_tap));

q11 = [A1_t .* env11 .* sin(w_j1*t11), ...
       A2_t .* env11 .* sin(w_j2*t11 + delta)];
qd11  = [gradient(q11(:,1),Ts), gradient(q11(:,2),Ts)];
qdd11 = [gradient(qd11(:,1),Ts), gradient(qd11(:,2),Ts)];

trajs{11} = make_traj(q11, qd11, qdd11, t11, Ts, 'Lissajous AM', 'test');

% NOTE: Traj 12 (Fourier test T=25s Nf=8) was generated in section 2.

%% ====================================================================
%  9.  VALIDATE ALL TRAJECTORIES
%  ====================================================================
fprintf('\n============ VALIDATION ============\n');
all_ok = true;
for ti = 1:N_traj
    if isempty(trajs{ti}), continue; end
    [ok, viol] = validate_traj(trajs{ti}, q_max, qd_max, qdd_max);
    if ok, status = 'OK';
    else,  status = sprintf('VIOLATION (%s)', strtrim(viol)); all_ok = false;
    end
    fprintf('  [%2d] %-35s  %-20s  (%5.1fs,  %s)\n', ...
        ti, trajs{ti}.name, status, trajs{ti}.T_dur, trajs{ti}.type);
end
if all_ok
    fprintf('  >>> All trajectories within hard limits.\n');
else
    fprintf('  >>> WARNING: some trajectories violate limits.\n');
end

%% ====================================================================
% 10.  REGRESSOR CONDITION ANALYSIS  (per trajectory + stacked)
%  ====================================================================
fprintf('\n============ REGRESSOR CONDITION NUMBERS ============\n');
fprintf('  Regressor: psi = [a1, a2, bp, fc1, fc2, b1, b2]\n\n');

Y_all_train = [];
for ti = 1:N_traj
    if isempty(trajs{ti}), continue; end
    s = trajs{ti};
    Y_ti = build_regressor(s.q, s.qd, s.qdd, v_eps);
    sv = svd(Y_ti);
    cn = sv(1) / max(sv(end), 1e-12);
    fprintf('  [%2d] %-30s  cond = %8.2f   sv_min = %.4f   (%s)\n', ...
        ti, s.name, cn, sv(end), s.type);

    if strcmp(s.type, 'train')
        Y_all_train = [Y_all_train; Y_ti]; %#ok<AGROW>
    end
end

% Stacked training regressor
sv_all = svd(Y_all_train);
cn_all = sv_all(1) / max(sv_all(end), 1e-12);
fprintf('\n  STACKED (all training):  cond = %.2f   sv_min = %.4f\n', ...
    cn_all, sv_all(end));
fprintf('  Singular values:'); fprintf(' %.3f', sv_all); fprintf('\n');

%% ====================================================================
% 11.  SAVE
%  ====================================================================
N_delay = round(1/Ts);   % samples in 1 second
fprintf('\n============ SAVING ============\n');
for ti = 1:N_traj
    if isempty(trajs{ti}), continue; end
    s = trajs{ti};
    q = s.q; qd = s.qd; qdd = s.qdd; t = s.t;

    % --- Prepend zeros in time direction ---
    q   = [zeros(N_delay, size(q,2));   q(:, :)];
    qd  = [zeros(N_delay, size(qd,2));  qd(:, :)];
    qdd = [zeros(N_delay, size(qdd,2)); qdd(:, :)];
    Ts_save = s.Ts;
    traj_name = s.name; traj_type = s.type;
    fname = sprintf('traj_%02d.mat', ti);
    save(fname, 'q','qd','qdd','t','Ts_save','traj_name','traj_type');
    fprintf('  Saved %s  (%s)\n', fname, traj_name);
end

all_trajs = trajs; %#ok<NASGU>
save('all_trajectories.mat', 'all_trajs');
fprintf('  Saved all_trajectories.mat\n');

%% ====================================================================
% 12.  PLOTS
%  ====================================================================
fprintf('\n============ PLOTTING ============\n');

% --- Configuration space overview ---
figure('Name','Configuration Space Overview','Position',[50 50 1400 900]);
n_cols = 4;  n_rows = ceil(N_traj/n_cols);
colours = lines(N_traj);
for ti = 1:N_traj
    if isempty(trajs{ti}), continue; end
    subplot(n_rows, n_cols, ti);
    plot(rad2deg(trajs{ti}.q(:,1)), rad2deg(trajs{ti}.q(:,2)), ...
        'Color', colours(ti,:), 'LineWidth', 0.8);
    hold on;
    plot(rad2deg(trajs{ti}.q(1,1)), rad2deg(trajs{ti}.q(1,2)), ...
        'go','MarkerSize',6,'LineWidth',1.5);
    xlim(rad2deg(q_max(1))*[-1 1]);
    ylim(rad2deg(q_max(2))*[-1 1]);
    title(sprintf('%d. %s', ti, trajs{ti}.name), ...
        'FontSize',8,'Interpreter','none');
    xlabel('q_1 [deg]'); ylabel('q_2 [deg]');
    grid on; axis equal;
    if strcmp(trajs{ti}.type, 'test')
        set(gca, 'Color', [1 0.97 0.92]);
    end
end
sgtitle('All 12 Trajectories - Configuration Space', 'FontSize', 14);

% --- Detailed q/qd/qdd per trajectory ---
for ti = 1:N_traj
    if isempty(trajs{ti}), continue; end
    plot_trajectory_detail(trajs{ti}, ti, q_max, qd_max, qdd_max);
end

% --- Summary bar chart ---
figure('Name','Trajectory Summary','Position',[100 100 1000 500]);
valid_idx = find(~cellfun(@isempty, trajs));
n_valid   = length(valid_idx);
names_str = cell(n_valid,1);
durations = zeros(n_valid,1);
max_qd1   = zeros(n_valid,1);  max_qd2  = zeros(n_valid,1);
max_qdd1  = zeros(n_valid,1);  max_qdd2 = zeros(n_valid,1);

for k = 1:n_valid
    ti = valid_idx(k);
    names_str{k} = sprintf('%d.%s', ti, trajs{ti}.name);
    durations(k) = trajs{ti}.T_dur;
    max_qd1(k)   = rad2deg(max(abs(trajs{ti}.qd(:,1))));
    max_qd2(k)   = rad2deg(max(abs(trajs{ti}.qd(:,2))));
    max_qdd1(k)  = rad2deg(max(abs(trajs{ti}.qdd(:,1))));
    max_qdd2(k)  = rad2deg(max(abs(trajs{ti}.qdd(:,2))));
end

subplot(1,3,1);
barh(durations); set(gca,'YTick',1:n_valid,'YTickLabel',names_str,'FontSize',7);
xlabel('Duration [s]'); title('Duration'); grid on;
subplot(1,3,2);
barh([max_qd1, max_qd2]);
set(gca,'YTick',1:n_valid,'YTickLabel',names_str,'FontSize',7);
xlabel('Max |qd| [deg/s]'); title('Peak velocity');
legend('J1','J2','Location','southeast'); grid on;
subplot(1,3,3);
barh([max_qdd1, max_qdd2]);
set(gca,'YTick',1:n_valid,'YTickLabel',names_str,'FontSize',7);
xlabel('Max |qdd| [deg/s^2]'); title('Peak acceleration');
legend('J1','J2','Location','southeast'); grid on;
sgtitle('Trajectory Set Summary', 'FontSize', 14);

% --- Regressor singular value plot ---
figure('Name','Stacked Training Regressor','Position',[1100 100 450 350]);
bar(sv_all, 'FaceColor', [0.2 0.5 0.8]);
xlabel('Index'); ylabel('Singular value');
title(sprintf('Stacked training regressor:  cond(Y) = %.1f', cn_all));
grid on;

fprintf('\nDone.  %d trajectories generated.\n', n_valid);


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  ===================  HELPER FUNCTIONS  =============================
%  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% --- Build regressor Y such that tau = Y * [a1;a2;bp;fc1;fc2;b1;b2] ---
%  Consistent with residualsEL_analytic_2dof.m
%
%  M = [a1+a2+2*bp*c2,  a2+bp*c2;        tau = M*qdd + C*qd + F
%       a2+bp*c2,        a2       ]
%
%  C = [-bp*s2*qd2,       -bp*s2*(qd1+qd2);
%        bp*s2*qd1,        0               ]
%
%  F = [fc1*tanh(qd1/v_eps) + b1*qd1;
%       fc2*tanh(qd2/v_eps) + b2*qd2]
%
%  Regressor rows (from d(tau)/d(psi)):
%    Row 1 (joint 1):
%      a1:  qdd1
%      a2:  qdd1 + qdd2
%      bp:  2*c2*qdd1 + c2*qdd2 - s2*(2*qd1*qd2 + qd2^2)
%      fc1: tanh(qd1/v_eps)    fc2: 0
%      b1:  qd1                b2:  0
%    Row 2 (joint 2):
%      a1:  0
%      a2:  qdd1 + qdd2
%      bp:  c2*qdd1 + s2*qd1^2
%      fc1: 0                  fc2: tanh(qd2/v_eps)
%      b1:  0                  b2:  qd2

function Y = build_regressor(q, qd, qdd, v_eps)
    N = size(q, 1);
    Y = zeros(2*N, 7);

    for i = 1:N
        r1 = 2*i - 1;
        r2 = 2*i;

        q2i  = q(i, 2);
        qd1  = qd(i, 1);    qd2  = qd(i, 2);
        qdd1 = qdd(i, 1);   qdd2 = qdd(i, 2);

        c2 = cos(q2i);
        s2 = sin(q2i);

        %       a1      a2           bp                                         fc1               fc2               b1   b2
        Y(r1,:) = [qdd1, qdd1+qdd2, 2*c2*qdd1+c2*qdd2-s2*(2*qd1*qd2+qd2^2), tanh(qd1/v_eps), 0,                qd1, 0  ];
        Y(r2,:) = [0,    qdd1+qdd2, c2*qdd1+s2*qd1^2,                         0,                tanh(qd2/v_eps), 0,   qd2];
    end
end

%% --- Make trajectory struct ---
function s = make_traj(q, qd, qdd, t, Ts, name, type)
    s.q     = q;
    s.qd    = qd;
    s.qdd   = qdd;
    s.t     = t(:);
    s.Ts    = Ts;
    s.name  = name;
    s.type  = type;
    s.T_dur = t(end) + Ts;
end

%% --- Validate trajectory against hard limits ---
function [ok, viol] = validate_traj(s, q_max, qd_max, qdd_max)
    ok = true;  viol = '';
    tol_q = 1.01; tol_qd = 1.05; tol_qdd = 1.10;
    for jj = 1:2
        if max(abs(s.q(:,jj)))   > q_max(jj)*tol_q
            ok=false; viol=[viol,sprintf('q%d ',jj)]; %#ok<AGROW>
        end
        if max(abs(s.qd(:,jj)))  > qd_max(jj)*tol_qd
            ok=false; viol=[viol,sprintf('qd%d ',jj)]; %#ok<AGROW>
        end
        if max(abs(s.qdd(:,jj))) > qdd_max(jj)*tol_qdd
            ok=false; viol=[viol,sprintf('qdd%d ',jj)]; %#ok<AGROW>
        end
    end
end

%% --- Plot single trajectory ---
function plot_trajectory_detail(s, idx, q_max, qd_max, qdd_max)
    figure('Name', sprintf('Traj %d: %s', idx, s.name), ...
           'Position', [100+20*idx, 100+15*idx, 950, 700]);

    jlabels = {'Joint 1', 'Joint 2'};
    for jj = 1:2
        subplot(3,2,jj);
        plot(s.t, rad2deg(s.q(:,jj)), 'b', 'LineWidth', 1); hold on;
        yline( rad2deg(q_max(jj)), 'r--', 'LineWidth', 0.8);
        yline(-rad2deg(q_max(jj)), 'r--', 'LineWidth', 0.8);
        ylabel('q [deg]'); grid on;
        title(jlabels{jj}, 'FontSize', 9);

        subplot(3,2, 2+jj);
        plot(s.t, rad2deg(s.qd(:,jj)), 'b', 'LineWidth', 1); hold on;
        yline( rad2deg(qd_max(jj)), 'r--', 'LineWidth', 0.8);
        yline(-rad2deg(qd_max(jj)), 'r--', 'LineWidth', 0.8);
        ylabel('qd [deg/s]'); grid on;

        subplot(3,2, 4+jj);
        plot(s.t, rad2deg(s.qdd(:,jj)), 'b', 'LineWidth', 1); hold on;
        yline( rad2deg(qdd_max(jj)), 'r--', 'LineWidth', 0.8);
        yline(-rad2deg(qdd_max(jj)), 'r--', 'LineWidth', 0.8);
        ylabel('qdd [deg/s^2]'); xlabel('Time [s]'); grid on;
    end

    type_str = upper(s.type);
    sgtitle(sprintf('Traj %d: %s  [%s]', idx, s.name, type_str), ...
            'FontSize', 12, 'Interpreter', 'none');
end


%% --- Constant-velocity trajectory (Coulomb/Stribeck friction) ---
function [q, qd, qdd, t] = gen_const_vel_traj( ...
    speeds_deg, t_hold, t_trans, Ts, q_lim)
    % Each joint cycles through all speeds (+/-).
    % Joint 1 first, then Joint 2.  5th-order poly transitions.

    n_speeds = length(speeds_deg);
    n_seg_per_joint = 2 * n_speeds;     % pos + neg per speed
    t_seg = t_hold + t_trans;
    T_per_joint = n_seg_per_joint * t_seg + t_seg;  % +return
    T_total = 2 * T_per_joint;

    t = (0:Ts:T_total-Ts)';
    N = length(t);
    q   = zeros(N, 2);
    qd  = zeros(N, 2);
    qdd = zeros(N, 2);

    for jj = 1:2
        t_offset = (jj-1) * T_per_joint;
        pos = 0;
        seg_idx = 0;

        for si = 1:n_speeds
            for direction = [1, -1]
                v_rad = direction * deg2rad(speeds_deg(si));

                % Check position limit
                delta_pos = v_rad * t_hold + v_rad * t_trans * 0.5;
                if abs(pos + delta_pos) > q_lim(jj) * 0.90
                    continue;  % skip this segment
                end

                t_start = t_offset + seg_idx * t_seg;

                for k = 1:N
                    dt = t(k) - t_start;
                    if dt < 0 || dt >= t_seg, continue; end

                    if dt < t_trans
                        tau = dt / t_trans;
                        s5  = 10*tau^3 - 15*tau^4 + 6*tau^5;
                        ds5 = (30*tau^2 - 60*tau^3 + 30*tau^4) / t_trans;
                        p5  = t_trans * (2.5*tau^4 - 3*tau^5 + tau^6);

                        q(k,jj)   = pos + v_rad * p5;
                        qd(k,jj)  = v_rad * s5;
                        qdd(k,jj) = v_rad * ds5;
                    else
                        dt2    = dt - t_trans;
                        p_ramp = v_rad * t_trans * 0.5;
                        q(k,jj)   = pos + p_ramp + v_rad * dt2;
                        qd(k,jj)  = v_rad;
                        qdd(k,jj) = 0;
                    end
                end

                p_ramp = v_rad * t_trans * 0.5;
                pos = pos + p_ramp + v_rad * t_hold;
                pos = max(-q_lim(jj)*0.9, min(q_lim(jj)*0.9, pos));
                seg_idx = seg_idx + 1;
            end
        end

        % Return to zero
        t_start = t_offset + seg_idx * t_seg;
        pos_final = pos;
        for k = 1:N
            dt = t(k) - t_start;
            if dt < 0 || dt >= t_seg, continue; end
            tau = dt / t_seg;
            blend   = 1 - 10*tau^3 + 15*tau^4 - 6*tau^5;
            dblend  = (-30*tau^2 + 60*tau^3 - 30*tau^4) / t_seg;
            d2blend = (-60*tau + 180*tau^2 - 120*tau^3) / t_seg^2;
            q(k,jj)   = pos_final * blend;
            qd(k,jj)  = pos_final * dblend;
            qdd(k,jj) = pos_final * d2blend;
        end
    end

    % Trim trailing zeros
    last_nonzero = find(any(q ~= 0, 2) | any(qd ~= 0, 2), 1, 'last');
    if ~isempty(last_nonzero)
        keep = min(N, last_nonzero + round(2/Ts));
        q=q(1:keep,:); qd=qd(1:keep,:); qdd=qdd(1:keep,:); t=t(1:keep);
    end
end


%% ====================================================================
%  FOURIER OPTIMISER  (Swevers 1997)
%  ====================================================================
%  Uses the SAME regressor as build_regressor:
%    psi = [a1, a2, bp, fc1, fc2, b1, b2]

function [q, qd, qdd, t] = run_fourier_optimiser( ...
    T, Nf, Ts, q_max, qd_max, qdd_max, v_eps, n_param, ...
    N_restarts, use_Dopt, lambda_asym)

    omega  = 2*pi / T;
    n_pj   = 2*Nf;          % decision vars per joint
    Ns     = 200;            % regressor evaluation points
    t_s    = linspace(0, T, Ns+1);  t_s(end) = [];
    t_save = (0:Ts:T-Ts);

    fprintf('  Fourier opt: Nf=%d  T=%.0fs  omega=%.4f  (%d vars)\n', ...
        Nf, T, omega, 2*n_pj);

    best_J = Inf;
    best_x = [];

    opts = optimoptions('fmincon', ...
        'Algorithm',              'sqp', ...
        'MaxFunctionEvaluations',  100000, ...
        'MaxIterations',           8000, ...
        'ConstraintTolerance',     1e-6, ...
        'OptimalityTolerance',     1e-8, ...
        'StepTolerance',           1e-10, ...
        'Display',                 'final');

    for r = 1:N_restarts
        x0 = make_x0_fourier(r, Nf, n_pj);
        try
            [xo, Jo, ef] = fmincon( ...
                @(x) obj_fourier(x,Nf,omega,t_s,v_eps,use_Dopt,n_param,lambda_asym), ...
                x0, [],[],[],[],[],[], ...
                @(x) con_fourier(x,Nf,omega,t_s,q_max,qd_max,qdd_max), ...
                opts);
            fprintf('    restart %d/%d  exit=%d  J=%.4f\n', ...
                r, N_restarts, ef, Jo);
            if Jo < best_J, best_J = Jo; best_x = xo; end
        catch ME
            fprintf('    restart %d/%d  FAILED: %s\n', r, N_restarts, ME.message);
        end
    end

    if isempty(best_x)
        warning('Fourier opt failed (T=%ds Nf=%d). Using random.', T, Nf);
        best_x = randn(2*n_pj, 1) * 0.2;
    end

    [q0_1,a1,b1] = unpack_fourier(best_x(1:n_pj), Nf, omega);
    [q0_2,a2,b2] = unpack_fourier(best_x(n_pj+1:end), Nf, omega);
    [q1,qd1,qdd1] = ftraj(q0_1,a1,b1,omega,Nf,t_save);
    [q2,qd2,qdd2] = ftraj(q0_2,a2,b2,omega,Nf,t_save);

    q   = [q1(:), q2(:)];
    qd  = [qd1(:), qd2(:)];
    qdd = [qdd1(:), qdd2(:)];
    t   = t_save(:);

    % Report condition number
    [q1s,qd1s,qdd1s] = ftraj(q0_1,a1,b1,omega,Nf,t_s);
    [q2s,qd2s,qdd2s] = ftraj(q0_2,a2,b2,omega,Nf,t_s);
    Y = build_regressor_from_vectors(q1s,q2s,qd1s,qd2s,qdd1s,qdd2s,v_eps);
    sv = svd(Y);
    fprintf('  cond(Y) = %.1f   sv_min = %.4f\n', sv(1)/sv(end), sv(end));
end

%% --- Fourier sub-functions ---

function [q0,a,b] = unpack_fourier(xj, Nf, omega)
    a  = xj(1:Nf);
    b  = xj(Nf+1:2*Nf);
    q0 = -sum(b(:) ./ ((1:Nf)'*omega));   % enforces q(0) = 0
end

function [q,qd,qdd] = ftraj(q0,a,b,w,Nf,t)
    q=q0*ones(size(t)); qd=zeros(size(t)); qdd=zeros(size(t));
    for k=1:Nf
        kw=k*w; s=sin(kw*t); c=cos(kw*t);
        q   = q   + (a(k)/kw)*s + (b(k)/kw)*c;
        qd  = qd  + a(k)*c      - b(k)*s;
        qdd = qdd + kw*(-a(k)*s - b(k)*c);
    end
end

% Regressor from row vectors (used inside Fourier optimiser)
% Same structure as build_regressor but operates on row vectors
function Y = build_regressor_from_vectors(q1,q2,qd1,qd2,qdd1,qdd2,v_eps)
    N = length(q1);
    Y = zeros(2*N, 7);
    for i = 1:N
        r1 = 2*i-1;  r2 = 2*i;
        c2 = cos(q2(i));  s2 = sin(q2(i));
        Y(r1,:) = [qdd1(i), qdd1(i)+qdd2(i), ...
                   2*c2*qdd1(i)+c2*qdd2(i)-s2*(2*qd1(i)*qd2(i)+qd2(i)^2), ...
                   tanh(qd1(i)/v_eps), 0, qd1(i), 0];
        Y(r2,:) = [0, qdd1(i)+qdd2(i), ...
                   c2*qdd1(i)+s2*qd1(i)^2, ...
                   0, tanh(qd2(i)/v_eps), 0, qd2(i)];
    end
end

function J = obj_fourier(x, Nf, w, t_s, v_eps, use_Dopt, np, lambda_asym)
    npj = 2*Nf;
    [q01,a1,b1] = unpack_fourier(x(1:npj), Nf, w);
    [q02,a2,b2] = unpack_fourier(x(npj+1:end), Nf, w);
    [q1,qd1,qdd1] = ftraj(q01,a1,b1,w,Nf,t_s);
    [q2,qd2,qdd2] = ftraj(q02,a2,b2,w,Nf,t_s);
    Y = build_regressor_from_vectors(q1,q2,qd1,qd2,qdd1,qdd2,v_eps);

    if use_Dopt
        M = Y'*Y + 1e-10*eye(np);
        J_info = -log(det(M));
    else
        s = svd(Y);
        J_info = s(1) / max(s(end), 1e-12);
    end

    dq  = q1 - q2;
    dqd = qd1 - qd2;
    rms_diff = sqrt(mean(dq.^2) + mean(dqd.^2));
    J_asym = lambda_asym / (rms_diff + 0.01);

    J = J_info + J_asym;
end

function [c, ceq] = con_fourier(x, Nf, w, t_s, q_max, qd_max, qdd_max)
    npj = 2*Nf;
    [q01,a1,b1] = unpack_fourier(x(1:npj), Nf, w);
    [q02,a2,b2] = unpack_fourier(x(npj+1:end), Nf, w);
    [q1,qd1,qdd1] = ftraj(q01,a1,b1,w,Nf,t_s);
    [q2,qd2,qdd2] = ftraj(q02,a2,b2,w,Nf,t_s);
    c = [ q1(:)-q_max(1);   -q1(:)-q_max(1);
          q2(:)-q_max(2);   -q2(:)-q_max(2);
          qd1(:)-qd_max(1); -qd1(:)-qd_max(1);
          qd2(:)-qd_max(2); -qd2(:)-qd_max(2);
          qdd1(:)-qdd_max(1);-qdd1(:)-qdd_max(1);
          qdd2(:)-qdd_max(2);-qdd2(:)-qdd_max(2) ];
    ceq = [];
end

function x0 = make_x0_fourier(idx, Nf, npj)
    x0 = zeros(2*npj, 1);
    switch mod(idx-1, 5)
        case 0   % J1 low harmonics, J2 high
            for k=1:min(3,Nf)
                x0(k)=randn*0.4; x0(Nf+k)=randn*0.4;
            end
            for k=max(1,Nf-2):Nf
                x0(npj+k)=randn*0.4; x0(npj+Nf+k)=randn*0.4;
            end
        case 1   % opposite signs
            x0(1:npj) = rand(npj,1)*0.5;
            x0(npj+1:end) = -rand(npj,1)*0.5;
        case 2   % J1 broadband, J2 single harmonic
            x0(1:npj) = randn(npj,1)*0.3;
            k=randi(Nf); x0(npj+k)=randn*0.8; x0(npj+Nf+k)=randn*0.8;
        case 3   % phase shifted
            for k=1:Nf
                amp=rand*0.5; phi=rand*2*pi;
                x0(k)=amp*cos(phi); x0(Nf+k)=amp*sin(phi);
                phi2=phi+pi/2+rand*pi/2;
                x0(npj+k)=amp*cos(phi2); x0(npj+Nf+k)=amp*sin(phi2);
            end
        case 4   % fully random
            x0 = randn(2*npj,1)*0.3;
    end
end