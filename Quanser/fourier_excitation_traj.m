%% OPTIMIZE_EXCITATION_2DOF
%  Fourier excitation trajectory optimisation for IDIM-OLS identification
%  of the Quanser 2DSFLE (2-DOF planar manipulator with harmonic drives).
%  Based on Swevers et al., IEEE Trans. Robotics, 1997.

clear; clc; close all;

%% 1. SETTINGS
Nf    = 9;
T     = 30;
omega = 2*pi / T;

% Per-joint limits [joint1; joint2]
%   Joint 1: Maxon 273759 + HD 100:1
%   Joint 2: Maxon 118752 + HD  50:1
q_max   = deg2rad([70; 70]);
qd_max  = deg2rad([90; 300]);
qdd_max = deg2rad([600; 400]);

Ns     = 200;
t_s    = linspace(0, T, Ns+1);  t_s(end) = [];
Ts     = 0.01;
t_save = 0:Ts:T-Ts;
v_eps  = 0.1;
l1     = 0.3493;

% Optimisation
N_restarts  = 5;
use_Dopt    = false;     % false = condition number (recommended)
lambda_asym = 15.0;       % anti-symmetry penalty weight


%% 2. SIZES
% Decision vector per joint: [a1..aNf, b1..bNf]  (q0 is NOT free)
n_pj    = 2*Nf;
n_var   = 2 * n_pj;
n_param = 7;

fprintf('2-DOF Fourier trajectory optimisation (Swevers 1997)\n');
fprintf('  Nf=%d, T=%.0fs, omega=%.3f rad/s\n', Nf, T, omega);
fprintf('  %d decision vars, %d base params\n', n_var, n_param);
fprintf('  J1: q±%.0f° qd±%.0f°/s qdd±%.0f°/s²\n', rad2deg(q_max(1)), rad2deg(qd_max(1)), rad2deg(qdd_max(1)));
fprintf('  J2: q±%.0f° qd±%.0f°/s qdd±%.0f°/s²\n', rad2deg(q_max(2)), rad2deg(qd_max(2)), rad2deg(qdd_max(2)));
fprintf('  q(0) = [0, 0] enforced\n');
fprintf('  Criterion: %s + anti-symmetry (lambda=%.1f)\n\n', ...
    tern(use_Dopt,'D-optimal','cond number'), lambda_asym);

%% 3. MULTI-START OPTIMISATION
best_J = Inf;
best_x = [];

opts = optimoptions('fmincon', ...
    'Algorithm','sqp', 'MaxFunctionEvaluations',80000, ...
    'MaxIterations',5000, 'ConstraintTolerance',1e-6, ...
    'OptimalityTolerance',1e-6, 'Display','iter-detailed');

for r = 1:N_restarts
    fprintf('========== Restart %d / %d ==========\n', r, N_restarts);
    x0 = make_x0(r, Nf, n_pj);

    try
        [xo, Jo, ef] = fmincon( ...
            @(x) objective(x,Nf,omega,t_s,v_eps,use_Dopt,n_param,lambda_asym), ...
            x0,[],[],[],[],[],[], ...
            @(x) constraints(x,Nf,omega,t_s,q_max,qd_max,qdd_max), opts);
        fprintf('  exit=%d  J=%.4f\n\n', ef, Jo);
        if Jo < best_J, best_J = Jo; best_x = xo; end
    catch ME
        fprintf('  FAILED: %s\n\n', ME.message);
    end
end

%% 4. ANALYSE RESULT
[q0_1,a1,b1] = unpack(best_x(1:n_pj), Nf, omega);
[q0_2,a2,b2] = unpack(best_x(n_pj+1:end), Nf, omega);

[q1,qd1,qdd1] = ftraj(q0_1,a1,b1,omega,Nf,t_save);
[q2,qd2,qdd2] = ftraj(q0_2,a2,b2,omega,Nf,t_save);

[q1s,qd1s,qdd1s] = ftraj(q0_1,a1,b1,omega,Nf,t_s);
[q2s,qd2s,qdd2s] = ftraj(q0_2,a2,b2,omega,Nf,t_s);
Y = regressor(q1s,q2s,qd1s,qd2s,qdd1s,qdd2s,v_eps);

sv = svd(Y);
cn = sv(1)/sv(end);

