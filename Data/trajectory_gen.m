clear; clc;

%% System parameters (unchanged)
m1 = 1.6537;  l1 = 0.343;  r1 = 0.29;  I1 = 0.039;
m2 = 0.9982;  l2 = 0.267;  r2 = 0.175; I2 = 0.0081;

% Shorthand constants
a1 = m1 * r1^2 + m2 * l1^2 + I1;
a2 = m2 * r2^2 + I2;
b  = m2 * l1 * r2;

%% Simulation settings
dt    = 1e-3;
tspan = [0, 5];                     % longer sim
t = (tspan(1):dt:tspan(2)).';       % Nx1
rng(32);                            % reproducible noise

%% Excitation & simulation sizing
num_simulations = 20;            % increased
N = numel(t);

%% Noise settings (small realistic values)
% sigma_tau1 = 0.01;   % [Nm] process
% sigma_tau2 = 0.01;
% sigma_uc1  = 0.01;   % command/actuator
% sigma_uc2  = 0.01;
% sigma_th1  = 1e-3;   % measurement noise
% sigma_th2  = 1e-3;
% sigma_dth1 = 1e-3;
% sigma_dth2 = 1e-3;

sigma_tau1 = 0;   % [Nm] process
sigma_tau2 = 0;
sigma_uc1  = 0;   % command/actuator
sigma_uc2  = 0;
sigma_th1  = 0;   % measurement noise
sigma_th2  = 0;
sigma_dth1 = 0;
sigma_dth2 = 0;

%% Friction parameters (as before)
b1  = 0.02;   % viscous [Nms/rad] joint 1
b2  = 0.025;  % viscous [Nms/rad] joint 2
fc1 = 0;      % Coulomb [Nm] joint 1
fc2 = 0;      % Coulomb [Nm] joint 2
v_eps = 1e-3; % smoothing speed [rad/s] for tanh

%% initial conditions 
low  = [-pi, -pi, 0, 0];
high = [ pi,  pi, 0, 0];
initial_conditions = low + (high - low).*rand(num_simulations, 4);

%% Storage 
runs = repmat(struct( ...
    'time', t, ...
    'x_true', [], ...             % Nx4
    'y_meas', [], ...             % Nx4
    'u_cmd', [], ...              % Nx2   (nominal)
    'u_cmd_noisy', [], ...        % Nx2   (after command noise)
    'u_applied', [], ...          % Nx2   (command-noisy + process disturbance)
    'p', [], ...                  % Nx2   momentum
    'KE', [], ...                 % Nx1
    'ddq', [], ...                % Nx2
    'initial_condition', [], ...
    'torque_params', struct('A1',[],'A2',[],'f1',[],'f2',[],'phi1',[],'phi2',[],'type',[],'multi_harms',[],'multi_phases',[]), ...
    'noise_sigmas', struct( ...
        'sigma_tau1',[],'sigma_tau2',[], ...
        'sigma_uc1',[],'sigma_uc2',[], ...
        'sigma_th1',[],'sigma_th2',[],'sigma_dth1',[],'sigma_dth2',[]), ...
    'friction_params', struct('b1',[],'b2',[],'fc1',[],'fc2',[],'v_eps',[]) ...
    ), num_simulations, 1);

traj_id = 0;
rng(42);

