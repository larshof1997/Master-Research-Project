clc; clear all; close all;
%% (N)LS on real experimental setup

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
dt = 1e-2;

data_dir = 'DATA-05-03_2';

%% ===================== TRAJECTORY DEFINITIONS =====================
% Each entry: {trajectory_file, shoulder_file, elbow_file, label}
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
%     'traj_11.mat', 'shoulder_11.mat', 'elbow_11.mat', 'traj\_11';
%     'traj_12.mat', 'shoulder_12.mat', 'elbow_12.mat', 'traj\_12';
};

%% ===================== TRAIN / VAL / TEST SPLIT =====================
% Specify trajectory indices (rows of the table above)
train_idx = [1,2,3,4,5,6,7,8];
val_idx   = [1];
test_idx  = [9,10];

fprintf('Training on:   %s\n', mat2str(train_idx));
fprintf('Validation on: %s\n', mat2str(val_idx));
fprintf('Testing on:    %s\n', mat2str(test_idx));

%% ===================== LOAD HELPER =====================
% Load a single trajectory and return its iddata struct + raw arrays
load_trajectory = @(idx) load_traj_data(data_dir, trajectories(idx,:), Kt1, Kt2, dt, K, F);

%% ===================== BUILD TRAINING SET (concatenated) =====================
fprintf('\n--- Loading training trajectories ---\n');
train_data_cells = cell(1, numel(train_idx));
for i = 1:numel(train_idx)
    [train_data_cells{i}, ~, ~] = load_trajectory(train_idx(i));
    fprintf('  Loaded %s: %d samples\n', trajectories{train_idx(i),4}, size(train_data_cells{i}.q_filt, 2));
end
data_train = concatenate_iddata(train_data_cells);
fprintf('  Total training samples: %d\n', size(data_train.q_filt, 2));

%% ===================== BUILD VALIDATION SET (concatenated) =====================
fprintf('\n--- Loading validation trajectories ---\n');
val_data_cells = cell(1, numel(val_idx));
for i = 1:numel(val_idx)
    [val_data_cells{i}, ~, ~] = load_trajectory(val_idx(i));
    fprintf('  Loaded %s: %d samples\n', trajectories{val_idx(i),4}, size(val_data_cells{i}.q_filt, 2));
end
data_val = concatenate_iddata(val_data_cells);
fprintf('  Total validation samples: %d\n', size(data_val.q_filt, 2));

%% ===================== LOAD TEST TRAJECTORIES (kept separate) =====================
fprintf('\n--- Loading test trajectories ---\n');
test_data   = cell(1, numel(test_idx));
test_q_meas = cell(1, numel(test_idx));
test_tau    = cell(1, numel(test_idx));
for i = 1:numel(test_idx)
    [test_data{i}, test_q_meas{i}, test_tau{i}] = load_trajectory(test_idx(i));
    fprintf('  Loaded %s: %d samples\n', trajectories{test_idx(i),4}, size(test_data{i}.q_filt, 2));
end

%% ===================== LINEAR LS (train on training set) =====================
psi_hat_lin = estimate_theta_ls_2dof(data_train);
fprintf('\n===== Linear LS (viscous only) --- trained on %d trajectories =====\n', numel(train_idx));
fprintf('  a1 = %.6f\n', psi_hat_lin(1));
fprintf('  a2 = %.6f\n', psi_hat_lin(2));
fprintf('  bp = %.6f\n', psi_hat_lin(3));
fprintf('  b1 = %.6f\n', psi_hat_lin(4));
fprintf('  b2 = %.6f\n', psi_hat_lin(5));
fprintf('  det(M) check: a1*a2 = %.6f > bp^2 = %.6f ? %s\n', ...
    psi_hat_lin(1)*psi_hat_lin(2), psi_hat_lin(3)^2, ...
    mat2str(psi_hat_lin(1)*psi_hat_lin(2) > psi_hat_lin(3)^2));

