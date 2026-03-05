%% GENERATE_ALL_TRAJECTORIES
%  Complete trajectory set for IDIM-OLS / NLS identification of the
%  Quanser 2DSFLE (2-DOF planar manipulator with harmonic drives).
%
%  Parameter vector (consistent with residualsEL_analytic_2dof):
%    psi = [a1, a2, bp, fc1, fc2, b1, b2]   (7 linear params)
%    v_eps is treated as fixed hyperparameter in the regressor.
%
%  TRAINING (10):
%    1-4.   Fourier-optimised  (column-equilibrated cond objective)
%    5-6.   Constant-velocity friction (low-speed, both directions)
%    7-10.  Lissajous  (one ultra-slow for friction excitation)
%
%  TESTING (2):
%   11.  Fourier-optimised     (T=25s, Nf=8)
%   12.  Lissajous             (unseen freq pair)
%
%  All trajectories:
%   - begin with 1 s of zeros (controller settling)
%   - ramp smoothly from zero velocity (raised-cosine, 1.5 s)
%   - ramp down to zero at end
%   - respect joint limits
%
%  CHANGES vs previous version:
%   [FIX 1] Two constant-velocity friction trajectories replace one
%           Fourier and one Lissajous — directly excite Coulomb/Stribeck
%   [FIX 2] One Lissajous is ultra-slow (f<0.04 Hz) so both joints spend
%           significant time in the tanh transition zone (|qd| ~ v_eps)
%   [FIX 3] Fourier objective uses column-equilibrated condition number:
%           cond(Y * diag(1./colnorms)) so friction columns get equal
%           weight vs inertial columns in the optimisation

clear; clc; close all;

%% ====================================================================
%  1. GLOBAL SETTINGS
%  ====================================================================
Ts = 0.01;                          % sample time [s]

% Joint limits  [joint1; joint2]
q_max   = deg2rad([70; 70]);        % [rad]
qd_max  = deg2rad([90; 300]);       % [rad/s]
qdd_max = deg2rad([600; 400]);      % [rad/s^2]

% Design margin (95 %)
margin  = 0.95;
q_lim   = margin * q_max;
qd_lim  = margin * qd_max;
qdd_lim = margin * qdd_max;

v_eps = 0.1;         % tanh smoothing for Coulomb
l1    = 0.3493;      % link-1 length [m]
n_param = 7;         % [a1, a2, bp, fc1, fc2, b1, b2]

% Prepend / envelope settings
t_prepend = 1.0;     % zeros at start [s]
t_ramp    = 1.5;     % raised-cosine ramp duration [s]

% Fourier optimiser
run_fourier_opt = true;
N_restarts      = 5;
use_Dopt        = false;
lambda_asym     = 15.0;

fprintf('==========================================================\n');
fprintf('  TRAJECTORY GENERATOR  (2-DOF Quanser 2DSFLE)\n');
fprintf('  4 Fourier + 2 Friction + 4 Lissajous  training\n');
fprintf('  1 Fourier + 1 Lissajous  testing   = 12 total\n');
fprintf('==========================================================\n');
fprintf('Ts = %.3f s   margin = %.0f%%\n', Ts, margin*100);
fprintf('Zero prepend = %.1f s   ramp = %.1f s\n', t_prepend, t_ramp);
fprintf('Regressor: psi = [a1, a2, bp, fc1, fc2, b1, b2]\n');
fprintf('J1: q +/-%.0fdeg   qd +/-%.0fdeg/s   qdd +/-%.0fdeg/s^2\n', ...
    rad2deg(q_max(1)), rad2deg(qd_max(1)), rad2deg(qdd_max(1)));
fprintf('J2: q +/-%.0fdeg   qd +/-%.0fdeg/s   qdd +/-%.0fdeg/s^2\n\n', ...
    rad2deg(q_max(2)), rad2deg(qd_max(2)), rad2deg(qdd_max(2)));

N_traj = 12;
trajs  = cell(N_traj, 1);

%% ====================================================================
%  2.  FOURIER-OPTIMISED  (1-4 train,  11 test)
%  ====================================================================
%  [FIX 3] Objective now uses column-equilibrated condition number.
%  This prevents the inertial columns (large norms) from dominating
%  and forces the optimiser to also improve the friction columns.

fourier_cfgs = { ...
%   idx   T    Nf   type
     1,  30,   9,  'train'; ...
     2,  15,   5,  'train'; ...
     3,  45,  12,  'train'; ...
     4,  20,   7,  'train'; ...
    11,  25,   8,  'test'};