for group = 1:2
    for k = 1:10
        x = zeros(N,4);                 % truth
        y = zeros(N,4);                 % measurements
        u_cmd = zeros(N,2);
        traj_id = traj_id + 1;

        switch group
            % A: single joint q2 excitation
            % case 1
            %     traj.type = 'single_q2';
            %     traj.A  = 0.3 + 0.15*k;        % 0.45..1.05 rad
            %     traj.f  = 0.15 + 0.05*k;         % 0.4..0.8 Hz

            % B: multisine
            case 1
                traj.type = 'multisine';
                traj.f  = 0.05 + 0.025*k;
                traj.A1 = 0.1*[1 0.7 0.5];
                traj.A2 = 0.25*[1 0.8 0.6];
                traj.phi1 = 2*pi*rand(1,3);
                traj.phi2 = 2*pi*rand(1,3);

            % C: Lissajous coverage 
            case 2
                traj.type = 'lissajous';
                traj.A1 = 0.25;
                traj.A2 = 0.15;
                traj.f1 = 0.1 + 0.03*k;
                traj.f2 = 0.2 + 0.05*k;
                traj.phi = 2*pi*rand();

        end

        % Generate trajectory 
        [q, dq, ddq] = generate_joint_trajectory(t, traj, initial_conditions(k+(10*(group-1)),1:2));


        % Inverse dynamics
        tau = zeros(N,2);
        for i = 1:N
            tau(i,:) = inverse_dynamics( ...
                q(i,:).', dq(i,:).', ddq(i,:).', ...
                a1,a2,b, b1,b2, fc1,fc2, v_eps).';
        end

        % Command / actuator noise (per-sample)
        eta_cmd = [sigma_uc1 sigma_uc2] .* randn(N,2);
        u_cmd_noisy = tau + eta_cmd;
        
        % Process torque disturbance (per-sample)
        w_tau = [sigma_tau1 sigma_tau2] .* randn(N,2);
        
        % Applied torque
        u_applied = u_cmd_noisy + w_tau;

        % Energetics / momentum from truth
        KE = kinetic_energy(q, dq, a1, a2, b);   % Nx1
        p  = momentum(q, dq, a1, a2, b);         % Nx2

        % store
        runs(traj_id).x_true = [q dq];
        runs(traj_id).y_meas = y;
        runs(traj_id).u_cmd = tau;
        runs(traj_id).u_cmd_noisy = u_cmd_noisy;
        runs(traj_id).u_applied = u_applied;
        runs(traj_id).p = p;
        runs(traj_id).KE = KE;
        runs(traj_id).ddq = ddq;
        runs(traj_id).initial_condition = initial_conditions(traj_id,:);
        % runs(traj_id).torque_params = struct('A1',traj.A1,'A2',traj.A2,'f1',traj.f1,'f2',traj.f2, ...
        %                                'phi1',traj.phi1,'phi2',traj.phi2,'type',traj.type, ...
        %                                'multi_harms',traj.multi_harms,'multi_phases',traj.multi_phases);
        runs(traj_id).noise_sigmas = struct('sigma_tau1',sigma_tau1,'sigma_tau2',sigma_tau2, ...
                                      'sigma_uc1',sigma_uc1,'sigma_uc2',sigma_uc2, ...
                                      'sigma_th1',sigma_th1,'sigma_th2',sigma_th2, ...
                                      'sigma_dth1',sigma_dth1,'sigma_dth2',sigma_dth2);
        runs(traj_id).friction_params = struct('b1',b1,'b2',b2,'fc1',fc1,'fc2',fc2,'v_eps',v_eps);
    end
end
%%
%% Sign-flip augmentation (dataset doubling)

% runs_orig = runs;
% runs_flip = runs;   % preallocate same size
% 
% for k = 1:numel(runs)
%     % States (q, dq)
%     runs_flip(k).x_true = -runs_orig(k).x_true;
% 
%     % Measurements (mirror state)
%     runs_flip(k).y_meas = -runs_orig(k).y_meas;
% 
%     % Torques
%     runs_flip(k).u_cmd       = -runs_orig(k).u_cmd;
%     runs_flip(k).u_cmd_noisy = -runs_orig(k).u_cmd_noisy;
%     runs_flip(k).u_applied   = -runs_orig(k).u_applied;
% 
%     % Accelerations
%     runs_flip(k).ddq = -runs_orig(k).ddq;
% 
%     % Momentum
%     runs_flip(k).p = -runs_orig(k).p;
% 
%     % Energy (DO NOT FLIP)
%     runs_flip(k).KE = runs_orig(k).KE;
% 
%     % Initial condition
%     runs_flip(k).initial_condition = -runs_orig(k).initial_condition;
% 
%     % Metadata stays identical
% end
% 
% % Concatenate original + flipped
% runs = [runs_orig; runs_flip];
% 
% disp(['Dataset doubled to ', num2str(numel(runs)), ' runs']);

%% Save dataset 
dataset.time = t;
dataset.runs = runs;
save('planar_2dof_dataset_no_noise_linear_friction.mat','dataset','-v7');
disp('Saved: planar_2dof_dataset_no_noise_linear_friction.mat');

% Quick checks (as before)
r = runs(15); tt = dataset.time;
figure('Color','w','Name','Run 1 torques');
subplot(2,1,1);
plot(tt, r.u_cmd(:,1), '-', tt, r.u_cmd_noisy(:,1), '--', tt, r.u_applied(:,1), ':');
grid on; ylabel('Nm'); title('Joint 1 torque');
legend('u\_cmd','u\_cmd\_noisy','u\_applied','Location','best');

subplot(2,1,2);
plot(tt, r.u_cmd(:,2), '-', tt, r.u_cmd_noisy(:,2), '--', tt, r.u_applied(:,2), ':');
grid on; ylabel('Nm'); xlabel('Time [s]'); title('Joint 2 torque');
legend('u\_cmd','u\_cmd\_noisy','u\_applied','Location','best');