%% ===================== NONLINEAR LS (warm-started, train on training set) =====================
opts = optimoptions('lsqnonlin', ...
    'Display','iter', ...
    'SpecifyObjectiveGradient', true, ...
    'MaxFunctionEvaluations', 1e5, ...
    'FunctionTolerance', 1e-9, ...
    'StepTolerance', 1e-9);

psi0_nls = [psi_hat_lin(1); psi_hat_lin(2); psi_hat_lin(3);
            0.1; 0.1;
            psi_hat_lin(4); psi_hat_lin(5);
            5e-2];

fun = @(psi) residualsEL_analytic_2dof(psi, data_train);
[psi_hat, ~, ~, exitflag, out] = lsqnonlin(fun, psi0_nls, lb, ub, opts);

fprintf('\n===== Nonlinear LS --- trained on %d trajectories =====\n', numel(train_idx));
fprintf('  a1    = %.6f  [kg m^2]\n',   psi_hat(1));
fprintf('  a2    = %.6f  [kg m^2]\n',   psi_hat(2));
fprintf('  bp    = %.6f  [kg m^2]\n',   psi_hat(3));
fprintf('  fc1   = %.6f  [Nm]\n',       psi_hat(4));
fprintf('  fc2   = %.6f  [Nm]\n',       psi_hat(5));
fprintf('  b1    = %.6f  [Nm s/rad]\n', psi_hat(6));
fprintf('  b2    = %.6f  [Nm s/rad]\n', psi_hat(7));
fprintf('  v_eps = %.6f  [rad/s]\n',    psi_hat(8));
fprintf('  det(M) check: a1*a2 = %.6f > bp^2 = %.6f ? %s\n', ...
    psi_hat(1)*psi_hat(2), psi_hat(3)^2, ...
    mat2str(psi_hat(1)*psi_hat(2) > psi_hat(3)^2));

%% ===================== UNPACK PARAMETERS =====================
a1_lin = psi_hat_lin(1);  a2_lin = psi_hat_lin(2);  bp_lin = psi_hat_lin(3);
b1_lin = psi_hat_lin(4);  b2_lin = psi_hat_lin(5);
fc1_lin = 0;  fc2_lin = 0;  v_eps_lin = v_eps;

a1_nls = psi_hat(1);  a2_nls = psi_hat(2);  bp_nls = psi_hat(3);
fc1_nls = psi_hat(4); fc2_nls = psi_hat(5);
b1_nls = psi_hat(6);  b2_nls = psi_hat(7);  v_eps_nls = psi_hat(8);

%% ===================== VALIDATION SET MSE =====================
fprintf('\n==================== VALIDATION SET MSE ====================\n');
[mse_val_lin, mse_val_nls] = evaluate_torque_mse( ...
    data_val, ...
    a1_lin, a2_lin, bp_lin, b1_lin, b2_lin, fc1_lin, fc2_lin, v_eps_lin, ...
    a1_nls, a2_nls, bp_nls, b1_nls, b2_nls, fc1_nls, fc2_nls, v_eps_nls);
fprintf('  Torque MSE (concatenated validation set):\n');
fprintf('              Linear LS          Nonlinear LS\n');
fprintf('  MSE tau1:   %.6e     %.6e\n', mse_val_lin(1), mse_val_nls(1));
fprintf('  MSE tau2:   %.6e     %.6e\n', mse_val_lin(2), mse_val_nls(2));

%% ===================== TEST: PER-TRAJECTORY EVALUATION =====================
fprintf('\n==================== TEST SET RESULTS ====================\n');

set(groot, 'defaultTextInterpreter','latex');
set(groot, 'defaultAxesTickLabelInterpreter','latex');
set(groot, 'defaultLegendInterpreter','latex');
defaultFontSize  = 20;
defaultLineWidth = 1.8;
set(groot, 'defaultAxesFontSize',  defaultFontSize);
set(groot, 'defaultLineLineWidth', defaultLineWidth);