for fi = 1:size(fourier_cfgs, 1)
    ti    = fourier_cfgs{fi, 1};
    Tf    = fourier_cfgs{fi, 2};
    Nf    = fourier_cfgs{fi, 3};
    ttype = fourier_cfgs{fi, 4};

    fprintf('--- Traj %2d: Fourier  T=%ds  Nf=%d  [%s] ---\n', ...
        ti, Tf, Nf, upper(ttype));

    fname = sprintf('traj_%02d_fourier_T%d_Nf%d.mat', ti, Tf, Nf);

    if run_fourier_opt
        [q_raw, ~, ~, ~] = run_fourier_optimiser( ...
            Tf, Nf, Ts, q_max, qd_max, qdd_max, v_eps, n_param, ...
            N_restarts, use_Dopt, lambda_asym);
    elseif isfile(fname)
        tmp = load(fname); q_raw = tmp.q;
        fprintf('  Loaded from %s\n', fname);
    else
        fprintf('  SKIPPED\n\n');
        continue
    end

    trajs{ti} = finalize_trajectory(q_raw, Ts, t_ramp, t_prepend, ...
        sprintf('Fourier T=%ds Nf=%d', Tf, Nf), ttype);
    fprintf('\n');
end

%% ====================================================================
%  3.  CONSTANT-VELOCITY FRICTION  (5-6 train)
%  ====================================================================
%  [FIX 1] Two dedicated friction trajectories.
%
%  Traj 5: Slow constant-velocity sweeps.  Both joints cycle through
%          speeds  [1, 2, 3, 5, 8, 12, 20]  deg/s  in both directions.
%          Joint 1 and Joint 2 run sequentially.
%          This directly excites the tanh(qd/v_eps) Coulomb term and
%          the b*qd viscous term at multiple operating points.
%
%  Traj 6: Same concept but simultaneous joint motion at different
%          speed ratios, exciting coupling terms too.

fprintf('--- Traj  5: Const-vel friction (sequential) ---\n');

speeds_deg_5 = [1, 2, 3, 5, 8, 12, 20];   % [deg/s]
t_hold_5     = 2.5;                          % hold per segment [s]
t_trans_5    = 1.0;                          % poly transition [s]

[q5_raw, ~, ~, ~] = gen_const_vel_sequential( ...
    speeds_deg_5, t_hold_5, t_trans_5, Ts, q_lim);

trajs{5} = finalize_trajectory(q5_raw, Ts, t_ramp, t_prepend, ...
    'Const-vel friction (seq)', 'train');


fprintf('--- Traj  6: Const-vel friction (simultaneous) ---\n');

speeds_j1 = [2, 5, 10, 15, 3, 8];    % [deg/s]
speeds_j2 = [5, 12, 3, 8, 15, 2];    % [deg/s] — different order
t_hold_6  = 2.5;
t_trans_6 = 1.0;

[q6_raw, ~, ~, ~] = gen_const_vel_simultaneous( ...
    speeds_j1, speeds_j2, t_hold_6, t_trans_6, Ts, q_lim);

trajs{6} = finalize_trajectory(q6_raw, Ts, t_ramp, t_prepend, ...
    'Const-vel friction (simul)', 'train');

%% ====================================================================
%  4.  LISSAJOUS TRAJECTORIES  (7-10 train,  12 test)
%  ====================================================================
%  [FIX 2] Traj 7 is ultra-slow:  f = [0.025, 0.035] Hz.
%  At f=0.025 Hz, peak velocity = A*2*pi*f.
%  With A = q_lim (66.5 deg = 1.16 rad): peak qd = 1.16*0.157 = 0.18 rad/s = 10.4 deg/s
%  At v_eps = 0.1 rad/s ? 5.7 deg/s, the trajectory spends substantial
%  time with |qd| < 3*v_eps = 17 deg/s, i.e. in the tanh transition zone.

lissajous_cfgs = { ...
%   idx   f1      f2      delta     A1%    A2%    AM     f_mod   T_dur  type
     7,  0.025,  0.035,  pi/4,     0.95,  0.95,  false, 0,      90,   'train'; ...  % [FIX 2] ultra-slow
     8,  0.30,   0.47,   pi/3,     0.80,  0.70,  true,  0.05,   40,   'train'; ...  % moderate
     9,  0.50,   0.81,   pi/7,     0.85,  0.80,  false, 0,      30,   'train'; ...  % faster
    10,  0.18,   0.73,   2*pi/3,   0.85,  0.75,  true,  0.04,   50,   'train'; ...  % wide ratio
    12,  0.25,   0.41,   pi/6,     0.75,  0.65,  true,  0.06,   40,   'test'};

