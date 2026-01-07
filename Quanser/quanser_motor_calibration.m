clear all; close all; clc;

% Directory
data_dir = 'C:\Users\S4236610\Documents\GitHub\Master-Research-Project\Quanser\motor_calibration_data\';

% File lists (keep exact names)
mat_files = {
    'simulink_V05_f1.mat', 'simulink_V05_f2.mat', 'simulink_V05f3.mat', ...
    'simulink_V05_f10.mat', 'simulink_V05_f15.mat', ...
    'simulink_V1_f1.mat', 'simulink_V1_f2.mat', 'simulink_V1_f3.mat', ...
    'simulink_V1_f10.mat', 'simulink_V1_f15.mat'
};

csv_files = {
    'teensy_V05_f1.csv', 'teensy_V05_f2.csv', 'teensy_V05_f3.csv', ...
    'teensy_V05_f10.csv', 'teensy_V05_f15.csv', ...
    'teensy_V1_f1.csv', 'teensy_V1_f2.csv', 'teensy_V1_f3.csv', ...
    'teensy_V1_f10.csv', 'teensy_V1_f15.csv'
};
% 
% File lists (keep exact names)
% mat_files = {
%      'simulink_V05_f1.mat', 'simulink_V05_f2.mat'
% %     'simulink_V05_f1.mat', 'simulink_V05_f2.mat',...
% %     'simulink_V1_f1.mat', 'simulink_V1_f2.mat'
% };
% 
% csv_files = {
%     'teensy_V05_f1.csv', 'teensy_V05_f2.csv',
% %     'teensy_V05_f1.csv', 'teensy_V05_f2.csv', ...
% %     'teensy_V1_f1.csv', 'teensy_V1_f2.csv', 
% };

% Hold out frequency 15 Hz for testing
test_freq = 3;
train_idx = ~contains(mat_files, ['f' num2str(test_freq)]);
test_idx  = ~train_idx;

% Torque calibration
a = 1.121303e-03;
b = -5.774345e-01;

train_I = [];  train_tau = [];  train_w = [];
test_I  = [];  test_tau  = [];



for i = 1:length(mat_files)
    % Load torque (teensy)
    csv_data = dlmread(fullfile(data_dir, csv_files{i}), ',', 0, 0);  % change to 1,0 if header
    adc = csv_data(:,2);
    tau = a * adc + b;
    N = length(tau);
    
    % Load current (simulink)
    S = load(fullfile(data_dir, mat_files{i}));
    vars = fieldnames(S);
    data = S.(vars{1});
    if isstruct(data) && isfield(data,'Data')
        I_full = data.Data(:,2);
    else
        I_full = data(:,2);
    end
    I = I_full(end-N:end-1);
   
    
    % Signal alignment using cross-correlation
%     maxLag = 500;
% 
%     [c, lags] = xcorr(I - mean(I), tau - mean(tau), maxLag, 'normalized');
%     [~, idx] = max(c);
%     lag = lags(idx);
% 
%     % If lag > 0: I leads tau  -> shift I backward
%     % If lag < 0: tau lags I   -> shift tau backward
%     if lag > 0
%         tau   = tau(1:end+lag);
%         I = I(-lag+1:end);
%     elseif lag < 0
%         I   = I(1:end+lag);
%         tau = tau(-lag+1:end);
%     end
% 
%     % Ensure equal length (safety)
%     N = length(I);
%     tau = tau(300:end);
%     I = I(300:end);
%     N = length(I);
    
%     figure;
%     hold on
%     plot(I)
%     plot(tau)
%     hold off
    
    if train_idx(i)
        train_I   = [train_I;   I];
        train_tau = [train_tau; tau];
        train_w   = [train_w;   (1/N)*ones(N,1)];  % equal weight per dataset
    else
        test_I    = [test_I;    I];
        test_tau  = [test_tau;  tau];
    end
end



% Weighted linear fit: tau = Kt * I + tau0
mdl = fitlm(train_I, train_tau, 'Intercept',true, 'Weights',train_w);
Kt   = mdl.Coefficients.Estimate(2);
tau0 = mdl.Coefficients.Estimate(1);

disp('=== Torque-Current Calibration ===');
disp(['Kt  (torque constant) = ' num2str(Kt, '%.6f') ' Nm/A']);
disp(['tau0 (offset)         = ' num2str(tau0, '%.6f') ' Nm']);
disp(mdl);

% Test performance
pred_test = predict(mdl, test_I);
rmse_test = sqrt(mean((pred_test - test_tau).^2));
disp(['Test RMSE (f=' num2str(test_freq) ' Hz held out): ' num2str(rmse_test, '%.5f') ' Nm']);

% --- Plots ---
figure('Position',[100 100 1100 500]);

% Training
subplot(1,2,1);
scatter(train_I, train_tau, 8, 'b', 'filled', 'MarkerFaceAlpha',0.4);
hold on;
xfit = linspace(min(train_I), max(train_I), 200)';
yfit = Kt * xfit + tau0;
plot(xfit, yfit, 'r-', 'LineWidth',2);
xlabel('Current I (A)');
ylabel('Torque \tau (Nm)');
title('Training Data + Fit');
legend('Data points', sprintf('Fit: \\tau = %.5f I + %.4f', Kt, tau0), 'Location','best');
grid on;

% Test
subplot(1,2,2);
scatter(test_I, test_tau, 8, 'b', 'filled', 'MarkerFaceAlpha',0.4);
hold on;
[test_I_sorted, sort_idx] = sort(test_I);  % Fixed indexing
plot(test_I_sorted, pred_test(sort_idx), 'r-', 'LineWidth',2);
xlabel('Current I (A)');
ylabel('Torque \tau (Nm)');
title(sprintf('Test (f=%d Hz) - RMSE = %.4f Nm', test_freq, rmse_test));
legend('Test data', 'Prediction', 'Location','best');
grid on;