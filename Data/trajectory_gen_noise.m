% 2-DOF planar manipulator (no gravity) with process, command, and measurement noise
% M(q)*ddq + C(q,dq)*dq = tau_applied
% tau_applied = (tau_command + eta_cmd) + w_tau
% y = x_true + v
%
% Saves per-run ground truth, inputs (u_cmd, u_cmd_noisy, u_applied), and measurements.

clear; clc;

%% System parameters
m1 = 1.6537;  l1 = 0.343;  r1 = 0.29;  I1 = 0.039;
m2 = 0.9982;  l2 = 0.267;  r2 = 0.175; I2 = 0.0081;

% Shorthand constants
a1 = m1 * r1^2 + m2 * l1^2 + I1;
a2 = m2 * r2^2 + I2;
b  = m2 * l1 * r2;

%% Simulation settings
dt    = 1e-3;
tspan = [0, 5];
tgrid = (tspan(1):dt:tspan(2)).';   % Nx1
rng(42);                            % reproducible noise

% Use fixed-step RK4
rk_substeps = 1; % kept for clarity; one substep = vanilla RK4

% Torque grid
A1_vals = [0.5, 1.0];
A2_vals = [0.5, 1.0];
f1_vals = [0.5, 1.5];
f2_vals = [0.5, 2.0];

num_simulations = 12;

low  = [-pi, -pi, -1.0, -1.0];
high = [ pi,  pi,  1.0,  1.0];
initial_conditions = low + (high - low).*rand(num_simulations, 4);

grid = [];
for A1 = A1_vals
    for A2 = A2_vals
        for f1 = f1_vals
            for f2 = f2_vals
                grid = [grid; A1, A2, f1, f2]; %#ok<AGROW>
            end
        end
    end
end

pars_list = repmat(struct('A1',1,'A2',1,'f1',1,'f2',1,'phi1',0,'phi2',0), num_simulations, 1);
for i = 1:num_simulations
    g = grid(mod(i-1, size(grid,1)) + 1, :);
    pars_list(i).A1 = g(1);  pars_list(i).A2 = g(2);
    pars_list(i).f1 = g(3);  pars_list(i).f2 = g(4);
    pars_list(i).phi1 = 0;   pars_list(i).phi2 = 0;
end

%% Friction parameters 
b1  = 0.02;   % viscous [Nms/rad] joint 1
b2  = 0.025;  % viscous [Nms/rad] joint 2
fc1 = 0.15;   % Coulomb [Nm] joint 1
fc2 = 0.12;   % Coulomb [Nm] joint 2
v_eps = 1e-3; % smoothing speed [rad/s] for tanh

%% Noise settings

% Process noise (torque disturbance)
sigma_tau1 = 0.015;   % [Nm]
sigma_tau2 = 0.025;   % [Nm]

% Command/actuator noise (on commanded torques)
sigma_uc1  = 0.0;   % [Nm]
sigma_uc2  = 0.0;   % [Nm]

% Measurement noise on [theta1 theta2 dtheta1 dtheta2]
sigma_th1   = 0.02; % [rad]
sigma_th2   = 0.02; % [rad]
sigma_dth1  = 0.1;  % [rad/s]
sigma_dth2  = 0.1;  % [rad/s]

%% Storage 
runs = repmat(struct( ...
    'time', tgrid, ...
    'x_true', [], ...             % Nx4
    'y_meas', [], ...             % Nx4
    'u_cmd', [], ...              % Nx2   (nominal)
    'u_cmd_noisy', [], ...        % Nx2   (after command noise)
    'u_applied', [], ...          % Nx2   (command-noisy + process disturbance)
    'p', [], ...                  % Nx2   momentum
    'KE', [], ...                 % Nx1
    'ddq', [], ...                % Nx2  joint accelerations
    'initial_condition', [], ...
    'torque_params', struct('A1',[],'A2',[],'f1',[],'f2',[],'phi1',[],'phi2',[]), ...
    'noise_sigmas', struct( ...
        'sigma_tau1',[],'sigma_tau2',[], ...
        'sigma_uc1',[],'sigma_uc2',[], ...
        'sigma_th1',[],'sigma_th2',[],'sigma_dth1',[],'sigma_dth2',[]), ...
    'friction_params', struct('b1',[],'b2',[],'fc1',[],'fc2',[],'v_eps',[]) ...
    ), num_simulations, 1);