for li = 1:size(lissajous_cfgs, 1)
    ti      = lissajous_cfgs{li, 1};
    f1      = lissajous_cfgs{li, 2};
    f2      = lissajous_cfgs{li, 3};
    delta   = lissajous_cfgs{li, 4};
    A1_frac = lissajous_cfgs{li, 5};
    A2_frac = lissajous_cfgs{li, 6};
    use_AM  = lissajous_cfgs{li, 7};
    f_mod   = lissajous_cfgs{li, 8};
    T_dur   = lissajous_cfgs{li, 9};
    ttype   = lissajous_cfgs{li, 10};

    fprintf('--- Traj %2d: Lissajous  f=[%.3f, %.3f] Hz  T=%ds  [%s] ---\n', ...
        ti, f1, f2, T_dur, upper(ttype));

    t_lis = (0:Ts:T_dur-Ts)';
    N_lis = length(t_lis);

    freqs  = [f1, f2];
    A_frac = [A1_frac, A2_frac];
    phases = [0, delta];

    q_raw = zeros(N_lis, 2);
    for jj = 1:2
        w_j = 2*pi * freqs(jj);

        % Max safe amplitude:  |q|<=A,  |qd|<=A*w,  |qdd|<=A*w^2
        A_safe = min([q_lim(jj), qd_lim(jj)/w_j, qdd_lim(jj)/w_j^2]);

        if use_AM
            m = 0.25;
            A_base = A_safe * A_frac(jj) / (1 + m);
            w_mod  = 2*pi * f_mod;
            phi_mod = (jj-1) * pi/3;
            A_t = A_base * (1 + m * sin(w_mod*t_lis + phi_mod));
        else
            A_t = A_safe * A_frac(jj) * ones(N_lis, 1);
        end

        q_raw(:, jj) = A_t .* sin(w_j*t_lis + phases(jj));
    end

    trajs{ti} = finalize_trajectory(q_raw, Ts, t_ramp, t_prepend, ...
        sprintf('Lissajous f=[%.3f,%.3f]', f1, f2), ttype);

    % Diagnostic: fraction of time in tanh transition zone
    s = trajs{ti};
    frac_low_j1 = mean(abs(s.qd(:,1)) < 3*v_eps);
    frac_low_j2 = mean(abs(s.qd(:,2)) < 3*v_eps);
    fprintf('  Time in |qd|<3*v_eps:  J1=%.0f%%  J2=%.0f%%\n', ...
        frac_low_j1*100, frac_low_j2*100);
end

%% ====================================================================
%  5.  VALIDATE ALL TRAJECTORIES
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
%  6.  REGRESSOR CONDITION ANALYSIS
%  ====================================================================
fprintf('\n============ REGRESSOR CONDITION NUMBERS ============\n');
fprintf('  psi = [a1, a2, bp, fc1, fc2, b1, b2]\n');
fprintf('  (both raw and column-equilibrated)\n\n');

Y_all_train = [];
for ti = 1:N_traj
    if isempty(trajs{ti}), continue; end
    s = trajs{ti};
    Y_ti = build_regressor(s.q, s.qd, s.qdd, v_eps);
    sv = svd(Y_ti);
    cn = sv(1) / max(sv(end), 1e-12);

    % Column-equilibrated
    col_norms = vecnorm(Y_ti, 2, 1);
    Y_eq = Y_ti ./ max(col_norms, 1e-10);
    sv_eq = svd(Y_eq);
    cn_eq = sv_eq(1) / max(sv_eq(end), 1e-12);

    fprintf('  [%2d] %-30s  cond=%7.1f  cond_eq=%7.1f  (%s)\n', ...
        ti, s.name, cn, cn_eq, s.type);

    if strcmp(s.type, 'train')
        Y_all_train = [Y_all_train; Y_ti]; %#ok<AGROW>
    end
end

% Stacked training
sv_all = svd(Y_all_train);
cn_all = sv_all(1) / max(sv_all(end), 1e-12);

col_norms_all = vecnorm(Y_all_train, 2, 1);
Y_all_eq = Y_all_train ./ max(col_norms_all, 1e-10);
sv_all_eq = svd(Y_all_eq);
cn_all_eq = sv_all_eq(1) / max(sv_all_eq(end), 1e-12);

fprintf('\n  STACKED training:\n');
fprintf('    cond(Y)    = %.2f\n', cn_all);
fprintf('    cond_eq(Y) = %.2f   (column-equilibrated)\n', cn_all_eq);
fprintf('    sv:'); fprintf(' %.1f', sv_all); fprintf('\n');
fprintf('    Column norms: '); fprintf(' %.1f', col_norms_all); fprintf('\n');
fprintf('    (a1    a2    bp    fc1   fc2   b1    b2)\n');

