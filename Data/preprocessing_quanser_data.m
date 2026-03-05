clear; clc;

%% ===================== USER SETTINGS =====================
Kt1 = 3.018583e+00;
Kt2 = 1.111065;
J1_motor  = 2.030252e-02;
B1_motor  = 9.233265e-02;
J2_motor  = 6.530040e-04;
B2_motor  = 4.505757e-02;
v_eps = 0.034872;

% Savitzky-Golay filter parameters
F = 61;
K = 2;
dt = 1e-2;
data_dir = 'DATA-05-03_2';

%% ===================== TRAJECTORY DEFINITIONS =====================
trajectories = {
    'traj_01.mat', 'shoulder_01.mat', 'elbow_01.mat', 'traj\_01';
    'traj_02.mat', 'shoulder_02.mat', 'elbow_02.mat', 'traj\_02';
    'traj_03.mat', 'shoulder_03.mat', 'elbow_03.mat', 'traj\_03';
    'traj_04.mat', 'shoulder_04.mat', 'elbow_04.mat', 'traj\_04';
    'traj_05.mat', 'shoulder_05.mat', 'elbow_05.mat', 'traj\_05';
    'traj_06.mat', 'shoulder_06.mat', 'elbow_06.mat', 'traj\_06';
    'traj_07.mat', 'shoulder_07.mat', 'elbow_07.mat', 'traj\_07';
    'traj_08.mat', 'shoulder_08.mat', 'elbow_08.mat', 'traj\_08';
    'traj_09.mat', 'shoulder_09.mat', 'elbow_09.mat', 'traj\_09';
    'traj_10.mat', 'shoulder_10.mat', 'elbow_10.mat', 'traj\_10';
};

%% ===================== TRAIN / VAL / TEST SPLIT =====================
train_idx = [1,2,3,4,5,6,7,8];
val_idx   = [1];
test_idx  = [9,10];

%% ===================== IDENTIFIED LINK-SIDE PARAMETERS =====================
% Fill these in with your identified values (from IDIM-OLS/NLS).
% These are needed for KE and momentum computation.
% psi = [a1; a2; bp; fc1; fc2; b1; b2]
%   a1 = m1*r1^2 + m2*l1^2 + I1  (composite shoulder inertia)
%   a2 = m2*r2^2 + I2              (composite elbow inertia)
%   bp = m2*l1*r2                   (coupling parameter)
%
% >>> UPDATE THESE WITH YOUR IDENTIFIED VALUES <<<
a1 = 0.039 + 1.6537*0.29^2 + 0.9982*0.343^2;  % placeholder from CAD
a2 = 0.0081 + 0.9982*0.175^2;                    % placeholder from CAD
bp = 0.9982 * 0.343 * 0.175;                     % placeholder from CAD

%% ===================== LOAD & FORMAT =====================
num_trajectories = size(trajectories, 1);

% Load all trajectory data
all_data = cell(num_trajectories, 1);
for i = 1:num_trajectories
    all_data{i} = load_traj_data(data_dir, trajectories(i,:), Kt1, Kt2, dt, K, F);
    fprintf('Loaded trajectory %d/%d\n', i, num_trajectories);
end

% Build runs struct array matching simulation format
runs = repmat(struct( ...
    'time',       [], ...
    'x_true',     [], ...   % Nx4: best estimate [q1, q2, qd1, qd2]
    'y_meas',     [], ...   % Nx4: raw measurements (before SG on positions)
    'y_filt',     [], ...   % Nx4: SG-filtered [q1, q2, qd1, qd2]
    'u_cmd',      [], ...   % Nx2: motor-side torque (Kt * I_filt)
    'u_cmd_noisy',[], ...   % Nx2: same as u_cmd (no synthetic noise)
    'u_applied',  [], ...   % Nx2: link-side torque (motor dynamics subtracted)
    'p',          [], ...   % Nx2: generalized momentum
    'KE',         [], ...   % Nx1: kinetic energy
    'ddq',        [], ...   % Nx2: filtered accelerations
    'initial_condition', [], ...
    'torque_params',     [], ...
    'noise_sigmas',      struct( ...
        'sigma_tau1',0,'sigma_tau2',0, ...
        'sigma_uc1',0,'sigma_uc2',0, ...
        'sigma_th1',0,'sigma_th2',0, ...
        'sigma_dth1',0,'sigma_dth2',0), ...
    'friction_params',   struct('b1',[],'b2',[],'fc1',[],'fc2',[],'v_eps',[]), ...
    'split', '' ...         % 'train', 'val', or 'test'
    ), num_trajectories, 1);