fprintf('\n==== RESULTS ====\n');
fprintf('Best objective: %.4f\n', best_J);
fprintf('Condition number: %.2f\n', cn);
fprintf('Singular values:'); fprintf(' %.3f', sv); fprintf('\n');
fprintf('q(0) = [%.4f, %.4f] rad = [%.2f, %.2f] deg\n', ...
    q1(1), q2(1), rad2deg(q1(1)), rad2deg(q2(1)));

if norm(best_x(1:n_pj)-best_x(n_pj+1:end)) < 0.01
    fprintf('WARNING: joints are near-identical!\n');
end

fprintf('\nJoint 1: q0=%.4f rad (%.1f deg)  [computed for q(0)=0]\n', q0_1, rad2deg(q0_1));
for k=1:Nf, fprintf('  k=%d: a=%+.4f b=%+.4f\n',k,a1(k),b1(k)); end
fprintf('Joint 2: q0=%.4f rad (%.1f deg)  [computed for q(0)=0]\n', q0_2, rad2deg(q0_2));
for k=1:Nf, fprintf('  k=%d: a=%+.4f b=%+.4f\n',k,a2(k),b2(k)); end

fprintf('\nActive harmonics (|a|+|b|>0.01):\n');
for j=1:2
    if j==1, aj=a1; bj=b1; else, aj=a2; bj=b2; end
    act = find(abs(aj)+abs(bj)>0.01);
    if isempty(act), fprintf('  J%d: NONE!\n',j);
    else, fprintf('  J%d:',j); fprintf(' k=%d',act); fprintf('\n'); end
end

%% 5. SAVE
q=[q1(:),q2(:)]; qd=[qd1(:),qd2(:)]; qdd=[qdd1(:),qdd2(:)];

N_delay = round(1/Ts);   % samples in 1 second

% --- Prepend zeros in time direction ---
q   = [zeros(N_delay, size(q,2));   q(1:end-N_delay, :)];
qd  = [zeros(N_delay, size(qd,2));  qd(1:end-N_delay, :)];
qdd = [zeros(N_delay, size(qdd,2)); qdd(1:end-N_delay, :)];

save('trajectory.mat','q','qd','qdd','Ts');
fprintf('\nSaved trajectory.mat (Ts=%.3fs)\n', Ts);

%% 6. PLOTS
figure('Position',[100 100 900 750]);
labels_q   = {'$q_1$ [deg]','$q_2$ [deg]'};
labels_qd  = {'$\dot{q}_1$ [deg/s]','$\dot{q}_2$ [deg/s]'};
labels_qdd = {'$\ddot{q}_1$ [deg/s$^2$]','$\ddot{q}_2$ [deg/s$^2$]'};
data_q   = {q1, q2};   lim_q   = q_max;
data_qd  = {qd1, qd2}; lim_qd  = qd_max;
data_qdd = {qdd1,qdd2}; lim_qdd = qdd_max;

for j=1:2
    subplot(3,2,j);
    plot(t_save,rad2deg(data_q{j}),'b','LineWidth',1.2); hold on;
    yline(rad2deg(lim_q(j)),'r--'); yline(-rad2deg(lim_q(j)),'r--');
    ylabel(labels_q{j},'Interpreter','latex'); grid on;
    if j==1, title('Joint 1','Interpreter','latex');
    else, title('Joint 2','Interpreter','latex'); end

    subplot(3,2,2+j);
    plot(t_save,rad2deg(data_qd{j}),'b','LineWidth',1.2); hold on;
    yline(rad2deg(lim_qd(j)),'r--'); yline(-rad2deg(lim_qd(j)),'r--');
    ylabel(labels_qd{j},'Interpreter','latex'); grid on;

    subplot(3,2,4+j);
    plot(t_save,rad2deg(data_qdd{j}),'b','LineWidth',1.2); hold on;
    yline(rad2deg(lim_qdd(j)),'r--'); yline(-rad2deg(lim_qdd(j)),'r--');
    ylabel(labels_qdd{j},'Interpreter','latex');
    xlabel('Time [s]','Interpreter','latex'); grid on;
end
sgtitle('Optimised Excitation Trajectory','Interpreter','latex','FontSize',14);

figure('Position',[1050 100 450 350]);
bar(sv,'FaceColor',[0.2 0.5 0.8]);
xlabel('Index','Interpreter','latex'); ylabel('Singular value','Interpreter','latex');
title(sprintf('cond(Y) = %.1f', cn),'Interpreter','latex'); grid on;

