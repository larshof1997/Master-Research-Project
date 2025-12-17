clc; clear all;
%% Check results
%Load dataset
S = load('planar_2dof_dataset_no_noise_linear_friction.mat');
dataset = S.dataset;

% Choose a run to validate on (change this index if you like)
run_idx = 5;
r = dataset.runs(run_idx);

t  = r.time;               % time vector (Nx1)
dt = t(2) - t(1);
N  = numel(t);

tau_applied = r.u_applied; % Nx2, the torque that actually drove the plant
x_true      = r.x_true;    % Nx4, "real" state: [th1 th2 dth1 dth2]
p_true      = r.p;

%% Physical constants (same as in your simulator)
m1 = 1.6537;  l1 = 0.343;  r1 = 0.29;
m2 = 0.9982;  l2 = 0.267;  r2 = 0.175;
dt = t(2) - t(1);

%load python env
pyenv('Version','/Library/Frameworks/Python.framework/Versions/3.11/bin/python3');

% import HNN module 
py.importlib.import_module('HNN_Momentum_Observer');
%Load HNN
py.HNN_Momentum_Observer.load_model();

%Initialize observer
phat = zeros(N,2);

% Preallocate
x_hat = zeros(N,4);      % [q1 q2 qd1 qd2]
x_hat(:,1:2) = x_true(:,1:2); % initial condition
x_hat(1,3:4) = phat(1,:); % initial condition

% x0 = [0.5, -0.3, 0.1, -0.2];
% x_hat(1,1:2) = x0(1,1:2); % initial condition
% x_hat(1,3:4) = x0(1,3:4); % initial condition

% Observer parameters
kappa = 10;
xp = [0 0];  % momentum estimate (\hat p)
xp_dis = [0 0];  % momentum estimate (\hat p)
% compute initial phi
phi = 0;
% Observer input
uo = @(q,ye) -obs.G(q)\ye;
% Observer energy function
ph = @(q,xp,phi) xp + phi*q;
% Observer dynamics
% dxp = @(q,ph,u,uo,phi) (S - D - phi*eye(2)/Ti)*ph + G*(u + uo);
Hp = @(p,ph) 0.5*(p-ph).'*(p-ph);
% initial conditions 
switchCond = @(q,ph,phi, Sbar, Ti) min(eig(phi*eye(2)/Ti - 0.5*(Sbar + Sbar'))) - kappa;
uo = zeros(size(tau_applied));
%Simulate
for k = 1:N
    x = x_true(k,1:2);
    phat = ph(x_true(k,1:2),xp, phi);
    x_py = py.numpy.array([x phat], pyargs('dtype','float32'));
    %Get Observer matrices
    out = py.HNN_Momentum_Observer.observer_matrices(x_py);
    out_mat = struct(out);
    S = py2mat(out_mat.S);
    Sbar = py2mat(out_mat.Sbar);
    D = py2mat(out_mat.D);
    G = py2mat(out_mat.G);
    T = py2mat(out_mat.T);
    Ti = py2mat(out_mat.Ti);

    if k >0
        % compute initial phi
        while switchCond(x_true(k,1:2),phat,phi, Sbar, Ti) <= 0
            phi = phi + kappa;
            phat = phat - kappa*x_true(k,1:2);
        end
    end

    % % Predict NN
    % x = py.numpy.array([0.5, -0.3, 0.1, -0.2], pyargs('dtype','float32'));
    % x_next_py = py.HNN_Momentum_Observer.predict_next(x_py, dt, tau_applied(k,:));
    % x_next_mat = cellfun(@double, cell(x_next_py.tolist()));
    % x = x_next_mat(1:2);

    %Control input
    u = tau_applied(k,:);
    %Update Observer
    n = numel(x_true(k,1:2));
    dxp = (S - D - phi*eye(n)/Ti) * phat' + G * (u + uo(k,:))'; 
    xp = xp + dt * dxp';         % simple Euler step; replace with RK4 if needed
    
    %Store
    x_hat(k,3:4) = Ti*phat';
    
end


%% Plots: true vs identified model

figure('Color','w','Name','Joint angles: true vs identified');
subplot(2,1,1); hold on; grid on;
plot(t, x_true(:,1), 'b', 'LineWidth', 1.5);
plot(t, x_hat(:,1),  'r--', 'LineWidth', 1.5);
xlabel('Time [s]'); ylabel('theta_1 [rad]');
legend('true','identified','Location','best');
title('Joint 1 angle');


subplot(2,1,2); hold on; grid on;
plot(t, x_true(:,2), 'b', 'LineWidth', 1.5);
plot(t, x_hat(:,2),  'r--', 'LineWidth', 1.5);
xlabel('Time [s]'); ylabel('theta_2 [rad]');
legend('true','identified','Location','best');
title('Joint 2 angle');
figure('Color','w','Name','Joint momentum: true vs identified');
subplot(2,1,1); hold on; grid on;
plot(t, p_true(:,1), 'b', 'LineWidth', 1.5);
plot(t, x_hat(:,3),  'r--', 'LineWidth', 1.5);
ylim(2*[-abs(min(p_true(:,1))) max(p_true(:,1))]);   % <-- one extra line
xlabel('Time [s]'); 
legend('true','identified','Location','best');
title('Joint 1 momentum');

subplot(2,1,2); hold on; grid on;
plot(t, p_true(:,2), 'b', 'LineWidth', 1.5);
plot(t, x_hat(:,4),  'r--', 'LineWidth', 1.5);
ylim(2*[-abs(min(p_true(:,2))) max(p_true(:,2))]);   % <-- one extra line
xlabel('Time [s]'); 
legend('true','identified','Location','best');
title('Joint 2 momentum');

% figure('Color','w','Name','Joint Torques');
% subplot(2,1,1); hold on; grid on;
% plot(t, tau_applied(:,1), 'b', 'LineWidth', 1.5);
% xlabel('Time [s]'); 
% legend('true','Location','best');
% title('Joint 1 Torque');
% 
% subplot(2,1,2); hold on; grid on;
% plot(t, tau_applied(:,2), 'b', 'LineWidth', 1.5);
% xlabel('Time [s]'); 
% legend('true','Location','best');
% title('Joint 2 Torque');

function A = py2mat(A)
    A = cellfun(@double, cell(A.tolist()), 'UniformOutput', false);
    A = cell2mat(A);
    n = sqrt(length(A));
    A = reshape(A, n, n);
end