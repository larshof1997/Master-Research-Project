%% OPTIMIZE_EXCITATION_2DOF
%  Optimises Fourier-series excitation trajectory for the IDIM-OLS
%  identification of a 2-DOF planar manipulator.

clear; clc; close all;

%% ====================================================================
%  1. USER SETTINGS
%  ====================================================================

% --- Fourier trajectory parameters ---
Nf    = 5;              % number of harmonics per joint
T     = 10;             % fundamental period [s]
omega = 2*pi / T;       % fundamental pulsation [rad/s]

% --- Physical constraints ---
q_max   = deg2rad(85);  % position limit [rad] (5 deg safety margin)
qd_max  = deg2rad(300); % velocity limit  [rad/s]  (adjust to your robot)
qdd_max = deg2rad(600); % acceleration limit [rad/s^2]

% --- Sampling for optimisation ---
Ns   = 100;             % number of sample points per period for optimisation
t_s  = linspace(0, T, Ns+1);  t_s(end) = [];  % one period, no overlap

% --- Desired sample time for Simulink trajectory ---
Ts = 0.01;              % 0.01 s sample time
t_save = 0:Ts:T-Ts;     % high-resolution time vector

% --- Friction model ---
v_eps = 0.1;            % tanh smoothing parameter [rad/s]

% --- Optimisation ---
N_restarts = 5;         % number of random initialisations
use_Dopt   = true;      % true = D-optimality,  false = cond. number

%% ====================================================================
%  2. DECISION VARIABLE LAYOUT
% ====================================================================
n_per_joint = 1 + 2*Nf;
n_var       = 2 * n_per_joint;

fprintf('Fourier trajectory optimisation for 2-DOF manipulator\n');
fprintf('  Harmonics Nf = %d,  Period T = %.1f s\n', Nf, T);
fprintf('  Decision variables: %d\n', n_var);
fprintf('  Position limit: +/- %.1f deg\n', rad2deg(q_max));
fprintf('  Sample points per period (optimization) : %d\n\n', Ns);

%% ====================================================================
%  7. MULTI-START OPTIMISATION
% ====================================================================
best_J = Inf;
best_x = [];

fprintf('Running %d random restarts ...\n\n', N_restarts);

opts = optimoptions('fmincon', ...
    'Algorithm',           'sqp', ...
    'MaxFunctionEvaluations', 50000, ...
    'MaxIterations',       3000, ...
    'ConstraintTolerance', 1e-6, ...
    'OptimalityTolerance', 1e-6, ...
    'Display',             'iter-detailed', ...
    'SpecifyObjectiveGradient', false);

for restart = 1:N_restarts
    fprintf('========== Restart %d / %d ==========\n', restart, N_restarts);

    x0 = zeros(n_var, 1);
    for joint = 1:2
        idx0 = (joint-1)*n_per_joint + 1;
        x0(idx0) = (rand - 0.5) * 0.6;                  % q0
        x0(idx0+1 : idx0+2*Nf) = (rand(2*Nf,1)-0.5)*0.3; % a,b
    end

    obj_fun = @(x) objective(x, Nf, omega, t_s, v_eps, use_Dopt);
    con_fun = @(x) constraints(x, Nf, omega, t_s, q_max, qd_max, qdd_max);

    try
        [x_opt, J_opt, exitflag, output] = fmincon(obj_fun, x0, ...
            [], [], [], [], [], [], con_fun, opts);

        fprintf('  Exit flag: %d,  Objective: %.4f\n\n', exitflag, J_opt);

        if J_opt < best_J
            best_J = J_opt;
            best_x = x_opt;
        end
    catch ME
        fprintf('  Optimisation failed: %s\n\n', ME.message);
    end
end

fprintf('\n====================================\n');
fprintf('Best objective value: %.4f\n', best_J);

%% ====================================================================
%  8. EVALUATE AND ANALYSE BEST TRAJECTORY
% ====================================================================
[q0_1, a1, b1] = unpack_joint(best_x(1:n_per_joint),              Nf);
[q0_2, a2, b2] = unpack_joint(best_x(n_per_joint+1:2*n_per_joint), Nf);

[q1, qd1, qdd1] = fourier_traj(q0_1, a1, b1, omega, Nf, t_save);
[q2, qd2, qdd2] = fourier_traj(q0_2, a2, b2, omega, Nf, t_save);