for i = 1:numel(test_idx)
    traj_label = trajectories{test_idx(i), 4};
    d   = test_data{i};
    qm  = test_q_meas{i};   % Nx2
    tm  = test_tau{i};       % Nx2
    N   = size(qm, 1);
    t   = (0:N-1).' * dt;

    fprintf('\n--- %s (%d samples) ---\n', traj_label, N);

    % ---- Forward simulation ----
    x_lin = simulate_forward(N, dt, qm, tm, a1_lin, a2_lin, bp_lin, b1_lin, b2_lin, fc1_lin, fc2_lin, v_eps_lin);
    x_nls = simulate_forward(N, dt, qm, tm, a1_nls, a2_nls, bp_nls, b1_nls, b2_nls, fc1_nls, fc2_nls, v_eps_nls);

    % ---- Torque reconstruction ----
    tau_model_lin = reconstruct_torque(d, a1_lin, a2_lin, bp_lin, b1_lin, b2_lin, fc1_lin, fc2_lin, v_eps_lin);
    tau_model_nls = reconstruct_torque(d, a1_nls, a2_nls, bp_nls, b1_nls, b2_nls, fc1_nls, fc2_nls, v_eps_nls);

    % ---- MSE: forward sim ----
    fprintf('  Forward simulation MSE:\n');
    fprintf('              Linear LS          Nonlinear LS\n');
    fprintf('  MSE q1  :   %.6e     %.6e\n', mean((qm(:,1)-x_lin(:,1)).^2), mean((qm(:,1)-x_nls(:,1)).^2));
    fprintf('  MSE q2  :   %.6e     %.6e\n', mean((qm(:,2)-x_lin(:,2)).^2), mean((qm(:,2)-x_nls(:,2)).^2));
    fprintf('  MSE dq1 :   %.6e     %.6e\n', mean((d.qd_filt(1,:).'-x_lin(:,3)).^2), mean((d.qd_filt(1,:).'-x_nls(:,3)).^2));
    fprintf('  MSE dq2 :   %.6e     %.6e\n', mean((d.qd_filt(2,:).'-x_lin(:,4)).^2), mean((d.qd_filt(2,:).'-x_nls(:,4)).^2));

    % ---- MSE: torque reconstruction ----
    fprintf('  Torque reconstruction MSE:\n');
    fprintf('              Linear LS          Nonlinear LS\n');
    fprintf('  MSE tau1:   %.6e     %.6e\n', mean((tm(:,1)-tau_model_lin(:,1)).^2), mean((tm(:,1)-tau_model_nls(:,1)).^2));
    fprintf('  MSE tau2:   %.6e     %.6e\n', mean((tm(:,2)-tau_model_lin(:,2)).^2), mean((tm(:,2)-tau_model_nls(:,2)).^2));

    % Pack into struct-friendly variables
    true_theta1 = qm(:,1);
    true_theta2 = qm(:,2);
    true_dtheta1 = d.qd_filt(1,:).';
    true_dtheta2 = d.qd_filt(2,:).';

    % LS predictions
    pred_theta1_LS  = x_lin(:,1);
    pred_theta2_LS  = x_lin(:,2);
    pred_dtheta1_LS = x_lin(:,3);
    pred_dtheta2_LS = x_lin(:,4);

    % NLS predictions
    pred_theta1_NLS  = x_nls(:,1);
    pred_theta2_NLS  = x_nls(:,2);
    pred_dtheta1_NLS = x_nls(:,3);
    pred_dtheta2_NLS = x_nls(:,4);

    % Torques
    tau_meas1 = tm(:,1);
    tau_meas2 = tm(:,2);
    tau_LS1   = tau_model_lin(:,1);
    tau_LS2   = tau_model_lin(:,2);
    tau_NLS1  = tau_model_nls(:,1);
    tau_NLS2  = tau_model_nls(:,2);
    % 
    % fname = sprintf('results_LS_NLS_test_%02d.mat', test_idx(i));
    % save(fname, ...
    %     't', 'dt', ...
    %     'true_theta1', 'true_theta2', 'true_dtheta1', 'true_dtheta2', ...
    %     'pred_theta1_LS', 'pred_theta2_LS', 'pred_dtheta1_LS', 'pred_dtheta2_LS', ...
    %     'pred_theta1_NLS', 'pred_theta2_NLS', 'pred_dtheta1_NLS', 'pred_dtheta2_NLS', ...
    %     'tau_meas1', 'tau_meas2', ...
    %     'tau_LS1', 'tau_LS2', 'tau_NLS1', 'tau_NLS2');
    % 
    % fprintf('Saved %s\n', fname);

    % ============================================================
    %  SAVE PER-MODEL RESULTS (forward sim + torque reconstruction)
    %  Replace the existing single save(...) block with this.
    % ============================================================

    % ---- Common ground truth ----
    true_theta1  = qm(:,1);
    true_theta2  = qm(:,2);
    true_dtheta1 = d.qd_filt(1,:).';
    true_dtheta2 = d.qd_filt(2,:).';
    tau_meas1    = tm(:,1);
    tau_meas2    = tm(:,2);

    % ---- Save LS ----
    model_name   = 'LS';
    pred_theta1  = x_lin(:,1);
    pred_theta2  = x_lin(:,2);
    pred_dtheta1 = x_lin(:,3);
    pred_dtheta2 = x_lin(:,4);
    pred_tau1    = tau_model_lin(:,1);
    pred_tau2    = tau_model_lin(:,2);

    fname_ls = sprintf('results_LS_test_%02d.mat', test_idx(i));
    save(fname_ls, ...
        'model_name', 'dt', 't', ...
        'true_theta1', 'true_theta2', 'true_dtheta1', 'true_dtheta2', ...
        'pred_theta1', 'pred_theta2', 'pred_dtheta1', 'pred_dtheta2', ...
        'tau_meas1', 'tau_meas2', 'pred_tau1', 'pred_tau2');
    fprintf('  Saved %s\n', fname_ls);

    % ---- Save NLS ----
    model_name   = 'NLS';
    pred_theta1  = x_nls(:,1);
    pred_theta2  = x_nls(:,2);
    pred_dtheta1 = x_nls(:,3);
    pred_dtheta2 = x_nls(:,4);
    pred_tau1    = tau_model_nls(:,1);
    pred_tau2    = tau_model_nls(:,2);

    fname_nls = sprintf('results_NLS_test_%02d.mat', test_idx(i));
    save(fname_nls, ...
        'model_name', 'dt', 't', ...
        'true_theta1', 'true_theta2', 'true_dtheta1', 'true_dtheta2', ...
        'pred_theta1', 'pred_theta2', 'pred_dtheta1', 'pred_dtheta2', ...
        'tau_meas1', 'tau_meas2', 'pred_tau1', 'pred_tau2');
    fprintf('  Saved %s\n', fname_nls);

    % ---- Plots per test trajectory ----
    % Joint angles
    % fig_ang = figure('Color','w', 'Position',[200 200 900 500]);
    % tiledlayout(2,1, 'Padding','compact', 'TileSpacing','compact');
    % 
    % nexttile;
    % plot(t, qm(:,1), 'b'); hold on;
    % plot(t, x_lin(:,1), 'r--'); plot(t, x_nls(:,1), 'g-.');
    % xlabel('Time $[s]$'); ylabel('$\theta_1$ [rad]');
    % title(sprintf('Joint 1 angle --- %s', traj_label)); grid on; box on;
    % legend('measured','Linear LS','NLS','Location','best','FontSize',defaultFontSize-2);
    % 
    % nexttile;
    % plot(t, qm(:,2), 'b'); hold on;
    % plot(t, x_lin(:,2), 'r--'); plot(t, x_nls(:,2), 'g-.');
    % xlabel('Time $[s]$'); ylabel('$\theta_2$ [rad]');
    % title(sprintf('Joint 2 angle --- %s', traj_label)); grid on; box on;
    % legend('measured','Linear LS','NLS','Location','best','FontSize',defaultFontSize-2);

    % exportgraphics(fig_ang, sprintf('test_%s_angles.png', trajectories{test_idx(i),4}), ...
        % 'Resolution', 300, 'BackgroundColor','white');

    % Torques
    % fig_tau = figure('Color','w', 'Position',[300 300 900 500]);
    % tiledlayout(2,1, 'Padding','compact', 'TileSpacing','compact');
    % 
    % nexttile;
    % plot(t, tm(:,1), 'b'); hold on;
    % plot(t, tau_model_lin(:,1), 'r--'); plot(t, tau_model_nls(:,1), 'g-.');
    % xlabel('Time $[s]$'); ylabel('$\tau_1$ [Nm]');
    % title(sprintf('Joint 1 torque --- %s', traj_label)); grid on; box on;
    % legend('measured','Linear LS','NLS','Location','best','FontSize',defaultFontSize-2);
    % 
    % nexttile;
    % plot(t, tm(:,2), 'b'); hold on;
    % plot(t, tau_model_lin(:,2), 'r--'); plot(t, tau_model_nls(:,2), 'g-.');
    % xlabel('Time $[s]$'); ylabel('$\tau_2$ [Nm]');
    % title(sprintf('Joint 2 torque --- %s', traj_label)); grid on; box on;
    % legend('measured','Linear LS','NLS','Location','best','FontSize',defaultFontSize-2);

    % exportgraphics(fig_tau, sprintf('test_%s_torques.png', trajectories{test_idx(i),4}), ...
        % 'Resolution', 300, 'BackgroundColor','white');
