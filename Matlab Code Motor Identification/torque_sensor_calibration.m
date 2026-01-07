
% weight (g) -> teensy measurement (0-1024)
measurements = [712.9 , 680;
    -712.9, 283;
    1726.3, 914;
    1726.3, 915;
    -1726.3, 104;
    -1726.3, 105;
    1537.7, 880;
    1537.7, 879;
    1537.7, 878;
    -1537.7, 152;
    -1537.7, 152;
    1370.2, 840;
    1370.2, 841;
    -1370.2, 187;
    -1370.2, 188;
    1080.9, 767;
    1080.9, 768;
    -1080.9, 260;
    -1080.9, 260;
    878.4, 729;
    878.4, 729;
    -878.4, 310;
    -878.4, 311;
    588.2, 655;
    588.2, 654;
    -588.2, 377;
    -588.2, 375;
    437.4, 619;
    437.4, 619;
    -437.4, 412;
    -437.4, 412;
    339.8, 597;
    339.8, 596;
    -339.8, 436;
    -339.8, 436;
    213.3, 566;
    213.3, 565;
    -213.3, 463;
    -213.3, 465;
    135.8, 549;
    135.8, 550;
    -135.8, 482;
    -135.8, 482;
    88.2, 536;
    88.2, 536;
    -88.2, 494;
    -88.2, 494;
    0, 515;
    0 516;
    0, 515
    0, 515
    ];

%% Compute residuals
torque_est = polyval(p, adc);
residuals = torque_Nm - torque_est;

%% Outlier detection (3-sigma rule)
sigma = std(residuals);
inliers = abs(residuals) < 3*sigma;

fprintf('Removed %d outliers\n', sum(~inliers));

%% Refit using inliers only
p_clean = polyfit(adc(inliers), torque_Nm(inliers), 1);

a_clean = p_clean(1);
b_clean = p_clean(2);

%% Recompute fit
adc_fit = linspace(min(adc), max(adc), 200);
torque_fit_clean = polyval(p_clean, adc_fit);

%% Plot comparison
figure; hold on; grid on;
scatter(adc(inliers), torque_Nm(inliers), 35, 'filled');
scatter(adc(~inliers), torque_Nm(~inliers), 60, 'rx', 'LineWidth', 2);
plot(adc_fit, torque_fit_clean, 'LineWidth', 2);

xlabel('ADC counts (0–1024)');
ylabel('Torque [Nm]');
title('Torque Calibration (Outlier Removed)');
legend('Inliers', 'Outlier(s)', 'Clean linear fit', 'Location', 'best');

%% Display cleaned calibration
fprintf('Clean calibration:\n');
fprintf('Torque [Nm] = %.6e * ADC + %.6e\n', a_clean, b_clean);

