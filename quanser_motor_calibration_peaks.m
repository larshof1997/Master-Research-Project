clear all; close all; clc;

% ---------- Visual style defaults ----------
set(groot, 'defaultTextInterpreter','latex');
set(groot, 'defaultAxesTickLabelInterpreter','latex');
set(groot, 'defaultLegendInterpreter','latex');

defaultFontSize = 20;
defaultLineWidth = 1.6;
defaultMarkerSize = 36;
set(groot, 'defaultAxesFontSize', defaultFontSize);
set(groot, 'defaultLineLineWidth', defaultLineWidth);

% ---------- Directory ----------
data_dir = '/Users/lars/Documents/GitHub/Master-Research-Project/Quanser/motor_calibration_data/';

mat_files = {
    'simulink_1.mat',...
    'simulink_2.mat'
};

csv_files = {
    'teensy_1.csv',...
    'teensy_2.csv',...
};

% ---------- Torque calibration ----------
a = 1.121303e-03;
b = -5.774345e-01;

% ---------- Storage for extrema ----------
I_peaks_all  = [];
I_vals_all   = [];
tau_peaks_all = [];
tau_vals_all  = [];

dt = 0.01;

for i = 1:length(mat_files)

    % ================= LOAD TORQUE =================
    csv_data = dlmread(fullfile(data_dir, csv_files{i}), ',', 0, 0);
    adc = csv_data(:,2);
    tau_raw = a * adc + b;

    % ================= LOAD CURRENT =================
    S = load(fullfile(data_dir, mat_files{i}));
    vars = fieldnames(S);
    data = S.(vars{1});

    if isstruct(data) && isfield(data,'Data')
        I_full = data.Data(:,2);
    else
        I_full = data(:,2);
    end

    N = min(length(I_full), length(tau_raw));
    I = I_full(end-N+1:end);
    tau_raw = tau_raw(1:N);

    % ================= TRIM TRANSIENT =================
    idx = 300:N-100;
    I = I(idx);
    tau_raw = tau_raw(idx);
    t = (0:length(I)-1)' * dt;

    % ================= SMOOTHING =================
    sg_order = 3;
    sg_window = 51;    % must be odd

    tau_s = sgolayfilt(tau_raw, sg_order, sg_window);
    I_s   = sgolayfilt(I,        sg_order, sg_window);

    % ================= PEAK DETECTION =================
    minDist = round(0.2 / dt);

    prom_tau = 0.02;   % Nm
    prom_I   = 0.05;   % A

    % Torque peaks & valleys
    [tp, lt_p] = findpeaks(tau_s, ...
        'MinPeakDistance', minDist, ...
        'MinPeakProminence', prom_tau);

    [tv, lt_v] = findpeaks(-tau_s, ...
        'MinPeakDistance', minDist, ...
        'MinPeakProminence', prom_tau);
    tv = -tv;

    % Current peaks & valleys
    [Ip, li_p] = findpeaks(I_s, ...
        'MinPeakDistance', minDist, ...
        'MinPeakProminence', prom_I);

    [Iv, li_v] = findpeaks(-I_s, ...
        'MinPeakDistance', minDist, ...
        'MinPeakProminence', prom_I);
    Iv = -Iv;

    % ================= ACCUMULATE =================
    tau_peaks_all = [tau_peaks_all; tp];
    tau_vals_all  = [tau_vals_all;  tv];
    I_peaks_all   = [I_peaks_all;   Ip];
    I_vals_all    = [I_vals_all;    Iv];

    % ================= SANITY PLOT =================
    figure('Color','w','Position',[200 200 900 300]); hold on;
    plot(t, tau_s, 'k');
    plot(t(lt_p), tp, 'ro', 'MarkerSize',8,'LineWidth',1.2);
    plot(t(lt_v), tv, 'bo', 'MarkerSize',8,'LineWidth',1.2);
    grid on; box on;
    xlabel('Time (s)');
    ylabel('Torque (Nm)');
    legend('Smoothed torque','Peaks','Valleys','Location','best');
    title(sprintf('Torque extrema – dataset %d', i));
end

% ================= EXTREMA STATISTICS =================
tau_p = median(tau_peaks_all);
tau_v = median(tau_vals_all);

I_p   = median(I_peaks_all);
I_v   = median(I_vals_all);

tau_p_std = std(tau_peaks_all);
tau_v_std = std(tau_vals_all);

% ================= TORQUE CONSTANT FROM EXTREMA =================
Kt_extrema  = (tau_p - tau_v) / (I_p - I_v);
tau0_extrema = tau_p - Kt_extrema * I_p;

fprintf('\n=== EXTREMA-BASED TORQUE CALIBRATION ===\n');
fprintf('Torque peak      : %.4f ± %.4f Nm\n', tau_p, tau_p_std);
fprintf('Torque valley    : %.4f ± %.4f Nm\n', tau_v, tau_v_std);
fprintf('Current peak     : %.4f A\n', I_p);
fprintf('Current valley   : %.4f A\n', I_v);
fprintf('--------------------------------------\n');
fprintf('Kt  = %.6f Nm/A\n', Kt_extrema);
fprintf('tau0 = %.6f Nm\n', tau0_extrema);

% ================= FINAL CALIBRATION PLOT =================
figure('Color','w','Position',[300 300 500 450]); hold on;

% --- Ensure equal lengths for scatter ---
Np = min(length(I_peaks_all), length(tau_peaks_all));
Nv = min(length(I_vals_all),  length(tau_vals_all));

I_peaks_plot  = I_peaks_all(1:Np);
tau_peaks_plot = tau_peaks_all(1:Np);

I_vals_plot   = I_vals_all(1:Nv);
tau_vals_plot  = tau_vals_all(1:Nv);

scatter(I_peaks_plot, tau_peaks_plot, 50, 'r', 'filled', 'MarkerFaceAlpha',0.6);
scatter(I_vals_plot,  tau_vals_plot,  50, 'b', 'filled', 'MarkerFaceAlpha',0.6);



xfit = linspace(min([I_vals_all; I_peaks_all]), ...
                max([I_vals_all; I_peaks_all]), 100);
yfit = Kt_extrema * xfit + tau0_extrema;

plot(xfit, yfit, 'k', 'LineWidth',2);

grid on; box on;
xlabel('Current (A)');
ylabel('Torque (Nm)');
legend('Positive extrema','Negative extrema', ...
       sprintf('$\\tau = %.4f I %+ .4f$',Kt_extrema,tau0_extrema), ...
       'Interpreter','latex','Location','best');
title('Torque–Current Calibration (Extrema-based)');