% Build regressor on optimisation grid (for condition number analysis)
[q1_s, qd1_s, qdd1_s] = fourier_traj(q0_1, a1, b1, omega, Nf, t_s);
[q2_s, qd2_s, qdd2_s] = fourier_traj(q0_2, a2, b2, omega, Nf, t_s);
Y_stack = build_regressor(q1_s, q2_s, qd1_s, qd2_s, qdd1_s, qdd2_s, v_eps);

sv = svd(Y_stack);
cond_num = sv(1)/sv(end);
fprintf('Condition number of Y_stack: %.2f\n', cond_num);
fprintf('Singular values: '); fprintf('%.4f  ', sv); fprintf('\n');

%% ====================================================================
%  9. DISPLAY OPTIMISED FOURIER COEFFICIENTS
% ====================================================================
fprintf('\n--- Optimised Fourier coefficients ---\n');
fprintf('Joint 1:  q0 = %+.4f rad (%+.2f deg)\n', q0_1, rad2deg(q0_1));
for k = 1:Nf
    fprintf('  k=%d:  a = %+.4f,  b = %+.4f\n', k, a1(k), b1(k));
end
fprintf('Joint 2:  q0 = %+.4f rad (%+.2f deg)\n', q0_2, rad2deg(q0_2));
for k = 1:Nf
    fprintf('  k=%d:  a = %+.4f,  b = %+.4f\n', k, a2(k), b2(k));
end

q   = [q1(:), q2(:)];
qd  = [qd1(:), qd2(:)];
qdd = [qdd1(:), qdd2(:)];

save('trajectory.mat', 'q', 'qd', 'qdd', 'Ts');
disp('Trajectory saved to trajectory.mat with Ts = 0.01 s');

%% ====================================================================
% 10. PLOTS
% ====================================================================
figure('Name','Optimised Excitation Trajectory','Position',[100 100 900 750]);

subplot(3,2,1);
plot(t_save, rad2deg(q1), 'b', 'LineWidth', 1.2); hold on;
yline(rad2deg(q_max),'r--','LineWidth',1); yline(-rad2deg(q_max),'r--','LineWidth',1);
ylabel('$q_1$ [deg]','Interpreter','latex'); title('Joint 1','Interpreter','latex'); grid on;

subplot(3,2,2);
plot(t_save, rad2deg(q2), 'b', 'LineWidth', 1.2); hold on;
yline(rad2deg(q_max),'r--','LineWidth',1); yline(-rad2deg(q_max),'r--','LineWidth',1);
ylabel('$q_2$ [deg]','Interpreter','latex'); title('Joint 2','Interpreter','latex'); grid on;

subplot(3,2,3);
plot(t_save, rad2deg(qd1), 'b', 'LineWidth', 1.2); hold on;
yline(rad2deg(qd_max),'r--','LineWidth',1); yline(-rad2deg(qd_max),'r--','LineWidth',1);
ylabel('$\dot{q}_1$ [deg/s]','Interpreter','latex'); grid on;

subplot(3,2,4);
plot(t_save, rad2deg(qd2), 'b', 'LineWidth', 1.2); hold on;
yline(rad2deg(qd_max),'r--','LineWidth',1); yline(-rad2deg(qd_max),'r--','LineWidth',1);
ylabel('$\dot{q}_2$ [deg/s]','Interpreter','latex'); grid on;

subplot(3,2,5);
plot(t_save, rad2deg(qdd1), 'b', 'LineWidth', 1.2); hold on;
yline(rad2deg(qdd_max),'r--','LineWidth',1); yline(-rad2deg(qdd_max),'r--','LineWidth',1);
ylabel('$\ddot{q}_1$ [deg/s$^2$]','Interpreter','latex'); xlabel('Time [s]','Interpreter','latex'); grid on;

subplot(3,2,6);
plot(t_save, rad2deg(qdd2), 'b', 'LineWidth', 1.2); hold on;
yline(rad2deg(qdd_max),'r--','LineWidth',1); yline(-rad2deg(qdd_max),'r--','LineWidth',1);
ylabel('$\ddot{q}_2$ [deg/s$^2$]','Interpreter','latex'); xlabel('Time [s]','Interpreter','latex'); grid on;

sgtitle('Optimised Fourier Excitation Trajectory','Interpreter','latex','FontSize',14);

