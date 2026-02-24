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
sigma_tau1 = 0.002;   % [Nm] process
sigma_tau2 = 0.0015;
sigma_uc1  = 0.01;   % command/actuator
sigma_uc2  = 0.005;
sigma_th1  = 0.05;   % measurement noise
sigma_th2  = 0.025;
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
    'y_filt', [], ...             % Nx4
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
        traj_id = traj_id + 1;

        switch group
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

        % Generate DESIRED trajectory (kinematic reference)
        [q_des, dq_des, ddq_des] = generate_joint_trajectory(t, traj, initial_conditions(traj_id,1:2));

        % Compute required torques via inverse dynamics
        tau_cmd = zeros(N,2);
        for i = 1:N
            tau_cmd(i,:) = inverse_dynamics( ...
                q_des(i,:).', dq_des(i,:).', ddq_des(i,:).', ...
                a1,a2,b, b1,b2, fc1,fc2, v_eps).';
        end

        % NOW SIMULATE FORWARD with these torques + noise
        x_true = zeros(N,4);
        x_true(1,:) = initial_conditions(traj_id,:);  % Use full 4D initial condition
        
        u_cmd_noisy = zeros(N,2);
        u_applied = zeros(N,2);
        ddq_true = zeros(N,2);
        
        for i = 1:N-1
            ti = t(i);
            h = dt;
            
            % Command/actuator noise
            eta_cmd = [sigma_uc1; sigma_uc2] .* randn(2,1);
            tau_cmd_noisy = tau_cmd(i,:).' + eta_cmd;
            u_cmd_noisy(i,:) = tau_cmd_noisy.';
            
            % Process torque disturbance
            w_tau = [sigma_tau1; sigma_tau2] .* randn(2,1);
            
            % Applied torque to the plant
            tau_applied = tau_cmd_noisy + w_tau;
            u_applied(i,:) = tau_applied.';
            
            % RK4 step with friction and applied torque
            k1 = f_dyn(ti,       x_true(i,:).',           tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps);
            k2 = f_dyn(ti+0.5*h, x_true(i,:).' + 0.5*h*k1, tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps);
            k3 = f_dyn(ti+0.5*h, x_true(i,:).' + 0.5*h*k2, tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps);
            k4 = f_dyn(ti+h,     x_true(i,:).' + h*k3,     tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps);
            
            x_true(i+1,:) = x_true(i,:).' + (h/6)*(k1 + 2*k2 + 2*k3 + k4);
            
            % Get acceleration from k1
            ddq_true(i,:) = k1(3:4).';
        end
        
        % Last sample torques
        u_cmd_noisy(N,:) = u_cmd_noisy(N-1,:);
        u_applied(N,:) = u_applied(N-1,:);
        ddq_true(N,:) = ddq_true(N-1,:);
        
        % Measurement noise
        v = [sigma_th1, sigma_th2, sigma_dth1, sigma_dth2] .* randn(N,4);
        y_meas = x_true + v;
        
        % Energetics / momentum from TRUE simulated states
        KE = zeros(N,1);
        p = zeros(N,2);
        for i = 1:N
            KE(i) = kinetic_energy_single(x_true(i,:).', a1, a2, b);
            p(i,:) = momentum_single(x_true(i,:).', a1, a2, b).';
        end

        K = 2;
        F = 301;
        q_filt1 = sgolayfilt(y_meas(:,1), K, F);
        q_filt2 = sgolayfilt(y_meas(:,2), K, F);
        [~, g] = sgolay(K, F);  
        qd_filt1 = conv(q_filt1, factorial(1)/(-dt) * g(:,2), 'same');
        qd_filt2 = conv(q_filt2, factorial(1)/(-dt) * g(:,2), 'same');

        y_filt = [q_filt1 q_filt2 qd_filt1 qd_filt2];

        % Store results
        runs(traj_id).x_true = x_true;
        runs(traj_id).y_meas = y_meas;
        runs(traj_id).y_filt = y_filt;
        runs(traj_id).u_cmd = tau_cmd;
        runs(traj_id).u_cmd_noisy = u_cmd_noisy;
        runs(traj_id).u_applied = u_applied;
        runs(traj_id).p = p;
        runs(traj_id).KE = KE;
        runs(traj_id).ddq = ddq_true;
        runs(traj_id).initial_condition = initial_conditions(traj_id,:);
        runs(traj_id).torque_params = traj;
        runs(traj_id).noise_sigmas = struct('sigma_tau1',sigma_tau1,'sigma_tau2',sigma_tau2, ...
                                      'sigma_uc1',sigma_uc1,'sigma_uc2',sigma_uc2, ...
                                      'sigma_th1',sigma_th1,'sigma_th2',sigma_th2, ...
                                      'sigma_dth1',sigma_dth1,'sigma_dth2',sigma_dth2);
        runs(traj_id).friction_params = struct('b1',b1,'b2',b2,'fc1',fc1,'fc2',fc2,'v_eps',v_eps);
        
        fprintf('Completed trajectory %d/%d\n', traj_id, num_simulations);
    end
end

%% Save dataset 
dataset.time = t;
dataset.runs = runs;
save('planar_2dof_dataset_gaussian_noise_linear_friction.mat','dataset','-v7');
disp('Saved: planar_2dof_dataset_gaussian_noise_linear_friction.mat');

%% Quick checks
r = runs(15); tt = dataset.time;
figure('Color','w','Name','Run 15 torques');
subplot(2,1,1);
plot(tt, r.u_cmd(:,1), '-', tt, r.u_cmd_noisy(:,1), '--', tt, r.u_applied(:,1), ':');
grid on; ylabel('Nm'); title('Joint 1 torque');
legend('u\_cmd','u\_cmd\_noisy','u\_applied','Location','best');

subplot(2,1,2);
plot(tt, r.u_cmd(:,2), '-', tt, r.u_cmd_noisy(:,2), '--', tt, r.u_applied(:,2), ':');
grid on; ylabel('Nm'); xlabel('Time [s]'); title('Joint 2 torque');
legend('u\_cmd','u\_cmd\_noisy','u\_applied','Location','best');

figure('Color','w','Name','Run 15: Truth vs Measurement (angles)');
subplot(2,1,1);
hold on;
plot(tt, r.x_true(:,1), '-'); 
plot(tt,r.y_filt(:,1),'.')
hold off;
grid on; ylabel('rad'); title('\theta_1');

subplot(2,1,2);
hold on;
plot(tt, r.x_true(:,2), '-'); 
plot(tt,r.y_filt(:,2),'.')
hold off;
grid on; ylabel('rad'); xlabel('Time [s]'); title('\theta_2');

figure('Color','w','Name','Run 15: Velocities');
subplot(2,1,1);
hold on;
plot(tt, r.x_true(:,3), '-'); 
plot(tt,r.y_filt(:,3),'.')
hold off;
grid on; ylabel('rad/s'); title('$\dot{\theta}_1$','Interpreter','latex');

subplot(2,1,2);
hold on;
plot(tt, r.x_true(:,4), '-'); 
plot(tt,r.y_filt(:,4),'.')
hold off;
grid on; ylabel('rad/s'); xlabel('Time [s]'); title('$\dot{\theta}_2$','Interpreter','latex');

%% Functions

function dx = f_dyn(~, x, tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps)
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
            
                phi1_k = traj.phi1(k);
                phi2_k = traj.phi2(k);
            
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
            phi = traj.phi;
            q_sin = zeros(N,2);
            dq_sin = zeros(N,2);
            ddq_sin = zeros(N,2);
            
            q_sin(:,1) = traj.A1*sin(2*pi*traj.f1*t + phi);
            dq_sin(:,1) = 2*pi*traj.f1*traj.A1*cos(2*pi*traj.f1*t + phi);
            ddq_sin(:,1)= -(2*pi*traj.f1)^2*traj.A1*sin(2*pi*traj.f1*t + phi);
    
            q_sin(:,2) = traj.A2*sin(2*pi*traj.f2*t);
            dq_sin(:,2) = 2*pi*traj.f2*traj.A2*cos(2*pi*traj.f2*t);
            ddq_sin(:,2)= -(2*pi*traj.f2)^2*traj.A2*sin(2*pi*traj.f2*t);
    
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

function T = kinetic_energy_single(x, a1, a2, b)
    theta2 = x(2);
    dtheta1 = x(3);
    dtheta2 = x(4);
    M = M_mat(theta2, a1, a2, b);
    v = [dtheta1; dtheta2];
    T = 0.5 * (v.' * M * v);
end

function p = momentum_single(x, a1, a2, b)
    theta2 = x(2);
    dtheta1 = x(3);
    dtheta2 = x(4);
    M = M_mat(theta2, a1, a2, b);
    p = M * [dtheta1; dtheta2];
end