for i = 1:num_trajectories
    d = all_data{i};
    N = numel(d.t);
    t_vec = d.t(:);  % Nx1

    % --- States ---
    % y_filt: SG-filtered positions and SG-differentiated velocities
    q_filt  = d.q_filt.';    % Nx2
    qd_filt = d.qd_filt.';   % Nx2
    qdd_filt = d.qdd_filt.'; % Nx2
    y_filt = [q_filt, qd_filt];  % Nx4

    % y_meas: the position measurements fed into SG (already lightly filtered
    % in load_traj_data — see note below). Velocities from SG differentiation.
    q_meas = d.q_meas.';     % Nx2
    % For y_meas velocities, use the SG-derived ones (no raw velocity sensor)
    y_meas = [q_meas, qd_filt];  % Nx4

    % x_true: for real data, best estimate = filtered
    x_true = y_filt;

    % --- Torques ---
    % Motor-side torque: Kt * I_filtered
    tau_motor = d.tau_meas.';  % Nx2

    % Link-side torque: subtract motor shaft dynamics
    %   tau_link = tau_motor - J_motor * qdd - B_motor * qd
    tau_link = zeros(N, 2);
    tau_link(:,1) = tau_motor(:,1) - J1_motor * qdd_filt(:,1) - B1_motor * qd_filt(:,1);
    tau_link(:,2) = tau_motor(:,2) - J2_motor * qdd_filt(:,2) - B2_motor * qd_filt(:,2);


    % --- Trim first and last 1 s (SG edge effects) ---
    trim_samples = round(1.0 / dt);  % 100 samples at 100 Hz
    idx_keep = (trim_samples + 1) : (N - trim_samples);

    % --- Populate struct (trimmed) ---
    runs(i).time       = t_vec(idx_keep) - t_vec(idx_keep(1));  % reset to 0
    runs(i).x_true     = x_true(idx_keep, :);
    runs(i).y_meas     = y_meas(idx_keep, :);
    runs(i).y_filt     = y_filt(idx_keep, :);
    runs(i).u_cmd      = tau_motor(idx_keep, :);       % motor-side
    runs(i).u_cmd_noisy = tau_motor(idx_keep, :);      % identical (real data)
    runs(i).u_applied  = tau_motor(idx_keep, :);       % link-side
    runs(i).ddq        = qdd_filt(idx_keep, :);
    runs(i).initial_condition = x_true(idx_keep(1), :);
    runs(i).torque_params = struct('type', 'real_data', ...
                                   'trajectory_file', trajectories{i,1}, ...
                                   'label', trajectories{i,4});
    runs(i).noise_sigmas = struct( ...
        'sigma_tau1',0,'sigma_tau2',0, ...
        'sigma_uc1',0,'sigma_uc2',0, ...
        'sigma_th1',0,'sigma_th2',0, ...
        'sigma_dth1',0,'sigma_dth2',0);
    runs(i).friction_params = struct('b1',[],'b2',[],'fc1',[],'fc2',[],'v_eps',v_eps);

    % Split label
    if ismember(i, train_idx), runs(i).split = 'train';
    elseif ismember(i, val_idx), runs(i).split = 'val';
    elseif ismember(i, test_idx), runs(i).split = 'test';
    else, runs(i).split = 'unused';
    end

    fprintf('Formatted trajectory %d/%d  [%s]  (%d -> %d samples)\n', ...
        i, num_trajectories, runs(i).split, N, numel(idx_keep));
end

%% ===================== BUILD DATASET STRUCT =====================
% Use the time vector from the first run as reference
% (all runs may have different lengths — store per-run)
dataset.runs = runs;
dataset.dt   = dt;
dataset.num_runs = num_trajectories;
dataset.split_info = struct('train_idx', train_idx, ...
                            'val_idx', val_idx, ...
                            'test_idx', test_idx);
dataset.motor_params = struct('Kt1', Kt1, 'Kt2', Kt2);
dataset.filter_params = struct('K', K, 'F', F);
dataset.source = 'real_robot';