%% Main loop (RK4 + noises)
N = numel(tgrid);
for i = 1:num_simulations
    x = zeros(N,4);                 % truth
    y = zeros(N,4);                 % measurements
    u_cmd_noisy = zeros(N,2);
    u_applied = zeros(N,2);
    p = zeros(N,2);
    KE = zeros(N,1);
    ddq = zeros(N,2);

    x(1,:) = initial_conditions(i,:);
    pars   = pars_list(i);

    for k = 1:N-1
        t = tgrid(k);
        h = dt;

        % Nominal commanded torque
        tau_cmd = tau_of_t(t, pars);          % 2x1

        % Command/actuator noise
        eta_cmd = [sigma_uc1; sigma_uc2] .* randn(2,1);
        tau_cmd_noisy = tau_cmd + eta_cmd;        % 2x1
        u_cmd_noisy(k,:) = tau_cmd_noisy.';

        % Process torque disturbance
        w_tau = [sigma_tau1; sigma_tau2] .* randn(2,1);

        % Applied torque to the plant
        tau_applied = tau_cmd_noisy + w_tau;      % 2x1
        u_applied(k,:) = tau_applied.';

        % % RK4 step with applied torque
        % k1 = f_dyn(t,       x(k,:).',           tau_applied, a1,a2,b);
        % k2 = f_dyn(t+0.5*h, x(k,:).' + 0.5*h*k1, tau_applied, a1,a2,b);
        % k3 = f_dyn(t+0.5*h, x(k,:).' + 0.5*h*k2, tau_applied, a1,a2,b);
        % k4 = f_dyn(t+h,     x(k,:).' + h*k3,     tau_applied, a1,a2,b);
        % x(k+1,:) = x(k,:).' + (h/6)*(k1 + 2*k2 + 2*k3 + k4);

        % RK4 step with friction and applied torque inside dynamics
        k1 = f_dyn(t,       x(k,:).',           tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps);
        k2 = f_dyn(t+0.5*h, x(k,:).' + 0.5*h*k1, tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps);
        k3 = f_dyn(t+0.5*h, x(k,:).' + 0.5*h*k2, tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps);
        k4 = f_dyn(t+h,     x(k,:).' + h*k3,     tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps);
        x(k+1,:) = x(k,:).' + (h/6)*(k1 + 2*k2 + 2*k3 + k4);

        %Get second derivative
        ddq(k,:) = k1(3:4).';

        % Energetics / momentum from truth
        KE(k)  = kinetic_energy(x(k,:).', a1, a2, b);
        p(k,:) = momentum(x(k,:).', a1, a2, b).';
        ddq(N,:) = ddq(N-1,:);
    end
    KE(N)  = kinetic_energy(x(N,:).', a1, a2, b);
    p(N,:) = momentum(x(N,:).', a1, a2, b).';

    % Measurements
    v = [sigma_th1, sigma_th2, sigma_dth1, sigma_dth2] .* randn(N,4);
    y = x + v;

    % store
    runs(i).x_true = x;
    runs(i).y_meas = y;
    runs(i).u_cmd_noisy = u_cmd_noisy;
    runs(i).u_applied = u_applied;
    runs(i).p = p;
    runs(i).KE = KE;
    runs(i).ddq = ddq;
    runs(i).initial_condition = initial_conditions(i,:);
    runs(i).torque_params = pars;
    runs(i).noise_sigmas = struct('sigma_tau1',sigma_tau1,'sigma_tau2',sigma_tau2, ...
                                  'sigma_uc1',sigma_uc1,'sigma_uc2',sigma_uc2, ...
                                  'sigma_th1',sigma_th1,'sigma_th2',sigma_th2, ...
                                  'sigma_dth1',sigma_dth1,'sigma_dth2',sigma_dth2);
    runs(i).friction_params = struct('b1',b1,'b2',b2,'fc1',fc1,'fc2',fc2,'v_eps',v_eps);

end

%% Save dataset 
dataset.time = tgrid;
dataset.runs = runs;
save('planar_2dof_dataset_gaussian_noise.mat','dataset','-v7');
disp('Saved: planar_2dof_dataset.mat');

%% Quick checks
% Show Run 1 commanded vs noisy vs applied torques
r = runs(1); tt = dataset.time;
figure('Color','w','Name','Run 1 torques');
subplot(2,1,1);
plot(tt, r.u_cmd_noisy(:,1), '--', tt, r.u_applied(:,1), ':');
grid on; ylabel('Nm'); title('Joint 1 torque');
legend('u\_cmd\_noisy','u\_applied','Location','best');

subplot(2,1,2);
plot(tt, r.u_cmd_noisy(:,2), '--', tt, r.u_applied(:,2), ':');
grid on; ylabel('Nm'); xlabel('Time [s]'); title('Joint 2 torque');
legend('u\_cmd\_noisy','u\_applied','Location','best');

% Truth vs measurement (angles) for Run 1
figure('Color','w','Name','Run 1: Truth vs Measurement (angles)');
plot(tt, r.x_true(:,1), '-', tt, r.y_meas(:,1), '--'); hold on;
plot(tt, r.x_true(:,2), '-', tt, r.y_meas(:,2), '--'); hold off;
grid on; ylabel('rad'); xlabel('Time [s]');
legend('\theta_1 true','\theta_1 meas','\theta_2 true','\theta_2 meas'); title('Angles');

%%  functions
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

function tau = tau_of_t(t, pars)
    tau1 = pars.A1 * sin(2*pi*pars.f1*t + pars.phi1);
    tau2 = pars.A2 * sin(2*pi*pars.f2*t + pars.phi2);
    tau = [tau1; tau2];
end

function T = kinetic_energy(x, a1, a2, b)
    theta2  = x(2); 
    dtheta1 = x(3);
    dtheta2 = x(4);
    M = M_mat(theta2, a1, a2, b);
    v = [dtheta1; dtheta2];
    T = 0.5 * (v.' * M * v);
end

function p = momentum(x, a1, a2, b)
    theta2  = x(2);
    dtheta1 = x(3);
    dtheta2 = x(4);
    M = M_mat(theta2, a1, a2, b);
    p = M * [dtheta1; dtheta2];
end