figure('Position',[1050 500 450 400]);
plot(rad2deg(q1),rad2deg(q2),'b','LineWidth',1.2); hold on;
plot(rad2deg(q1(1)),rad2deg(q2(1)),'go','MarkerSize',10,'LineWidth',2);
xlabel('$q_1$ [deg]','Interpreter','latex');
ylabel('$q_2$ [deg]','Interpreter','latex');
title('Configuration space','Interpreter','latex'); axis equal; grid on;

fprintf('\nDone.\n');

%% ====================================================================
%  FUNCTIONS
%  ====================================================================

function s = tern(cond,a,b)
    if cond, s=a; else, s=b; end
end

% Unpack: decision vector = [a1..aNf, b1..bNf], q0 computed for q(0)=0
function [q0,a,b] = unpack(xj, Nf, omega)
    a  = xj(1:Nf);
    b  = xj(Nf+1:2*Nf);
    q0 = -sum(b(:) ./ ((1:Nf)'*omega));  % enforces q(0) = 0
end

% Swevers 1997 Fourier trajectory
function [q,qd,qdd] = ftraj(q0,a,b,w,Nf,t)
    q=q0*ones(size(t)); qd=zeros(size(t)); qdd=zeros(size(t));
    for k=1:Nf
        kw=k*w; s=sin(kw*t); c=cos(kw*t);
        q   = q   + (a(k)/kw)*s + (b(k)/kw)*c;
        qd  = qd  + a(k)*c - b(k)*s;
        qdd = qdd + kw*(-a(k)*s - b(k)*c);
    end
end

% Regressor: theta = [ZZ1, ZZ2, L2, fc1, fv1, fc2, fv2]
function Y = regressor(q1,q2,qd1,qd2,qdd1,qdd2,v_eps)
    N = length(q1);
    Y = zeros(2*N, 7);
    for i=1:N
        r1=2*i-1; r2=2*i;
        c2=cos(q2(i)); s2=sin(q2(i));
        Y(r1,:) = [qdd1(i), qdd2(i), ...
                   2*c2*qdd1(i)+c2*qdd2(i)-s2*(2*qd1(i)*qd2(i)+qd2(i)^2), ...
                   tanh(qd1(i)/v_eps), qd1(i), 0, 0];
        Y(r2,:) = [0, qdd1(i)+qdd2(i), ...
                   c2*qdd1(i)+s2*qd1(i)^2, ...
                   0, 0, tanh(qd2(i)/v_eps), qd2(i)];
    end
end

function J = objective(x, Nf, w, t_s, v_eps, use_Dopt, np, lambda_asym)
    npj = 2*Nf;
    [q01,a1,b1] = unpack(x(1:npj), Nf, w);
    [q02,a2,b2] = unpack(x(npj+1:end), Nf, w);
    [q1,qd1,qdd1] = ftraj(q01,a1,b1,w,Nf,t_s);
    [q2,qd2,qdd2] = ftraj(q02,a2,b2,w,Nf,t_s);
    Y = regressor(q1,q2,qd1,qd2,qdd1,qdd2,v_eps);

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

function [c, ceq] = constraints(x, Nf, w, t_s, q_max, qd_max, qdd_max)
    npj = 2*Nf;
    [q01,a1,b1] = unpack(x(1:npj), Nf, w);
    [q02,a2,b2] = unpack(x(npj+1:end), Nf, w);
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

function x0 = make_x0(idx, Nf, npj)
    x0 = zeros(2*npj, 1);
    switch mod(idx-1, 5)
        case 0  % J1 low harmonics, J2 high
            for k=1:min(3,Nf)
                x0(k)=randn*0.4; x0(Nf+k)=randn*0.4;
            end
            for k=max(1,Nf-2):Nf
                x0(npj+k)=randn*0.4; x0(npj+Nf+k)=randn*0.4;
            end
        case 1  % opposite signs
            x0(1:npj) = rand(npj,1)*0.5;
            x0(npj+1:end) = -rand(npj,1)*0.5;
        case 2  % J1 broadband, J2 single harmonic
            x0(1:npj) = randn(npj,1)*0.3;
            k=randi(Nf); x0(npj+k)=randn*0.8; x0(npj+Nf+k)=randn*0.8;
        case 3  % phase shifted
            for k=1:Nf
                amp=rand*0.5; phi=rand*2*pi;
                x0(k)=amp*cos(phi); x0(Nf+k)=amp*sin(phi);
                phi2=phi+pi/2+rand*pi/2;
                x0(npj+k)=amp*cos(phi2); x0(npj+Nf+k)=amp*sin(phi2);
            end
        case 4  % fully random
            x0 = randn(2*npj,1)*0.3;
    end
end