figure('Name','Regressor Singular Values','Position',[1050 100 450 350]);
bar(sv,'FaceColor',[0.2 0.5 0.8]);
xlabel('Index','Interpreter','latex'); ylabel('Singular value','Interpreter','latex');
title(sprintf('$\\mathrm{cond}(Y_{\\mathrm{stack}}) = %.1f$',cond_num),'Interpreter','latex','FontSize',13);
grid on;

figure('Name','Configuration Space','Position',[1050 500 450 400]);
plot(rad2deg(q1), rad2deg(q2),'b','LineWidth',1.2); hold on;
plot(rad2deg(q1(1)), rad2deg(q2(1)),'go','MarkerSize',10,'LineWidth',2);
rectangle('Position',[-rad2deg(q_max),-rad2deg(q_max),2*rad2deg(q_max),2*rad2deg(q_max)], ...
    'EdgeColor','r','LineStyle','--','LineWidth',1);
xlabel('$q_1$ [deg]','Interpreter','latex'); ylabel('$q_2$ [deg]','Interpreter','latex');
title('Configuration space coverage','Interpreter','latex'); legend('Trajectory','Start','Joint limits','Interpreter','latex');
axis equal; grid on;

fprintf('\nDone.\n');

%% ====================================================================
%  3. HELPER FUNCTIONS
% ====================================================================
function [q0,a,b] = unpack_joint(x_joint,Nf)
    q0 = x_joint(1);
    a  = x_joint(2:Nf+1);
    b  = x_joint(Nf+2:2*Nf+1);
end

function [q,qd,qdd] = fourier_traj(q0,a,b,omega,Nf,t)
    q   = q0*ones(size(t));
    qd  = zeros(size(t));
    qdd = zeros(size(t));
    for k=1:Nf
        s_k = sin(k*omega*t);
        c_k = cos(k*omega*t);
        q   = q   + a(k)*s_k + b(k)*c_k;
        qd  = qd  + k*omega*(a(k)*c_k - b(k)*s_k);
        qdd = qdd - (k*omega)^2*(a(k)*s_k + b(k)*c_k);
    end
end

function Y_stack = build_regressor(q1,q2,qd1,qd2,qdd1,qdd2,v_eps)
    N = length(q1);
    Y_stack = zeros(2*N,6);
    for i=1:N
        row1 = 2*(i-1)+1;
        row2 = 2*(i-1)+2;
        Y_stack(row1,:) = [qdd1(i), qdd1(i)+qdd2(i), tanh(qd1(i)/v_eps), 0, qd1(i), 0];
        Y_stack(row2,:) = [0, qdd1(i)+qdd2(i), 0, tanh(qd2(i)/v_eps), 0, qd2(i)];
    end
end

function J = objective(x,Nf,omega,t_s,v_eps,use_Dopt)
    n_pj = 1+2*Nf;
    [q0_1,a1,b1] = unpack_joint(x(1:n_pj), Nf);
    [q0_2,a2,b2] = unpack_joint(x(n_pj+1:2*n_pj), Nf);
    [q1,qd1,qdd1] = fourier_traj(q0_1,a1,b1,omega,Nf,t_s);
    [q2,qd2,qdd2] = fourier_traj(q0_2,a2,b2,omega,Nf,t_s);
    Y_stack = build_regressor(q1,q2,qd1,qd2,qdd1,qdd2,v_eps);
    if use_Dopt
        M = Y_stack'*Y_stack + 1e-10*eye(6);
        J = -log(det(M));
    else
        s = svd(Y_stack);
        if s(end)<1e-12
            J = 1e12;
        else
            J = s(1)/s(end);
        end
    end
end

function [c,ceq] = constraints(x,Nf,omega,t_s,q_max,qd_max,qdd_max)
    n_pj = 1+2*Nf;
    [q0_1,a1,b1] = unpack_joint(x(1:n_pj),Nf);
    [q0_2,a2,b2] = unpack_joint(x(n_pj+1:2*n_pj),Nf);
    [q1,qd1,qdd1] = fourier_traj(q0_1,a1,b1,omega,Nf,t_s);
    [q2,qd2,qdd2] = fourier_traj(q0_2,a2,b2,omega,Nf,t_s);
    c = [q1(:)-q_max; -q1(:)-q_max; q2(:)-q_max; -q2(:)-q_max; ...
         qd1(:)-qd_max; -qd1(:)-qd_max; qd2(:)-qd_max; -qd2(:)-qd_max; ...
         qdd1(:)-qdd_max; -qdd1(:)-qdd_max; qdd2(:)-qdd_max; -qdd2(:)-qdd_max];
    ceq = [];
end
