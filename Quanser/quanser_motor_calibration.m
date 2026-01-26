clear all; close all; clc;

% ---------- Visual style defaults (LaTeX-friendly, larger fonts) ----------
set(groot, 'defaultTextInterpreter','latex');
set(groot, 'defaultAxesTickLabelInterpreter','latex');
set(groot, 'defaultLegendInterpreter','latex');

% Global plotting defaults you can tweak
defaultFontSize = 20;
defaultLineWidth = 1.6;
defaultMarkerSize = 36;   % used for scatter 'SizeData'
set(groot, 'defaultAxesFontSize', defaultFontSize);
set(groot, 'defaultLineLineWidth', defaultLineWidth);

% Directory
data_dir = '/Users/lars/Documents/GitHub/Master-Research-Project/Quanser/motor_calibration_data/';

% File lists (keep exact names)
mat_files = {
      'simulink_1.mat',...
     'simulink_2.mat'
};

csv_files = {
     'teensy_1.csv',...
     'teensy_2.csv',...
};

% Hold out frequency 15 Hz for testing
test_freq = '1';
train_idx = ~contains(mat_files, test_freq);
test_idx  = ~train_idx;

% Torque calibration
a = 1.121303e-03;
b = -5.774345e-01;

train_I = [];  train_tau = [];  train_w = [];
test_I  = [];  test_tau  = [];

% ---------- Storage for extrema ----------
I_peaks_train  = [];
I_vals_train   = [];
tau_peaks_train = [];
tau_vals_train  = [];

% ---------- Storage for extrema ----------
I_peaks_test  = [];
I_vals_test   = [];
tau_peaks_test = [];
tau_vals_test  = [];

dt = 0.01;

minDist = round(0.2 / dt);

prom_tau = 0.02;   % Nm
prom_I   = 0.05;   % A

for i = 1:length(mat_files)
    % ---------------- Load torque (teensy) ----------------
    csv_data = dlmread(fullfile(data_dir, csv_files{i}), ',', 0, 0);  % change header indices if needed
    adc = csv_data(:,2);
    tau_raw = a * adc + b;

    tau = kalman_filter_tau(tau_raw, dt);
    N = length(tau);

    % ---------------- Load current (simulink) ----------------
    S = load(fullfile(data_dir, mat_files{i}));
    vars = fieldnames(S);
    data = S.(vars{1});
    if isstruct(data) && isfield(data,'Data')
        I_full = data.Data(:,2);
    else
        I_full = data(:,2);
    end
    I = I_full(end-N:end-1);



    % ---------------- Signal alignment (cross-corr) ----------------
    maxLag = 500;
    [c, lags] = xcorr(I - mean(I), tau - mean(tau), maxLag, 'normalized');
    [~, idx] = max(c);
    lag = lags(idx);

    % If lag > 0: I leads tau  -> shift I backward
    % If lag < 0: tau lags I   -> shift tau backward
    if lag > 0
        tau   = tau(1:end+lag);
        I = I(-lag+1:end);
    elseif lag < 0
        I   = I(1:end+lag);
        tau = tau(-lag+1:end);
    end


    % Torque peaks & valleys
    [tp, lt_p] = findpeaks(tau, ...
        'MinPeakDistance', minDist, ...
        'MinPeakProminence', prom_tau);

    [tv, lt_v] = findpeaks(-tau, ...
        'MinPeakDistance', minDist, ...
        'MinPeakProminence', prom_tau);
    tv = -tv;

    % Current peaks & valleys
    [Ip, li_p] = findpeaks(I, ...
        'MinPeakDistance', minDist, ...
        'MinPeakProminence', prom_I);

    [Iv, li_v] = findpeaks(-I, ...
        'MinPeakDistance', minDist, ...
        'MinPeakProminence', prom_I);

   


    % Ensure equal length and trim transient edges
    tau = tau(300:end-100);
    tau_raw = tau_raw(300:end-100+lag);
    I = I(300:end-100);
    N = length(I);

    % ---------------- Per-file time-series plot ----------------
    t = (0:N-1)' * dt;
    fig = figure('Color','w', 'Position',[200 200 900 300]);
    plot(t, I, 'LineWidth', defaultLineWidth, 'DisplayName','Current $I_a$');
    hold on;
    plot(t, tau_raw, 'LineWidth', defaultLineWidth, 'DisplayName','Torque $\tau$');
    plot(t, tau, 'LineWidth', defaultLineWidth, 'DisplayName','Filtered Torque $\hat{\tau}$');
    grid on; box on;
    xlabel('Time (s)', 'Interpreter','latex');
    ylabel('Amplitude', 'Interpreter','latex');
    legend('Location','southeast', 'FontSize', defaultFontSize-2);
    set(gca, 'FontSize', defaultFontSize);
    hold off;

    % ---------------- Accumulate training / test sets ----------------
    if train_idx(i)
        train_I   = [train_I;   I];
        train_tau = [train_tau; tau];
        train_w   = [train_w;   (1/N)*ones(N,1)];  % equal weight per dataset

        tau_peaks_train = [tau_peaks_train; tp];
        tau_vals_train  = [tau_vals_train;  tv];
        I_peaks_train   = [I_peaks_train;   Ip];
        I_vals_train    = [I_vals_train;    Iv];
    else
        test_I    = [test_I;    I];
        test_tau  = [test_tau;  tau];

        tau_peaks_test = [tau_peaks_test; tp];
        tau_vals_test  = [tau_vals_test;  tv];
        I_peaks_test   = [I_peaks_test;   Ip];
        I_vals_test    = [I_vals_test;    Iv];
    end