%% ====================================================================
%  7.  SAVE
%  ====================================================================
fprintf('\n============ SAVING ============\n');
for ti = 1:N_traj
    if isempty(trajs{ti}), continue; end
    s = trajs{ti};
    q = s.q; qd = s.qd; qdd = s.qdd; t = s.t;
    Ts_save = s.Ts; traj_name = s.name; traj_type = s.type;
    fname = sprintf('traj_%02d.mat', ti);
    save(fname, 'q','qd','qdd','t','Ts_save','traj_name','traj_type');
    fprintf('  Saved %s  (%s)\n', fname, traj_name);
end
all_trajs = trajs; %#ok<NASGU>
save('all_trajectories.mat', 'all_trajs');
fprintf('  Saved all_trajectories.mat\n');

%% ====================================================================
%  8.  PLOTS
%  ====================================================================
fprintf('\n============ PLOTTING ============\n');

% --- Configuration space overview ---
figure('Name','Config Space Overview','Position',[50 50 1400 900]);
n_cols = 4;  n_rows = ceil(N_traj/n_cols);
colours = lines(N_traj);
for ti = 1:N_traj
    if isempty(trajs{ti}), continue; end
    subplot(n_rows, n_cols, ti);
    plot(rad2deg(trajs{ti}.q(:,1)), rad2deg(trajs{ti}.q(:,2)), ...
        'Color', colours(ti,:), 'LineWidth', 0.8);
    hold on;
    plot(0, 0, 'go','MarkerSize',6,'LineWidth',1.5);
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

% --- Detailed plots ---
for ti = 1:N_traj
    if isempty(trajs{ti}), continue; end
    plot_trajectory_detail(trajs{ti}, ti, q_max, qd_max, qdd_max);
end

% --- Startup check ---
figure('Name','Startup Verification','Position',[100 800 1200 350]);
for ti = 1:N_traj
    if isempty(trajs{ti}), continue; end
    s = trajs{ti};
    subplot(2, ceil(N_traj/2), ti);
    n_show = min(500, size(s.q,1));
    plot(s.t(1:n_show), rad2deg(s.qd(1:n_show,1)), 'b', 'LineWidth', 1); hold on;
    plot(s.t(1:n_show), rad2deg(s.qd(1:n_show,2)), 'r', 'LineWidth', 1);
    xline(t_prepend, 'k--', 'LineWidth', 0.5);
    ylabel('qd [deg/s]'); xlabel('t [s]');
    title(sprintf('%d. %s', ti, trajs{ti}.name), 'FontSize', 7, 'Interpreter','none');
    grid on;
end
sgtitle('Startup: velocity in first 5 s  (dashed = end of zero section)', ...
    'FontSize', 11);

% --- Velocity histograms (friction diagnostic) ---
figure('Name','Velocity Histograms','Position',[100 400 1400 500]);
vel_edges = linspace(-30, 30, 120);  % deg/s
for ti = 1:N_traj
    if isempty(trajs{ti}), continue; end
    s = trajs{ti};
    subplot(2, ceil(N_traj/2), ti);
    histogram(rad2deg(s.qd(:,1)), vel_edges, 'FaceAlpha', 0.5, 'FaceColor', 'b'); hold on;
    histogram(rad2deg(s.qd(:,2)), vel_edges, 'FaceAlpha', 0.5, 'FaceColor', 'r');
    xline(-rad2deg(v_eps), 'k--'); xline(rad2deg(v_eps), 'k--');
    xline(-3*rad2deg(v_eps), 'k:'); xline(3*rad2deg(v_eps), 'k:');
    title(sprintf('%d. %s', ti, trajs{ti}.name), 'FontSize', 7, 'Interpreter','none');
    xlabel('qd [deg/s]'); ylabel('count');
    xlim([-30 30]); grid on;
end
sgtitle('Velocity distributions  (dashed = v_{eps},  dotted = 3*v_{eps})', ...
    'FontSize', 11);

% --- Summary bar chart ---
figure('Name','Trajectory Summary','Position',[100 100 1100 450]);
valid_idx = find(~cellfun(@isempty, trajs));
n_valid   = length(valid_idx);
names_str = cell(n_valid,1);
durations = zeros(n_valid,1);
max_qd1   = zeros(n_valid,1); max_qd2  = zeros(n_valid,1);
max_qdd1  = zeros(n_valid,1); max_qdd2 = zeros(n_valid,1);
for k = 1:n_valid
    ti = valid_idx(k);
    names_str{k} = sprintf('%d. %s [%s]', ti, trajs{ti}.name, trajs{ti}.type);
    durations(k) = trajs{ti}.T_dur;
    max_qd1(k)  = rad2deg(max(abs(trajs{ti}.qd(:,1))));
    max_qd2(k)  = rad2deg(max(abs(trajs{ti}.qd(:,2))));
    max_qdd1(k) = rad2deg(max(abs(trajs{ti}.qdd(:,1))));
    max_qdd2(k) = rad2deg(max(abs(trajs{ti}.qdd(:,2))));
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