end

%% ===================== ADDITIONAL PLOTS =====================
% Add these to the test loop, or run standalone after the main script.
% Requires: test_data, test_q_meas, test_tau, psi_hat_lin, psi_hat populated.

%% ---------- Plot 1: Velocity comparison (filtered meas vs forward sim) ----------
for i = 1:numel(test_idx)
    traj_label = trajectories{test_idx(i), 4};
    d   = test_data{i};
    qm  = test_q_meas{i};
    tm  = test_tau{i};
    N   = size(qm, 1);
    t   = (0:N-1).' * dt;

    x_lin = simulate_forward(N, dt, qm, tm, a1_lin, a2_lin, bp_lin, b1_lin, b2_lin, fc1_lin, fc2_lin, v_eps_lin);
    x_nls = simulate_forward(N, dt, qm, tm, a1_nls, a2_nls, bp_nls, b1_nls, b2_nls, fc1_nls, fc2_nls, v_eps_nls);

    fig_vel = figure('Color','w', 'Position',[250 250 900 500]);
    tiledlayout(2,1, 'Padding','compact', 'TileSpacing','compact');

    nexttile;
    plot(t, d.qd_filt(1,:), 'b'); hold on;
    plot(t, x_lin(:,3), 'r--'); plot(t, x_nls(:,3), 'g-.');
    xlabel('Time $[s]$'); ylabel('$\dot{\theta}_1$ [rad/s]');
    title(sprintf('Joint 1 velocity --- %s', traj_label)); grid on; box on;
    legend('filtered meas.','Linear LS','NLS','Location','best','FontSize',defaultFontSize-2);

    nexttile;
    plot(t, d.qd_filt(2,:), 'b'); hold on;
    plot(t, x_lin(:,4), 'r--'); plot(t, x_nls(:,4), 'g-.');
    xlabel('Time $[s]$'); ylabel('$\dot{\theta}_2$ [rad/s]');
    title(sprintf('Joint 2 velocity --- %s', traj_label)); grid on; box on;
    legend('filtered meas.','Linear LS','NLS','Location','best','FontSize',defaultFontSize-2);