end

% ================= TORQUE CONSTANT FROM EXTREMA =================
Kt_extrema  = (median(tau_peaks_train) - median(tau_vals_train)) / (median(I_peaks_train) - median(I_vals_train));
tau0_extrema = median(tau_peaks_train) - Kt_extrema * median(I_peaks_train);

fprintf('\n=== EXTREMA-BASED TORQUE CALIBRATION ===\n');
fprintf('--------------------------------------\n');
fprintf('Kt  = %.6f Nm/A\n', Kt_extrema);
fprintf('tau0 = %.6f Nm\n', tau0_extrema);

% ---------------- Weighted linear fit: tau = Kt * I + tau0 ----------------
mdl = fitlm(train_I, train_tau, 'Intercept',true, 'Weights',train_w);
Kt   = mdl.Coefficients.Estimate(2);
tau0 = mdl.Coefficients.Estimate(1);

fprintf('=== Torque-Current Calibration ===\n');
fprintf('Kt  (torque constant) = %.6f Nm/A\n', Kt);
fprintf('tau0 (offset)         = %.6f Nm\n', tau0);
disp(mdl);

% ---------------- Test performance ----------------
pred_test = predict(mdl, test_I);
rmse_test = sqrt(mean((pred_test - test_tau).^2));
fprintf('Test RMSE = %.5f Nm\n', rmse_test);

% ---------------- Plots (training + test) ----------------
fig = figure('Color','w', 'Position',[150 150 1200 520]);
tiledlayout(1,2, 'Padding','compact', 'TileSpacing','compact');

% Training: scatter + fit line
nexttile;
hold on;
s = scatter(train_I, train_tau, defaultMarkerSize, 'filled', 'MarkerFaceAlpha', 0.45);
xfit = linspace(min(train_I), max(train_I), 200)';
yfit = Kt * xfit + tau0;
ph = plot(xfit, yfit, 'r-', 'LineWidth', 2.2);
xlabel('Current $I$ (A)', 'Interpreter','latex');
ylabel('Torque $\tau$ (Nm)', 'Interpreter','latex');
title(sprintf('Train (0.1V, 1Hz) - RMSE = %.4f Nm', mdl.RMSE), 'Interpreter','latex');grid on; box on;
legend([s ph], {'Data points', sprintf('$\\tau = %.6f I  %.6f$', Kt, tau0)}, 'Interpreter','latex', 'Location','best', 'FontSize', defaultFontSize-2);
set(gca, 'FontSize', defaultFontSize);
axis tight;
hold off;

% Test: scatter + predicted curve (sorted)
nexttile;
s2 = scatter(test_I, test_tau, defaultMarkerSize, 'filled', 'MarkerFaceAlpha', 0.45);
hold on;
[test_I_sorted, sort_idx] = sort(test_I);
plot(test_I_sorted, pred_test(sort_idx), 'r-', 'LineWidth', 2.2);
xlabel('Current $I$ (A)', 'Interpreter','latex');
ylabel('Torque $\tau$ (Nm)', 'Interpreter','latex');
title(sprintf('Test (0.2V, 1Hz) - RMSE = %.4f Nm', rmse_test), 'Interpreter','latex');
grid on; box on;
legend('Test data', 'Prediction', 'Location','best', 'Interpreter','latex', 'FontSize', defaultFontSize-2);
set(gca, 'FontSize', defaultFontSize);
axis tight;
hold off;

% ================= PEAK-BASED PLOTS (EXTREMA FIT) =================
fig = figure('Color','w', 'Position',[150 150 1200 520]);
tiledlayout(1,2, 'Padding','compact', 'TileSpacing','compact');

% ---------------- TRAINING PEAK DATA ----------------
Np_tr = min(length(I_peaks_train), length(tau_peaks_train));
Nv_tr = min(length(I_vals_train),  length(tau_vals_train));