% --- Stacked SVD ---
figure('Name','Stacked Regressor','Position',[1100 100 500 350]);
subplot(1,2,1);
bar(sv_all, 'FaceColor', [0.2 0.5 0.8]);
xlabel('Index'); ylabel('Singular value');
title(sprintf('Raw:  cond = %.1f', cn_all)); grid on;
subplot(1,2,2);
bar(sv_all_eq, 'FaceColor', [0.8 0.3 0.2]);
xlabel('Index'); ylabel('Singular value');
title(sprintf('Column-equilibrated:  cond = %.1f', cn_all_eq)); grid on;
sgtitle('Stacked training regressor', 'FontSize', 12);

fprintf('\nDone.  %d trajectories generated.\n', n_valid);


%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  =========================  FUNCTIONS  ==============================
%  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% --- Finalize: envelope + zero-prepend + derivatives ---
function s = finalize_trajectory(q_raw, Ts, t_ramp, t_prepend, name, type)
    [N, nj] = size(q_raw);
    n_ramp = round(t_ramp / Ts);
    n_pre  = round(t_prepend / Ts);

    % Raised-cosine envelope
    env = ones(N, 1);
    ramp_up   = 0.5 * (1 - cos(pi * (0:n_ramp-1)' / n_ramp));
    ramp_down = flipud(ramp_up);
    n_up = min(n_ramp, N);
    n_dn = min(n_ramp, N);
    env(1:n_up)         = ramp_up(1:n_up);
    env(end-n_dn+1:end) = ramp_down(end-n_dn+1:end);

    q_env = q_raw .* env;

    % Prepend zeros
    q = [zeros(n_pre, nj); q_env];
    N_total = size(q, 1);

    % Numerical derivatives
    qd  = zeros(N_total, nj);
    qdd = zeros(N_total, nj);
    for j = 1:nj
        qd(:,j)  = gradient(q(:,j), Ts);
        qdd(:,j) = gradient(qd(:,j), Ts);
    end

    t = (0:Ts:(N_total-1)*Ts)';

    s.q = q;  s.qd = qd;  s.qdd = qdd;  s.t = t;
    s.Ts = Ts;  s.name = name;  s.type = type;
    s.T_dur = t(end) + Ts;
end

%% --- Build regressor:  tau = Y * [a1; a2; bp; fc1; fc2; b1; b2] ---
function Y = build_regressor(q, qd, qdd, v_eps)
    N = size(q, 1);
    Y = zeros(2*N, 7);
    for i = 1:N
        r1 = 2*i-1;  r2 = 2*i;
        c2 = cos(q(i,2));  s2 = sin(q(i,2));
        qd1 = qd(i,1);   qd2 = qd(i,2);
        qdd1 = qdd(i,1); qdd2 = qdd(i,2);
        Y(r1,:) = [qdd1, qdd1+qdd2, ...
                   2*c2*qdd1+c2*qdd2-s2*(2*qd1*qd2+qd2^2), ...
                   tanh(qd1/v_eps), 0, qd1, 0];
        Y(r2,:) = [0, qdd1+qdd2, c2*qdd1+s2*qd1^2, ...
                   0, tanh(qd2/v_eps), 0, qd2];
    end
end

%% --- Validate ---
function [ok, viol] = validate_traj(s, q_max, qd_max, qdd_max)
    ok = true;  viol = '';
    tol_q=1.01; tol_qd=1.05; tol_qdd=1.10;
    for jj = 1:2
        if max(abs(s.q(:,jj)))   > q_max(jj)*tol_q
            ok=false; viol=[viol,sprintf('q%d ',jj)]; end %#ok<AGROW>
        if max(abs(s.qd(:,jj)))  > qd_max(jj)*tol_qd
            ok=false; viol=[viol,sprintf('qd%d ',jj)]; end %#ok<AGROW>
        if max(abs(s.qdd(:,jj))) > qdd_max(jj)*tol_qdd
            ok=false; viol=[viol,sprintf('qdd%d ',jj)]; end %#ok<AGROW>
    end
end

%% --- Plot detail ---
function plot_trajectory_detail(s, idx, q_max, qd_max, qdd_max)
    figure('Name', sprintf('Traj %d: %s', idx, s.name), ...
           'Position', [100+20*idx, 100+15*idx, 950, 700]);
    jlabels = {'Joint 1', 'Joint 2'};
    for jj = 1:2
        subplot(3,2,jj);
        plot(s.t, rad2deg(s.q(:,jj)), 'b', 'LineWidth', 1); hold on;
        yline( rad2deg(q_max(jj)), 'r--'); yline(-rad2deg(q_max(jj)), 'r--');
        ylabel('q [deg]'); grid on; title(jlabels{jj});
        subplot(3,2,2+jj);
        plot(s.t, rad2deg(s.qd(:,jj)), 'b', 'LineWidth', 1); hold on;
        yline( rad2deg(qd_max(jj)), 'r--'); yline(-rad2deg(qd_max(jj)), 'r--');
        ylabel('qd [deg/s]'); grid on;
        subplot(3,2,4+jj);
        plot(s.t, rad2deg(s.qdd(:,jj)), 'b', 'LineWidth', 1); hold on;
        yline( rad2deg(qdd_max(jj)), 'r--'); yline(-rad2deg(qdd_max(jj)), 'r--');
        ylabel('qdd [deg/s^2]'); xlabel('Time [s]'); grid on;
    end
    sgtitle(sprintf('Traj %d: %s  [%s]', idx, s.name, upper(s.type)), ...
            'FontSize', 12, 'Interpreter', 'none');
end


%% ====================================================================
%  CONSTANT-VELOCITY GENERATORS
%  ====================================================================

%% --- Sequential: one joint at a time ---
function [q, qd, qdd, t] = gen_const_vel_sequential( ...
    speeds_deg, t_hold, t_trans, Ts, q_lim)
    % Each joint cycles through all speeds (+/-).
    % Joint 1 first, then Joint 2.

    n_speeds = length(speeds_deg);
    n_seg_per_joint = 2 * n_speeds;
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
                delta_pos = v_rad * t_hold + v_rad * t_trans * 0.5;
                if abs(pos + delta_pos) > q_lim(jj) * 0.90
                    continue;
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
                        dt2 = dt - t_trans;
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
            q(k,jj)   = pos_final * (1 - 10*tau^3 + 15*tau^4 - 6*tau^5);
            qd(k,jj)  = pos_final / t_seg * (-30*tau^2 + 60*tau^3 - 30*tau^4);
            qdd(k,jj) = pos_final / t_seg^2 * (-60*tau + 180*tau^2 - 120*tau^3);
        end
    end

    % Trim trailing zeros
    last_nz = find(any(q ~= 0, 2) | any(qd ~= 0, 2), 1, 'last');
    if ~isempty(last_nz)
        keep = min(N, last_nz + round(2/Ts));
        q=q(1:keep,:); qd=qd(1:keep,:); qdd=qdd(1:keep,:); t=t(1:keep);
    end
end

%% --- Simultaneous: both joints at different speeds ---
function [q, qd, qdd, t] = gen_const_vel_simultaneous( ...
    speeds_j1, speeds_j2, t_hold, t_trans, Ts, q_lim)
    % Both joints move simultaneously at different speed pairs.
    % Positive then negative for each pair.

    n_pairs = min(length(speeds_j1), length(speeds_j2));
    t_seg   = t_hold + t_trans;
    n_segs  = 2 * n_pairs + 1;     % pos+neg for each pair + return
    T_total = n_segs * t_seg;

    t = (0:Ts:T_total-Ts)';
    N = length(t);
    q   = zeros(N, 2);
    qd  = zeros(N, 2);
    qdd = zeros(N, 2);

    pos = [0, 0];
    seg_idx = 0;

    for pi_idx = 1:n_pairs
        for direction = [1, -1]
            v_rad = direction * [deg2rad(speeds_j1(pi_idx)), ...
                                 deg2rad(speeds_j2(pi_idx))];

            % Check both joints stay in bounds
            skip = false;
            for jj = 1:2
                delta = v_rad(jj)*t_hold + v_rad(jj)*t_trans*0.5;
                if abs(pos(jj) + delta) > q_lim(jj)*0.85
                    skip = true; break;
                end
            end
            if skip, continue; end

            t_start = seg_idx * t_seg;
            for k = 1:N
                dt = t(k) - t_start;
                if dt < 0 || dt >= t_seg, continue; end

                for jj = 1:2
                    if dt < t_trans
                        tau = dt / t_trans;
                        s5  = 10*tau^3 - 15*tau^4 + 6*tau^5;
                        ds5 = (30*tau^2 - 60*tau^3 + 30*tau^4) / t_trans;
                        p5  = t_trans * (2.5*tau^4 - 3*tau^5 + tau^6);
                        q(k,jj)   = pos(jj) + v_rad(jj) * p5;
                        qd(k,jj)  = v_rad(jj) * s5;
                        qdd(k,jj) = v_rad(jj) * ds5;
                    else
                        dt2 = dt - t_trans;
                        p_ramp = v_rad(jj) * t_trans * 0.5;
                        q(k,jj)   = pos(jj) + p_ramp + v_rad(jj) * dt2;
                        qd(k,jj)  = v_rad(jj);
                        qdd(k,jj) = 0;
                    end
                end
            end

            for jj = 1:2
                p_ramp = v_rad(jj) * t_trans * 0.5;
                pos(jj) = pos(jj) + p_ramp + v_rad(jj) * t_hold;
                pos(jj) = max(-q_lim(jj)*0.85, min(q_lim(jj)*0.85, pos(jj)));
            end
            seg_idx = seg_idx + 1;
        end
    end

    % Return to zero
    t_start = seg_idx * t_seg;
    for k = 1:N
        dt = t(k) - t_start;
        if dt < 0 || dt >= t_seg, continue; end
        tau = dt / t_seg;
        for jj = 1:2
            q(k,jj)   = pos(jj) * (1 - 10*tau^3 + 15*tau^4 - 6*tau^5);
            qd(k,jj)  = pos(jj)/t_seg * (-30*tau^2 + 60*tau^3 - 30*tau^4);
            qdd(k,jj) = pos(jj)/t_seg^2 * (-60*tau + 180*tau^2 - 120*tau^3);
        end
    end

    last_nz = find(any(q ~= 0, 2) | any(qd ~= 0, 2), 1, 'last');
    if ~isempty(last_nz)
        keep = min(N, last_nz + round(2/Ts));
        q=q(1:keep,:); qd=qd(1:keep,:); qdd=qdd(1:keep,:); t=t(1:keep);
    end
end


%% ====================================================================
%  FOURIER OPTIMISER  (Swevers 1997)
%  ====================================================================
%  [FIX 3] Uses column-equilibrated condition number:
%    J_info = cond(Y * diag(1./col_norms))
%  This ensures the optimiser cannot ignore friction columns (fc1, fc2)
%  just because their norms are smaller than the inertial columns.

function [q, qd, qdd, t] = run_fourier_optimiser( ...
    T, Nf, Ts, q_max, qd_max, qdd_max, v_eps, n_param, ...
    N_restarts, use_Dopt, lambda_asym)

    omega  = 2*pi / T;
    n_pj   = 2*Nf;
    Ns     = 200;
    t_s    = linspace(0, T, Ns+1);  t_s(end) = [];
    t_save = (0:Ts:T-Ts);

    fprintf('  Fourier opt: Nf=%d  T=%.0fs  omega=%.4f  (%d vars)\n', ...
        Nf, T, omega, 2*n_pj);

    best_J = Inf;
    best_x = [];

    opts = optimoptions('fmincon', ...
        'Algorithm','sqp', ...
        'MaxFunctionEvaluations',100000, ...
        'MaxIterations',8000, ...
        'ConstraintTolerance',1e-6, ...
        'OptimalityTolerance',1e-8, ...
        'StepTolerance',1e-10, ...
        'Display','final');

    for r = 1:N_restarts
        x0 = make_x0_fourier(r, Nf, n_pj);
        try
            [xo, Jo, ef] = fmincon( ...
                @(x) obj_fourier(x,Nf,omega,t_s,v_eps,use_Dopt,n_param,lambda_asym), ...
                x0, [],[],[],[],[],[], ...
                @(x) con_fourier(x,Nf,omega,t_s,q_max,qd_max,qdd_max), opts);
            fprintf('    restart %d/%d  exit=%d  J=%.4f\n', r, N_restarts, ef, Jo);
            if Jo < best_J, best_J = Jo; best_x = xo; end
        catch ME
            fprintf('    restart %d/%d  FAILED: %s\n', r, N_restarts, ME.message);
        end
    end

    if isempty(best_x)
        warning('Fourier opt failed (T=%ds Nf=%d).', T, Nf);
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

    % Report both raw and equilibrated condition numbers
    [q1s,qd1s,qdd1s] = ftraj(q0_1,a1,b1,omega,Nf,t_s);
    [q2s,qd2s,qdd2s] = ftraj(q0_2,a2,b2,omega,Nf,t_s);
    Y = build_regressor_vec(q1s,q2s,qd1s,qd2s,qdd1s,qdd2s,v_eps);
    sv = svd(Y);
    col_n = vecnorm(Y, 2, 1);
    Y_eq  = Y ./ max(col_n, 1e-10);
    sv_eq = svd(Y_eq);
    fprintf('  cond(Y) = %.1f   cond_eq(Y) = %.1f   sv_min = %.4f\n', ...
        sv(1)/sv(end), sv_eq(1)/sv_eq(end), sv(end));
end

function [q0,a,b] = unpack_fourier(xj, Nf, omega)
    a  = xj(1:Nf);
    b  = xj(Nf+1:2*Nf);
    q0 = -sum(b(:) ./ ((1:Nf)'*omega));
end

function [q,qd,qdd] = ftraj(q0,a,b,w,Nf,t)
    q=q0*ones(size(t)); qd=zeros(size(t)); qdd=zeros(size(t));
    for k=1:Nf
        kw=k*w; s=sin(kw*t); c=cos(kw*t);
        q   = q   + (a(k)/kw)*s + (b(k)/kw)*c;
        qd  = qd  + a(k)*c - b(k)*s;
        qdd = qdd + kw*(-a(k)*s - b(k)*c);
    end
end

function Y = build_regressor_vec(q1,q2,qd1,qd2,qdd1,qdd2,v_eps)
    N = length(q1);
    Y = zeros(2*N, 7);
    for i = 1:N
        r1=2*i-1; r2=2*i;
        c2=cos(q2(i)); s2=sin(q2(i));
        Y(r1,:) = [qdd1(i), qdd1(i)+qdd2(i), ...
                   2*c2*qdd1(i)+c2*qdd2(i)-s2*(2*qd1(i)*qd2(i)+qd2(i)^2), ...
                   tanh(qd1(i)/v_eps), 0, qd1(i), 0];
        Y(r2,:) = [0, qdd1(i)+qdd2(i), c2*qdd1(i)+s2*qd1(i)^2, ...
                   0, tanh(qd2(i)/v_eps), 0, qd2(i)];
    end
end

%% [FIX 3] Column-equilibrated condition number objective
function J = obj_fourier(x, Nf, w, t_s, v_eps, use_Dopt, np, lambda_asym)
    npj = 2*Nf;
    [q01,a1,b1] = unpack_fourier(x(1:npj), Nf, w);
    [q02,a2,b2] = unpack_fourier(x(npj+1:end), Nf, w);
    [q1,qd1,qdd1] = ftraj(q01,a1,b1,w,Nf,t_s);
    [q2,qd2,qdd2] = ftraj(q02,a2,b2,w,Nf,t_s);
    Y = build_regressor_vec(q1,q2,qd1,qd2,qdd1,qdd2,v_eps);

    % Column-equilibrate before computing information metric
    col_norms = vecnorm(Y, 2, 1);
    Y_eq = Y ./ max(col_norms, 1e-10);

    if use_Dopt
        M = Y_eq'*Y_eq + 1e-10*eye(np);
        J_info = -log(det(M));
    else
        s = svd(Y_eq);
        J_info = s(1) / max(s(end), 1e-12);
    end

    % Anti-symmetry penalty
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
    c = [q1(:)-q_max(1);   -q1(:)-q_max(1);
         q2(:)-q_max(2);   -q2(:)-q_max(2);
         qd1(:)-qd_max(1); -qd1(:)-qd_max(1);
         qd2(:)-qd_max(2); -qd2(:)-qd_max(2);
         qdd1(:)-qdd_max(1);-qdd1(:)-qdd_max(1);
         qdd2(:)-qdd_max(2);-qdd2(:)-qdd_max(2)];
    ceq = [];
end

function x0 = make_x0_fourier(idx, Nf, npj)
    x0 = zeros(2*npj, 1);
    switch mod(idx-1, 5)
        case 0
            for k=1:min(3,Nf)
                x0(k)=randn*0.4; x0(Nf+k)=randn*0.4;
            end
            for k=max(1,Nf-2):Nf
                x0(npj+k)=randn*0.4; x0(npj+Nf+k)=randn*0.4;
            end
        case 1
            x0(1:npj) = rand(npj,1)*0.5;
            x0(npj+1:end) = -rand(npj,1)*0.5;
        case 2
            x0(1:npj) = randn(npj,1)*0.3;
            k=randi(Nf); x0(npj+k)=randn*0.8; x0(npj+Nf+k)=randn*0.8;
        case 3
            for k=1:Nf
                amp=rand*0.5; phi=rand*2*pi;
                x0(k)=amp*cos(phi); x0(Nf+k)=amp*sin(phi);
                phi2=phi+pi/2+rand*pi/2;
                x0(npj+k)=amp*cos(phi2); x0(npj+Nf+k)=amp*sin(phi2);
            end
        case 4
            x0 = randn(2*npj,1)*0.3;
    end
end