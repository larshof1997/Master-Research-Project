psi0 = [0.05; 0.01; 0.1; 0.1; 0.03; 0.03; 5e-2]; %[I1; I2; fc1; fc2; b1 ; b2 ; v_eps]
v_eps = 1e-3; % smoothing speed [rad/s] for tanh for Linear LS
lb = [0;0;0;0;0;0;0];
ub = [0.5;0.1;0.5;0.5;0.1;0.1;0.1];
opts = optimoptions('lsqnonlin','Display','iter','FiniteDifferenceType','forward', ...
                    'SpecifyObjectiveGradient',false,'MaxFunctionEvaluations',1e5, ...
                    'FunctionTolerance',1e-9,'StepTolerance',1e-9);

S = load('planar_2dof_dataset_gaussian_noise.mat');
dataset = S.dataset;  
% Convert to identification data format
% Filter parameters
F = 251;
K = 2;
data = dataset_to_iddata(dataset, K, F);

t_plot = dataset.time;
idxs = 1:numel(t_plot);

% figure;
% subplot(2,1,1); hold on; grid on;
% plot(t_plot, data.q(1,idxs), 'LineWidth', 1.5);
% plot(t_plot, data.q_filt(1,idxs), '--', 'LineWidth', 1.5);
% xlabel('t [s]'); ylabel('qd_1');
% legend('q true','q filt');
% 
% subplot(2,1,2); hold on; grid on;
% plot(t_plot, data.q(2,idxs), 'LineWidth', 1.5);
% plot(t_plot, data.q_filt(2,idxs), '--', 'LineWidth', 1.5);
% xlabel('t [s]'); ylabel('qd_2');
% legend('q true','q filt');
% 
% figure;
% subplot(2,1,1); hold on; grid on;
% plot(t_plot, data.qd(1,idxs), 'LineWidth', 1.5);
% plot(t_plot, data.qd_filt(1,idxs), '--', 'LineWidth', 1.5);
% xlabel('t [s]'); ylabel('qd_1');
% legend('qd true','qd from diff');
% 
% subplot(2,1,2); hold on; grid on;
% plot(t_plot, data.qd(2,idxs), 'LineWidth', 1.5);
% plot(t_plot, data.qd_filt(2,idxs), '--', 'LineWidth', 1.5);
% xlabel('t [s]'); ylabel('qd_2');
% legend('qd true','qd from diff');
% 
% figure;
% subplot(2,1,1); hold on; grid on;
% plot(t_plot, data.qdd(1,idxs), 'LineWidth', 1.5);
% plot(t_plot, data.qdd_filt(1,idxs), '--', 'LineWidth', 1.5);
% xlabel('t [s]'); ylabel('qdd_1');
% legend('qdd true','qdd from diff');
% 
% subplot(2,1,2); hold on; grid on;
% plot(t_plot, data.qdd(2,idxs), 'LineWidth', 1.5);
% plot(t_plot, data.qdd_filt(2,idxs), '--', 'LineWidth', 1.5);
% xlabel('t [s]'); ylabel('qdd_2');
% legend('qdd true','qdd from diff');


opts = optimoptions('lsqnonlin', ...
    'Display','iter', ...
    'SpecifyObjectiveGradient', true);

%Linear
psi_hat = estimate_theta_ls(data,v_eps);
psi_hat = [psi_hat;v_eps];

%NON-Linear
fun = @(psi) residualsEL_analytic(psi, data);
[psi_hat,~,res,exitflag,out] = lsqnonlin(fun, psi0, lb, ub, opts);

% [psi_hat,~,res,exitflag,out] = lsqnonlin(@(psi) residualsEL(psi, data), psi0, lb, ub, opts);


%% Check results
%Load dataset
S = load('planar_2dof_dataset_gaussian_noise.mat');
dataset = S.dataset;

% Choose a run to validate on (change this index if you like)
run_idx = 1;
r = dataset.runs(run_idx);

t  = r.time;               % time vector (Nx1)
dt = t(2) - t(1);
N  = numel(t);