figure('Color','w','Name','Run 1: Truth vs Measurement (angles)');
plot(tt, r.x_true(:,1), '-', tt, r.y_meas(:,1), '--'); hold on;
plot(tt, r.x_true(:,2), '-', tt, r.y_meas(:,2), '--'); hold off;
grid on; ylabel('rad'); xlabel('Time [s]');
legend('\theta_1 true','\theta_1 meas','\theta_2 true','\theta_2 meas'); title('Angles');

figure('Color','w','Name','Run 1: Truth vs Measurement (momentum)');
plot(tt, r.p(:,1), '-', tt, r.y_meas(:,1), '--'); hold on;
plot(tt, r.p(:,2), '-', tt, r.y_meas(:,2), '--'); hold off;
grid on; ylabel('rad'); xlabel('Time [s]');
legend('\theta_1 true','\theta_1 meas','\theta_2 true','\theta_2 meas'); title('Momenta');

% functions 
function [q, dq, ddq] = generate_joint_trajectory(t, traj, q0)
    N = numel(t);
    
    switch traj.type
        case 'multisine'
            q_sin = zeros(N,2);
            dq_sin = zeros(N,2);
            ddq_sin = zeros(N,2);
    
            for k = 1:3
                w1 = 2*pi*k*traj.f;  % joint 1 frequency
                w2 = 2*pi*k*traj.f;  % joint 2 frequency (different)
            
                phi1_k = 2*pi*rand(); % random phase for joint 1
                phi2_k = 2*pi*rand(); % random phase for joint 2
            
                q_sin(:,1) = q_sin(:,1) + traj.A1(k)*sin(w1*t + phi1_k);
                dq_sin(:,1)= dq_sin(:,1) + traj.A1(k)*w1*cos(w1*t + phi1_k);
                ddq_sin(:,1)= ddq_sin(:,1) - traj.A1(k)*w1^2*sin(w1*t + phi1_k);
            
                q_sin(:,2) = q_sin(:,2) + traj.A2(k)*sin(w2*t + phi2_k);
                dq_sin(:,2)= dq_sin(:,2) + traj.A2(k)*w2*cos(w2*t + phi2_k);
                ddq_sin(:,2)= ddq_sin(:,2) - traj.A2(k)*w2^2*sin(w2*t + phi2_k);
            end

    
            % Offset to enforce q(0) = q0
            q = q0(1:2) + (q_sin - q_sin(1,:));
            dq = dq_sin;
            ddq = ddq_sin;
    
        case 'lissajous'
            phi = pi/2;
            q_sin(:,1) = traj.A1*sin(2*pi*traj.f1*t + phi);
            dq_sin(:,1) = 2*pi*traj.f1*traj.A1*cos(2*pi*traj.f1*t + phi);
            ddq_sin(:,1)= -(2*pi*traj.f1)^2*traj.A1*sin(2*pi*traj.f1*t + phi);
    
            q_sin(:,2) = traj.A2*sin(2*pi*traj.f2*t + phi);
            dq_sin(:,2) = 2*pi*traj.f2*traj.A2*cos(2*pi*traj.f2*t + phi);
            ddq_sin(:,2)= -(2*pi*traj.f2)^2*traj.A2*sin(2*pi*traj.f2*t + phi);
    
            % Offset
            q = q0 + (q_sin - q_sin(1,:));
            dq = dq_sin;
            ddq = ddq_sin;
    
    end
end

function tau = inverse_dynamics(q, dq, ddq, a1,a2,b, b1,b2, fc1,fc2, v_eps)

    theta2  = q(2);
    dtheta1 = dq(1);
    dtheta2 = dq(2);
    
    M = M_mat(theta2, a1, a2, b);
    C = C_mat(theta2, dtheta1, dtheta2, b);
    
    F_visc = [b1*dtheta1; b2*dtheta2];
    F_coul = [fc1*tanh(dtheta1/v_eps); fc2*tanh(dtheta2/v_eps)];
    tau_fric = F_visc + F_coul;
    
    tau = M*ddq + C*[dtheta1; dtheta2] + tau_fric;
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


function T = kinetic_energy(q, dq, a1, a2, b)
% q  : Nx2
% dq : Nx2
% T  : Nx1

    N = size(q,1);
    T = zeros(N,1);

    for k = 1:N
        theta2 = q(k,2);
        M = M_mat(theta2, a1, a2, b);
        v = dq(k,:).';
        T(k) = 0.5 * (v.' * M * v);
    end
end

function p = momentum(q, dq, a1, a2, b)
% q  : Nx2
% dq : Nx2
% p  : Nx2

    N = size(q,1);
    p = zeros(N,2);

    for k = 1:N
        theta2 = q(k,2);
        M = M_mat(theta2, a1, a2, b);
        p(k,:) = (M * dq(k,:).').';
    end
end