end

%% ---------- Plot 2: Desired vs filtered derivatives ----------
% Load trajectory files and compare qd_des vs qd_filt, qdd_des vs qdd_filt

% Choose which trajectories to compare (e.g. test set, or all)
compare_idx = test_idx;  % change to 1:12 for all

for i = 1:numel(compare_idx)
    idx = compare_idx(i);
    traj_label = trajectories{idx, 4};

    % Load trajectory file (desired q, qd, qdd)
    S_traj = load(fullfile(data_dir, trajectories{idx, 1}));
    fn = fieldnames(S_traj);
    % Handle both struct-with-fields and direct variable cases
    if numel(fn) == 1 && isstruct(S_traj.(fn{1}))
        S_traj = S_traj.(fn{1});
        q_des   = S_traj.q;
        qd_des  = S_traj.qd;
        qdd_des = S_traj.qdd;
    else
        q_des   = S_traj.q;
        qd_des  = S_traj.qd;
        qdd_des = S_traj.qdd;
    end

    % Load measured + filtered data
    [d, ~, ~] = load_traj_data(data_dir, trajectories(idx,:), Kt1, Kt2, dt, K, F);
    N = size(d.q_filt, 2);
    t = (0:N-1).' * dt;

    % Trim desired to match measured length (in case of off-by-one)
    N_des = min(size(q_des, 1), N);

    % % --- Velocity: desired vs filtered ---
    % fig_qd = figure('Color','w', 'Position',[200 200 900 500]);
    % tiledlayout(2,1, 'Padding','compact', 'TileSpacing','compact');
    % 
    % nexttile;
    % plot(t(1:N_des), qd_des(1:N_des, 1), 'k', 'DisplayName','desired'); hold on;
    % plot(t, d.qd_filt(1,:), 'b--', 'DisplayName','filtered meas.');
    % xlabel('Time $[s]$'); ylabel('$\dot{\theta}_1$ [rad/s]');
    % title(sprintf('Joint 1 velocity: desired vs filtered --- %s', traj_label)); grid on; box on;
    % legend('Location','best','FontSize',defaultFontSize-2);
    % 
    % nexttile;
    % plot(t(1:N_des), qd_des(1:N_des, 2), 'k', 'DisplayName','desired'); hold on;
    % plot(t, d.qd_filt(2,:), 'b--', 'DisplayName','filtered meas.');
    % xlabel('Time $[s]$'); ylabel('$\dot{\theta}_2$ [rad/s]');
    % title(sprintf('Joint 2 velocity: desired vs filtered --- %s', traj_label)); grid on; box on;
    % legend('Location','best','FontSize',defaultFontSize-2);
    % 
    % % --- Acceleration: desired vs filtered ---
    % fig_qdd = figure('Color','w', 'Position',[250 250 900 500]);
    % tiledlayout(2,1, 'Padding','compact', 'TileSpacing','compact');
    % 
    % nexttile;
    % plot(t(1:N_des), qdd_des(1:N_des, 1), 'k', 'DisplayName','desired'); hold on;
    % plot(t, d.qdd_filt(1,:), 'b--', 'DisplayName','filtered meas.');
    % xlabel('Time $[s]$'); ylabel('$\ddot{\theta}_1$ [rad/s$^2$]');
    % title(sprintf('Joint 1 acceleration: desired vs filtered --- %s', traj_label)); grid on; box on;
    % legend('Location','best','FontSize',defaultFontSize-2);
    % 
    % nexttile;
    % plot(t(1:N_des), qdd_des(1:N_des, 2), 'k', 'DisplayName','desired'); hold on;
    % plot(t, d.qdd_filt(2,:), 'b--', 'DisplayName','filtered meas.');
    % xlabel('Time $[s]$'); ylabel('$\ddot{\theta}_2$ [rad/s$^2$]');
    % title(sprintf('Joint 2 acceleration: desired vs filtered --- %s', traj_label)); grid on; box on;
    % legend('Location','best','FontSize',defaultFontSize-2);