%% ===================== SAVE =====================
save('planar_2dof_dataset_real.mat', 'dataset', '-v7');
fprintf('\nSaved: planar_2dof_dataset_real.mat\n');
fprintf('  %d runs total: %d train, %d val, %d test\n', ...
    num_trajectories, numel(train_idx), numel(val_idx), numel(test_idx));

%% ===================== QUICK SANITY PLOTS =====================
r = runs(1); tt = r.time;

figure('Color','w','Name','Run 1: Torques');
subplot(2,1,1);
plot(tt, r.u_cmd(:,1), '-', tt, r.u_applied(:,1), '--');
grid on; ylabel('Nm'); title('Joint 1 torque');
legend('Motor-side (Kt*I)', 'Link-side (motor dyn subtracted)', 'Location','best');
subplot(2,1,2);
plot(tt, r.u_cmd(:,2), '-', tt, r.u_applied(:,2), '--');
grid on; ylabel('Nm'); xlabel('Time [s]'); title('Joint 2 torque');
legend('Motor-side (Kt*I)', 'Link-side (motor dyn subtracted)', 'Location','best');

figure('Color','w','Name','Run 1: Filtered states');
subplot(2,2,1);
plot(tt, r.y_filt(:,1)); grid on; ylabel('rad'); title('\theta_1 filtered');
subplot(2,2,2);
plot(tt, r.y_filt(:,2)); grid on; ylabel('rad'); title('\theta_2 filtered');
subplot(2,2,3);
plot(tt, r.y_filt(:,3)); grid on; ylabel('rad/s'); xlabel('Time [s]');
title('$\dot{\theta}_1$ filtered','Interpreter','latex');
subplot(2,2,4);
plot(tt, r.y_filt(:,4)); grid on; ylabel('rad/s'); xlabel('Time [s]');
title('$\dot{\theta}_2$ filtered','Interpreter','latex');


%% ===================== HELPER FUNCTIONS =====================

function M = M_mat(theta2, a1, a2, b)
    c2 = cos(theta2);
    M = [a1 + a2 + 2*b*c2,  a2 + b*c2;
         a2 + b*c2,          a2];
end

function data = load_traj_data(data_dir, traj_info, Kt1, Kt2, dt, K, F)
    % Load shoulder data
    S_res1 = load(fullfile(data_dir, traj_info{2}));
    fn1 = fieldnames(S_res1);
    S_res1 = S_res1.(fn1{1});
    S_res1 = S_res1(2:end, :);  % skip header row

    % Load elbow data
    S_res2 = load(fullfile(data_dir, traj_info{3}));
    fn2 = fieldnames(S_res2);
    S_res2 = S_res2.(fn2{1});
    S_res2 = S_res2(2:end, :);

    actual_current_1 = S_res1(:,2);
    q_meas_1         = S_res1(:,4);
    actual_current_2 = S_res2(:,2);
    q_meas_2         = S_res2(:,4);

    % SG-filter current and position
    filt_current_1 = sgolayfilt(actual_current_1, K, F);
    filt_current_2 = sgolayfilt(actual_current_2, K, F);
    q_filt_1 = sgolayfilt(q_meas_1, K, F);
    q_filt_2 = sgolayfilt(q_meas_2, K, F);

    N = numel(q_meas_1);
    t = (0:N-1).' * dt;

    tau_meas = [Kt1 * filt_current_1, Kt2 * filt_current_2];
    q_meas   = [q_filt_1, q_filt_2];

    % Build struct with SG derivatives
    data = dataset_to_iddata_2dof(t, q_meas, tau_meas, dt, K, F);
end

function data = dataset_to_iddata_2dof(t, q_meas, tau_meas, dt, K, F)
    N = size(q_meas, 1);
    data.t        = t(:).';
    data.q_meas   = q_meas.';      % 2xN
    data.tau_meas = tau_meas.';     % 2xN
    data.dt       = dt;
    data.q_filt   = zeros(2, N);
    data.qd_filt  = zeros(2, N);
    data.qdd_filt = zeros(2, N);

    [~, g] = sgolay(K, F);
    d1 = flipud(g(:,2)) / dt;
    d2 = flipud(g(:,3)) / (dt^2);

    for j = 1:2
        q_filt_j = sgolayfilt(q_meas(:,j), K, F);
        data.q_filt(j,:)   = q_filt_j(:).';
        data.qd_filt(j,:)  = conv(q_filt_j, d1, 'same').';
        data.qdd_filt(j,:) = conv(q_filt_j, d2, 'same').';
    end
end