I_ext_train   = [ I_peaks_train(1:Np_tr) ; I_vals_train(1:Nv_tr) ];
tau_ext_train = [ tau_peaks_train(1:Np_tr); tau_vals_train(1:Nv_tr) ];

% ---------------- TEST PEAK DATA ----------------
Np_te = min(length(I_peaks_test), length(tau_peaks_test));
Nv_te = min(length(I_vals_test),  length(tau_vals_test));

I_ext_test   = [ I_peaks_test(1:Np_te) ; I_vals_test(1:Nv_te) ];
tau_ext_test = [ tau_peaks_test(1:Np_te); tau_vals_test(1:Nv_te) ];

% ================= TRAIN: PEAKS + EXTREMA FIT =================
nexttile;
hold on;

s = scatter(I_ext_train, tau_ext_train, ...
    defaultMarkerSize+10, 'filled', ...
    'MarkerFaceAlpha',0.65);

xfit = linspace(min(I_ext_train), max(I_ext_train), 200)';
yfit = Kt_extrema * xfit + tau0_extrema;
ph = plot(xfit, yfit, 'r-', 'LineWidth', 2.2);

xlabel('Current $I$ (A)', 'Interpreter','latex');
ylabel('Torque $\tau$ (Nm)', 'Interpreter','latex');
title('Train – Peak-based fit', 'Interpreter','latex');

legend([s ph], ...
    {'Peaks \& valleys', ...
     sprintf('$\\tau = %.6f I %+ .6f$', Kt_extrema, tau0_extrema)}, ...
     'Interpreter','latex', ...
     'Location','best', ...
     'FontSize', defaultFontSize-2);

grid on; box on;
set(gca, 'FontSize', defaultFontSize);
axis tight;
hold off;

% ================= TEST: PEAKS + EXTREMA FIT =================
nexttile;
hold on;

s2 = scatter(I_ext_test, tau_ext_test, ...
    defaultMarkerSize+10, 'filled', ...
    'MarkerFaceAlpha',0.65);

xfit = linspace(min(I_ext_test), max(I_ext_test), 200)';
yfit = Kt_extrema * xfit + tau0_extrema;
plot(xfit, yfit, 'r-', 'LineWidth', 2.2);

xlabel('Current $I$ (A)', 'Interpreter','latex');
ylabel('Torque $\tau$ (Nm)', 'Interpreter','latex');
title('Test – Peak-based fit', 'Interpreter','latex');

legend('Peaks \& valleys', 'Extrema fit', ...
       'Interpreter','latex', ...
       'Location','best', ...
       'FontSize', defaultFontSize-2);

grid on; box on;
set(gca, 'FontSize', defaultFontSize);
axis tight;
hold off;


% Optional: save a high-quality PDF (uncomment if you want to save)
% exportgraphics(fig, fullfile(data_dir, 'torque_current_fit.pdf'), 'ContentType','vector');

% ---------------- Kalman filter function (unchanged) ----------------
function tau_smooth = kalman_filter_tau(tau, dt)

    N = length(tau);

    % State matrices
    F = [1 dt;
         0  1];
    H = [1 0];

    % ---- TUNING PARAMETERS ----
    Q = [1e-7 0;
         0    1e-4];   % process noise (smoothness)
    R = 0.1;          % measurement noise
    % ---------------------------

     % Allocate storage
    x_filt = zeros(2, N);
    P_filt = zeros(2, 2, N);
    x_pred = zeros(2, N);
    P_pred = zeros(2, 2, N);

    % Initial conditions
    x = [tau(1); 0];
    P = eye(2);

    % Forward Kalman filter
    for k = 1:N
        % Prediction
        x_pred(:,k) = F * x;
        P_pred(:,:,k) = F * P * F' + Q;

        % Update
        K = P_pred(:,:,k) * H' / (H * P_pred(:,:,k) * H' + R);
        x = x_pred(:,k) + K * (tau(k) - H * x_pred(:,k));
        P = (eye(2) - K * H) * P_pred(:,:,k);

        % Store
        x_filt(:,k) = x;
        P_filt(:,:,k) = P;
    end

    % RTS backward smoothing
    x_smooth = x_filt;
    P_smooth = P_filt;

    for k = N-1:-1:1
        C = P_filt(:,:,k) * F' / P_pred(:,:,k+1);
        x_smooth(:,k) = x_filt(:,k) + ...
                        C * (x_smooth(:,k+1) - x_pred(:,k+1));
        P_smooth(:,:,k) = P_filt(:,:,k) + ...
                          C * (P_smooth(:,:,k+1) - P_pred(:,:,k+1)) * C';
    end

    % Output: smoothed torque
    tau_smooth = x_smooth(1,:)';
end