end


fprintf('\n==================== DONE ====================\n');

%% ===================== LOCAL FUNCTIONS =====================

function [data, q_meas_out, tau_meas_out] = load_traj_data(data_dir, traj_info, Kt1, Kt2, dt, K, F)
    t_remove = 1;

    % traj_info: {traj_file, shoulder_file, elbow_file, label}
    S_res1 = load(fullfile(data_dir, traj_info{2}));
    fn1 = fieldnames(S_res1);
    S_res1 = S_res1.(fn1{1});
    S_res1 = S_res1(2:end, :);

    S_res2 = load(fullfile(data_dir, traj_info{3}));
    fn2 = fieldnames(S_res2);
    S_res2 = S_res2.(fn2{1});
    S_res2 = S_res2(2:end, :);

    actual_current_1 = S_res1(:,2);
    q_meas_1         = S_res1(:,4);
    actual_current_2 = S_res2(:,2);
    q_meas_2         = S_res2(:,4);

    % ---- Remove first seconds ----
    N_remove = round(t_remove / dt);
    
    actual_current_1 = actual_current_1(N_remove+1:end);
    actual_current_2 = actual_current_2(N_remove+1:end);
    q_meas_1         = q_meas_1(N_remove+1:end);
    q_meas_2         = q_meas_2(N_remove+1:end);

    % % Filter torque 
    % filt_current_1 = sgolayfilt(actual_current_1, K, F);
    % filt_current_2 = sgolayfilt(actual_current_2, K, F);
    filt_current_1 = actual_current_1;
    filt_current_2 = actual_current_2;
    % % Filter position
    q_filt_1 = sgolayfilt(q_meas_1, K, F);
    q_filt_2 = sgolayfilt(q_meas_2, K, F);
    
    N = numel(q_meas_1);
    t = (0:N-1).' * dt;

    tau_meas_out = [Kt1 * filt_current_1, Kt2 * filt_current_2];
    
    q_meas_out   = [q_filt_1, q_filt_2];

    data = dataset_to_iddata_2dof(t, q_meas_out, tau_meas_out, dt, K, F);