tau_applied = r.u_applied; % Nx2, the torque that actually drove the plant
x_true      = r.x_true;    % Nx4, "real" state: [th1 th2 dth1 dth2]

%% Physical constants (same as in your simulator)
m1 = 1.6537;  l1 = 0.343;  r1 = 0.29;
m2 = 0.9982;  l2 = 0.267;  r2 = 0.175;

%% Identified parameters
I1_hat  = psi_hat(1);
I2_hat  = psi_hat(2);
fc1_hat = psi_hat(3);
fc2_hat = psi_hat(4);
b1_hat  = psi_hat(5);
b2_hat  = psi_hat(6);
v_eps_hat = psi_hat(7);

% Shorthand inertial constants
a1_hat = m1 * r1^2 + m2 * l1^2 + I1_hat;
a2_hat = m2 * r2^2 + I2_hat;
b_hat  = m2 * l1 * r2;

%% Simulate identified model with same input
x_hat = zeros(N,4);
x_hat(1,:) = x_true(1,:);   % same initial condition as real system

for k = 1:N-1
    tk = t(k);
    h  = dt;

    tau_k = tau_applied(k,:).';  % 2x1 torque at this step

    % RK4 integration step using identified parameters
    k1 = f_dyn_id(tk,       x_hat(k,:).',           tau_k, a1_hat,a2_hat,b_hat, b1_hat,b2_hat, fc1_hat,fc2_hat, v_eps_hat);
    k2 = f_dyn_id(tk+0.5*h, x_hat(k,:).' + 0.5*h*k1, tau_k, a1_hat,a2_hat,b_hat, b1_hat,b2_hat, fc1_hat,fc2_hat, v_eps_hat);
    k3 = f_dyn_id(tk+0.5*h, x_hat(k,:).' + 0.5*h*k2, tau_k, a1_hat,a2_hat,b_hat, b1_hat,b2_hat, fc1_hat,fc2_hat, v_eps_hat);
    k4 = f_dyn_id(tk+h,     x_hat(k,:).' + h*k3,     tau_k, a1_hat,a2_hat,b_hat, b1_hat,b2_hat, fc1_hat,fc2_hat, v_eps_hat);

    x_hat(k+1,:) = x_hat(k,:).' + (h/6)*(k1 + 2*k2 + 2*k3 + k4);
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

figure('Color','w','Name','Joint velocities: true vs identified');
subplot(2,1,1); hold on; grid on;
plot(t, x_true(:,3), 'b', 'LineWidth', 1.5);
plot(t, x_hat(:,3),  'r--', 'LineWidth', 1.5);
xlabel('Time [s]'); ylabel('theta_1 [rad/s]');
legend('true','identified','Location','best');
title('Joint 1 velocity');

subplot(2,1,2); hold on; grid on;
plot(t, x_true(:,4), 'b', 'LineWidth', 1.5);
plot(t, x_hat(:,4),  'r--', 'LineWidth', 1.5);
xlabel('Time [s]'); ylabel('theta_2 [rad/s]');
legend('true','identified','Location','best');
title('Joint 2 velocity');



function dx = f_dyn_id(~, x, tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps)
    % x = [theta1; theta2; dtheta1; dtheta2]
    theta2  = x(2);
    dtheta1 = x(3);
    dtheta2 = x(4);

    M = M_mat(theta2, a1, a2, b);
    C = C_mat(theta2, dtheta1, dtheta2, b);

    % Friction forces (viscous + Coulomb with tanh smoothing)
    F_visc = [b1*dtheta1; b2*dtheta2];
    F_coul = [fc1*tanh(dtheta1/v_eps); fc2*tanh(dtheta2/v_eps)];
    tau_fric = F_visc + F_coul;

    ddq = M \ (tau_applied - C * [dtheta1; dtheta2] - tau_fric);
    dx = [dtheta1; dtheta2; ddq(1); ddq(2)];
end

function M = M_mat(theta2, a1, a2, b)
    c2 = cos(theta2);
    M = [a1 + a2 + 2*b*c2,  a2 + b*c2;
         a2 + b*c2,         a2];
end

function C = C_mat(theta2, dtheta1, dtheta2, b)
    s2 = sin(theta2);
    C = [-b*s2*dtheta2,           -b*s2*(dtheta1 + dtheta2);
          b*s2*dtheta1,            0];
end


function r = residualsEL(psi, data)
    % data: struct with q, qd, qdd, tau_meas, dt, etc.
    % Build M(q,psi), C(q,qd,psi), g(q,psi) from your EL model per sample.

    N = size(data.q_filt, 2);
        
    r = [];
    for k = 1:N
        q  = data.q_filt(:,k); qd = data.qd_filt(:,k); qdd = data.qdd_filt(:,k);

        tau_m = data.tau_meas(:,k);
        [M,C] = eulerLagrangeTerms(q, qd, psi);   % your implementation
        tau_f = frictionTorque(qd, psi);            % viscous + (smoothed) Coulomb
        tau_hat = M*qdd + C*qd + tau_f;
        r = [r; tau_m - tau_hat];
    end
end

function tau_f = frictionTorque(qd, psi)
    fc1 = psi(3);
    fc2 = psi(4);
    b1 = psi(5);
    b2 = psi(6);
    v_eps = psi(7);
    
    % Friction forces (viscous + Coulomb with tanh smoothing)
    F_visc = [b1*qd(1); b2*qd(2)];
    F_coul = [fc1*tanh(qd(1)/v_eps); fc2*tanh(qd(2)/v_eps)];
    tau_f = F_visc + F_coul;
end

function [M,C] = eulerLagrangeTerms(q, qd, psi)
    % System parameters
    m1 = 1.6537;  l1 = 0.343;  r1 = 0.29; 
    m2 = 0.9982;  l2 = 0.267;  r2 = 0.175; 
    
    I1 = psi(1);
    I2 = psi(2);
    
    % Shorthand constants
    a1 = m1 * r1^2 + m2 * l1^2 + I1;
    a2 = m2 * r2^2 + I2;
    b  = m2 * l1 * r2;

    M = M_mat(q(2), a1, a2, b);
    C = C_mat(q(2), qd(1), qd(2), b);
end


function data = dataset_to_iddata(dataset,K, F)
    % dataset: struct with fields .time (Nx1) and .runs(1xR)
    % Each runs(i) has fields x_true (Nx4), ddq_true (Nx2), u_applied (Nx2)

    R = numel(dataset.runs);

    % --- first pass: compute total number of samples ---
    Ni = zeros(1,R);
    for i = 1:R
        Ni(i) = size(dataset.runs(i).x_true,1);  % length of this run
    end
    Ntot = sum(Ni);

    % Preallocate: all as 2 x Ntot
    data.t        = zeros(1, Ntot);
    data.q_meas   = zeros(2, Ntot);
    data.qd_filt  = zeros(2, Ntot);
    data.qdd_filt = zeros(2, Ntot);
    data.q        = zeros(2, Ntot);
    data.qd       = zeros(2, Ntot);
    data.qdd      = zeros(2, Ntot);
    data.tau_meas = zeros(2, Ntot);

    % assume constant dt across runs
    dt = dataset.runs(1).time(2) - dataset.runs(1).time(1);
    data.dt = dt;



    idx = 0;
    idx0 = 0;
    for i = 1:R
        r = dataset.runs(i);
        ti = r.time(:);
        Ni_i = Ni(i);

        for k = 1:Ni_i
            idx = idx + 1;

            xk = r.x_true(k,:);      % [th1 th2 dth1 dth2]
            yk = r.y_meas(k,:);      % [th1 th2 dth1 dth2]
            data.t(idx)       = ti(k);
            data.q_meas(:,idx)       = yk(1:2).';
            data.q(:,idx)     = xk(1:2).';          % [theta1; theta2]
            data.qd(:,idx)    = xk(3:4).';          % [dtheta1; dtheta2]
            data.qdd(:,idx)   = r.ddq(k,:).';  % [ddtheta1; ddtheta2]
            data.tau_meas(:,idx) = r.u_applied(k,:).'; % applied torque as "measured"
        end

        idxs = idx0 + (1:Ni_i);


        data.q_filt1 = sgolayfilt(data.q_meas(1,idxs), K, F);
        data.q_filt2 = sgolayfilt(data.q_meas(2,idxs), K, F);
        data.q_filt = [data.q_filt1;data.q_filt2];

        % fs = 1/dt;
        % fc = 10;        % cutoff freq in Hz — tune this! 
        % order = 6;
        % 
        % [b,a] = butter(order, fc/(fs/2));      % normalized cutoff
        % data.q_filt = filtfilt(b, a, data.q_meas(:,idxs)')';      % preserve row shape

        % central difference for interior points
        for k = 2:Ni_i-1
            j = idxs(k);
            idx_prev = idxs(k-1);
            idx_next = idxs(k+1);

            data.qd_filt(:,j) = (data.q_filt(:,idx_next)-data.q_filt(:,idx_prev)) / (2*data.dt);
        end

        % simple one-sided at the boundaries
        data.qd_filt(:,idxs(1)) = (data.q_filt(:,idxs(2)) - data.q_filt(:,idxs(1))) / data.dt;
        data.qd_filt(:,idxs(end)) = (data.q_filt(:,idxs(end)) - data.q_filt(:,idxs(end-1))) / data.dt;

        data.qd_filt1 = sgolayfilt(data.qd_filt(1,idxs), K, F);
        data.qd_filt2 = sgolayfilt(data.qd_filt(2,idxs), K, F);
        data.qd_filt = [data.qd_filt1;data.qd_filt2];
            
        % then accelerations from those velocities, same idea
        for k = 2:Ni_i-1
            j = idxs(k); idx_prev = idxs(k-1); idx_next = idxs(k+1);
            data.qdd_filt(:,j) = (data.qd_filt(:,idx_next)-data.qd_filt(:,idx_prev)) / (2*data.dt);
        end
        data.qdd_filt(:,idxs(1)) = (data.qd_filt(:,idxs(2))-data.qd_filt(:,idxs(1))) / data.dt;
        data.qdd_filt(:,idxs(end)) = (data.qd_filt(:,idxs(end))-data.qd_filt(:,idxs(end-1))) / data.dt;
        data.qdd_filt1 = sgolayfilt(data.qdd_filt(1,idxs), K, F);
        data.qdd_filt2 = sgolayfilt(data.qdd_filt(2,idxs), K, F);
        data.qdd_filt = [data.qdd_filt1;data.qdd_filt2];
    end
end

function [r,J] = residualsEL_analytic(psi, data)
    % psi = [I1; I2; fc1; fc2; b1; b2; v_eps]

    I1     = psi(1);
    I2     = psi(2);
    fc1    = psi(3);
    fc2    = psi(4);
    b1     = psi(5);
    b2     = psi(6);
    v_eps  = psi(7);

    % fixed physical params
    m1 = 1.6537;  l1 = 0.343;  r1 = 0.29;
    m2 = 0.9982;  l2 = 0.267;  r2 = 0.175;
    b  = m2 * l1 * r2;

    a1 = m1 * r1^2 + m2 * l1^2 + I1;
    a2 = m2 * r2^2 + I2;

    N = size(data.q_filt,2);
    r = zeros(2*N,1);
    J = zeros(2*N,7);

    for k = 1:N
        q   = data.q_filt(:,k);
        qd  = data.qd_filt(:,k);
        qdd = data.qdd_filt(:,k);
        tau_m = data.tau_meas(:,k);

        % --- dynamics terms ---
        theta2  = q(2);
        dtheta1 = qd(1);
        dtheta2 = qd(2);

        c2 = cos(theta2);
        s2 = sin(theta2);

        M = [a1 + a2 + 2*b*c2,  a2 + b*c2;
             a2 + b*c2,         a2];

        C = [-b*s2*dtheta2,           -b*s2*(dtheta1 + dtheta2);
              b*s2*dtheta1,            0];

        % friction
        z1 = qd(1)/v_eps;
        z2 = qd(2)/v_eps;
        F_visc = [b1*qd(1); b2*qd(2)];
        F_coul = [fc1*tanh(z1); fc2*tanh(z2)];
        tau_f  = F_visc + F_coul;

        tau_hat = M*qdd + C*qd + tau_f;
        rk = tau_m - tau_hat;      % 2x1

        idx = 2*(k-1) + (1:2);
        r(idx) = rk;

        % --- analytic Jacobian 2x7 ---
        qdd1 = qdd(1); qdd2 = qdd(2);
        qd1  = qd(1);  qd2  = qd(2);

        Jk = zeros(2,7);

        % d r / d I1
        Jk(:,1) = -[qdd1; 0];

        % d r / d I2
        sI2 = qdd1 + qdd2;
        Jk(:,2) = -[sI2; sI2];

        % d r / d fc1, fc2
        Jk(1,3) = -tanh(z1);
        Jk(2,4) = -tanh(z2);

        % d r / d b1, b2
        Jk(1,5) = -qd1;
        Jk(2,6) = -qd2;

        % d r / d v_eps
        sech2_z1 = 1./cosh(z1).^2;
        sech2_z2 = 1./cosh(z2).^2;
        Jk(1,7)  =  fc1 * (qd1 / v_eps^2) * sech2_z1;
        Jk(2,7)  =  fc2 * (qd2 / v_eps^2) * sech2_z2;

        J(idx,:) = Jk;
    end
end


function theta_hat = estimate_theta_ls(data,v_eps)
    %ESTIMATE_THETA_LS  Estimate parameter vector theta_hat via linear least squares

    N = size(data.q_filt,2);
    Y_stack   = zeros(2*N, 6);
    tau_stack = zeros(2*N, 1);

    for k = 1:N
        qdd1 = data.qdd_filt(1,k);
        qdd2 = data.qdd_filt(2,k);
        qd1  = data.qd_filt(1,k);
        qd2  = data.qd_filt(2,k);

        rows = (2*k-1):(2*k);

        % regressor
        Y_stack(rows,:) = [ qdd1,          qdd1 + qdd2,  tanh(qd1 / v_eps), 0,                 qd1, 0;
                            0,             qdd1 + qdd2,  0,                 tanh(qd2 / v_eps), 0,   qd2 ];

        % torque stacking
        tau_stack(rows) = data.tau_meas(:,k);
    end

    % Solve LS
    theta_hat = Y_stack \ tau_stack;
    % (equivalent to (Y'Y)\(Y'tau)
end

%% calculate MSE's
mse = computeMSEJointStates(x_true, x_hat)

function mse = computeMSEJointStates(x_true, x_hat)
    % Ensure x_hat has the same orientation as x_true
    if size(x_hat,1) == 4 && size(x_hat,2) == size(x_true,1)
        x_hat = x_hat.';  % transpose to N x 4
    elseif size(x_hat,1) ~= size(x_true,1) || size(x_hat,2) ~= 4
        error('x_hat must have size N x 4 or 4 x N, where N = number of samples');
    end

    % True states
    q_true  = x_true(:,1:2);   % [theta1 theta2]
    qd_true = x_true(:,3:4);   % [dtheta1 dtheta2]

    % Estimated states
    q_hat  = x_hat(:,1:2);
    qd_hat = x_hat(:,3:4);

    % Errors
    e_q  = q_true  - q_hat;
    e_qd = qd_true - qd_hat;

    % Per-state MSE
    mse.theta1  = mean(e_q(:,1).^2);
    mse.theta2  = mean(e_q(:,2).^2);
    mse.dtheta1 = mean(e_qd(:,1).^2);
    mse.dtheta2 = mean(e_qd(:,2).^2);

    % Combined MSEs
    mse.theta  = mean(e_q(:).^2);                 % all angle samples
    mse.dtheta = mean(e_qd(:).^2);                % all velocity samples
    mse.total  = mean([e_q(:); e_qd(:)].^2);     % all 4 states together
end


   