end

function data_cat = concatenate_iddata(data_cells)
    % Concatenate multiple iddata structs along the time axis
    data_cat.dt = data_cells{1}.dt;

    t_all     = [];
    q_filt    = [];
    qd_filt   = [];
    qdd_filt  = [];
    tau_meas  = [];
    q_meas    = [];

    for i = 1:numel(data_cells)
        d = data_cells{i};
        t_all    = [t_all,    d.t];         
        q_filt   = [q_filt,   d.q_filt];    
        qd_filt  = [qd_filt,  d.qd_filt];    
        qdd_filt = [qdd_filt, d.qdd_filt];   
        tau_meas = [tau_meas, d.tau_meas];   
        q_meas   = [q_meas,   d.q_meas];    
    end

    data_cat.t        = t_all;
    data_cat.q_filt   = q_filt;
    data_cat.qd_filt  = qd_filt;
    data_cat.qdd_filt = qdd_filt;
    data_cat.tau_meas = tau_meas;
    data_cat.q_meas   = q_meas;
end

function x = simulate_forward(N, dt, q_meas, tau_meas, a1, a2, bp, b1, b2, fc1, fc2, v_eps)
    x = zeros(N, 4);
    x(1,:) = [q_meas(1,1), q_meas(1,2), 0, 0];

    for k = 1:N-1
        h     = dt;
        tau_k = tau_meas(k,:).';
        k1 = f_dyn_2dof(x(k,:).',             tau_k, a1, a2, bp, b1, b2, fc1, fc2, v_eps);
        k2 = f_dyn_2dof(x(k,:).' + 0.5*h*k1, tau_k, a1, a2, bp, b1, b2, fc1, fc2, v_eps);
        k3 = f_dyn_2dof(x(k,:).' + 0.5*h*k2, tau_k, a1, a2, bp, b1, b2, fc1, fc2, v_eps);
        k4 = f_dyn_2dof(x(k,:).' + h*k3,     tau_k, a1, a2, bp, b1, b2, fc1, fc2, v_eps);
        x(k+1,:) = (x(k,:).' + (h/6)*(k1 + 2*k2 + 2*k3 + k4)).';
    end
end

function tau_model = reconstruct_torque(data, a1, a2, bp, b1, b2, fc1, fc2, v_eps)
    N = size(data.q_filt, 2);
    tau_model = zeros(N, 2);

    for k = 1:N
        q_k   = data.q_filt(:,k);
        qd_k  = data.qd_filt(:,k);
        qdd_k = data.qdd_filt(:,k);

        M_k = M_mat(q_k(2), a1, a2, bp);
        C_k = C_mat(q_k(2), qd_k(1), qd_k(2), bp);
        Fv  = [b1*qd_k(1); b2*qd_k(2)];
        Fc  = [fc1*tanh(qd_k(1)/v_eps); fc2*tanh(qd_k(2)/v_eps)];
        tau_model(k,:) = (M_k*qdd_k + C_k*qd_k + Fv + Fc).';
    end
end

function [mse_lin, mse_nls] = evaluate_torque_mse(data, ...
        a1_l, a2_l, bp_l, b1_l, b2_l, fc1_l, fc2_l, veps_l, ...
        a1_n, a2_n, bp_n, b1_n, b2_n, fc1_n, fc2_n, veps_n)

    tau_lin = reconstruct_torque(data, a1_l, a2_l, bp_l, b1_l, b2_l, fc1_l, fc2_l, veps_l);
    tau_nls = reconstruct_torque(data, a1_n, a2_n, bp_n, b1_n, b2_n, fc1_n, fc2_n, veps_n);

    tau_m = data.tau_meas.';  % Nx2
    mse_lin = [mean((tau_m(:,1) - tau_lin(:,1)).^2); mean((tau_m(:,2) - tau_lin(:,2)).^2)];
    mse_nls = [mean((tau_m(:,1) - tau_nls(:,1)).^2); mean((tau_m(:,2) - tau_nls(:,2)).^2)];
end

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

    % SG differentiation kernels
    [~, g] = sgolay(K, F);
    d1 = flipud(g(:,2)) / dt;        % 1st derivative coefficients
    d2 = flipud(g(:,3)) / (dt^2);    % 2nd derivative coefficients (factorial already in sgolay)

    for j = 1:2
        q_filt_j = sgolayfilt(q_meas(:,j), K, F);
        data.q_filt(j,:)   = q_filt_j(:).';
        data.qd_filt(j,:)  = conv(q_filt_j, d1, 'same').';
        data.qdd_filt(j,:) = conv(q_filt_j, d2, 'same').';
    end
    
end

function [r, J] = residualsEL_analytic_2dof(psi, data)
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

        Jk = zeros(2,8);
        Jk(:,1) = -[qdd1; 0];
        Jk(:,2) = -[qdd1+qdd2; qdd1+qdd2];
        Jk(:,3) = -[2*c2*qdd1 + c2*qdd2 - s2*(2*qd1*qd2 + qd2^2);
                     c2*qdd1 + s2*qd1^2];
        Jk(1,4) = -tanh(z1);
        Jk(2,5) = -tanh(z2);
        Jk(1,6) = -qd1;
        Jk(2,7) = -qd2;

        sech2_z1 = 1/cosh(z1)^2;
        sech2_z2 = 1/cosh(z2)^2;
        Jk(1,8) =  fc1 * (qd1 / v_eps^2) * sech2_z1;
        Jk(2,8) =  fc2 * (qd2 / v_eps^2) * sech2_z2;

        J(idx,:) = Jk;
    end
end

function theta_hat = estimate_theta_ls_2dof(data)
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

