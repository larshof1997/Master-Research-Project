% enhanced_planar_2dof_dataset_with_rich_excitation.m
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
tspan = [0, 5];                  % longer sim
tgrid = (tspan(1):dt:tspan(2)).'; % Nx1
rng(42);                          % reproducible noise

% Use fixed-step RK4
rk_substeps = 1;

%% Excitation & simulation sizing
num_simulations = 20;            % increased
N = numel(tgrid);

% frequency pool for random selection (Hz)
freq_pool = [0.2, 0.5, 1, 2.5, 4.0, 10];

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

%% initial conditions (wider velocities)
low  = [-pi, -pi, 0, 0];
high = [ pi,  pi, 0, 0];
initial_conditions = low + (high - low).*rand(num_simulations, 4);

%% excitation types
excitation_types = {'sine','multisine','chirp','prbs'};

% prepare pars_list
pars_list = repmat(struct('type','sine','A1',0.5,'A2',0.5,'f1',0.5,'f2',1.0,...
    'phi1',0,'phi2',0,'duration',tspan(2),'prbs_period',0.2,...
    'multi_harms',[],'multi_phases',[]), ...
    num_simulations, 1);

rng(42);
%% --- realistic torque adjustments ---
for i = 1:num_simulations
    % choose type with bias toward smooth/broadband but low freq
    types_weights = [0.4, 0.25, 0.3, 0.05]; % more smooth
    cumw = cumsum(types_weights);
    r = rand()*cumw(end);
    pick = find(r <= cumw, 1);
    pars_list(i).type = excitation_types{pick};

    % realistic torque amplitudes (Nm)
    pars_list(i).A1 = 0.1 + 0.3*rand();    % 0.1..0.4 Nm
    pars_list(i).A2 = 0.1 + 0.3*rand();    

    % low-frequency excitations (Hz)
    pars_list(i).f1 = freq_pool(randi([1 4]));  % 0.2..1.2 Hz
    pars_list(i).f2 = freq_pool(randi([1 4]));

    pars_list(i).phi1 = 2*pi*rand();
    pars_list(i).phi2 = 2*pi*rand();
    pars_list(i).duration = tspan(2);

    % PRBS / band noise / multisine adjustments
    pars_list(i).prbs_period = 0.5 + 0.5*rand();   % 0.5..1s

    if strcmp(pars_list(i).type,'multisine')
        % smooth multi-harmonic low frequency
        H = 2 + randi(2); % 2..4 harmonics
        pars_list(i).multi_harms = 1:H;
        pars_list(i).multi_phases = 2*pi*rand(1,H);
        pars_list(i).A1 = pars_list(i).A1 * (0.6 + 0.3*rand());
        pars_list(i).A2 = pars_list(i).A2 * (0.6 + 0.3*rand());
        pars_list(i).f1 = pars_list(i).f1 / 2; % lower freq
        pars_list(i).f2 = pars_list(i).f2 / 2;
    end
end

%% Storage (same struct layout)
runs = repmat(struct( ...
    'time', tgrid, ...
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

%% Main loop (RK4) - store everything in same format
for i = 1:num_simulations
    x = zeros(N,4);                 % truth
    y = zeros(N,4);                 % measurements
    u_cmd = zeros(N,2);
    u_cmd_noisy = zeros(N,2);
    u_applied = zeros(N,2);
    p = zeros(N,2);
    KE = zeros(N,1);
    ddq = zeros(N,2);

    x(1,:) = initial_conditions(i,:);
    pars   = pars_list(i);

    % pre-generate any light per-run deterministic helpers if needed (none required here)

    for k = 1:N-1
        t = tgrid(k);
        h = dt;

        % Nominal commanded torque
        tau_cmd = tau_of_t(t, pars);          % 2x1
        u_cmd(k,:) = tau_cmd.';               % store nominal

        % Command/actuator noise
        eta_cmd = [sigma_uc1; sigma_uc2] .* randn(2,1);
        tau_cmd_noisy = tau_cmd + eta_cmd;        % 2x1
        u_cmd_noisy(k,:) = tau_cmd_noisy.';

        % Process torque disturbance
        w_tau = [sigma_tau1; sigma_tau2] .* randn(2,1);

        % Applied torque to the plant
        tau_applied = tau_cmd_noisy + w_tau;      % 2x1
        u_applied(k,:) = tau_applied.';

        % RK4 step with friction and applied torque inside dynamics
        k1 = f_dyn(t,       x(k,:).',           tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps);
        k2 = f_dyn(t+0.5*h, x(k,:).' + 0.5*h*k1, tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps);
        k3 = f_dyn(t+0.5*h, x(k,:).' + 0.5*h*k2, tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps);
        k4 = f_dyn(t+h,     x(k,:).' + h*k3,     tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps);
        x(k+1,:) = (x(k,:).' + (h/6)*(k1 + 2*k2 + 2*k3 + k4)).';

        %Get second derivative (from k1)
        ddq(k,:) = k1(3:4).';

        % Energetics / momentum from truth
        KE(k)  = kinetic_energy(x(k,:).', a1, a2, b);
        p(k,:) = momentum(x(k,:).', a1, a2, b).';
    end

    % Fill last-step signals (repeat last commanded/applied as reasonable)
    % compute nominal tau at final t
    tau_cmd_final = tau_of_t(tgrid(end), pars);
    u_cmd(N,:) = tau_cmd_final.';
    % last noisy/applied: assume last used noisy + last w_tau ~ zero-mean -> repeat previous
    u_cmd_noisy(N,:) = u_cmd_noisy(N-1,:);
    u_applied(N,:) = u_applied(N-1,:);
    ddq(N,:) = ddq(N-1,:);
    KE(N)  = kinetic_energy(x(N,:).', a1, a2, b);
    p(N,:) = momentum(x(N,:).', a1, a2, b).';

    % Measurements (with measurement noise)
    v = [sigma_th1, sigma_th2, sigma_dth1, sigma_dth2] .* randn(N,4);
    y = x + v;

    % store (exact same fields & names)
    runs(i).x_true = x;
    runs(i).y_meas = y;
    runs(i).u_cmd = u_cmd;
    runs(i).u_cmd_noisy = u_cmd_noisy;
    runs(i).u_applied = u_applied;
    runs(i).p = p;
    runs(i).KE = KE;
    runs(i).ddq = ddq;
    runs(i).initial_condition = initial_conditions(i,:);
    runs(i).torque_params = struct('A1',pars.A1,'A2',pars.A2,'f1',pars.f1,'f2',pars.f2, ...
                                   'phi1',pars.phi1,'phi2',pars.phi2,'type',pars.type, ...
                                   'multi_harms',pars.multi_harms,'multi_phases',pars.multi_phases);
    runs(i).noise_sigmas = struct('sigma_tau1',sigma_tau1,'sigma_tau2',sigma_tau2, ...
                                  'sigma_uc1',sigma_uc1,'sigma_uc2',sigma_uc2, ...
                                  'sigma_th1',sigma_th1,'sigma_th2',sigma_th2, ...
                                  'sigma_dth1',sigma_dth1,'sigma_dth2',sigma_dth2);
    runs(i).friction_params = struct('b1',b1,'b2',b2,'fc1',fc1,'fc2',fc2,'v_eps',v_eps);
end


%% Save dataset (same variable name & file)
dataset.time = tgrid;
dataset.runs = runs;
save('planar_2dof_dataset_no_noise_linear_friction.mat','dataset','-v7');
disp('Saved: planar_2dof_dataset_no_noise_linear_friction.mat');

%% Quick checks (as before)
r = runs(1); tt = dataset.time;
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

figure('Color','w','Name','Momenta');
plot(tt, r.p(:,1), '-'); hold on;
plot(tt, r.p(:,2), '-'); hold off;
grid on; ylabel('rad'); xlabel('Time [s]');
legend('p_1','p_1'); title('Angles');


%% functions (use your original ones — appended here for completeness)
function dx = f_dyn(~, x, tau_applied, a1,a2,b, b1,b2, fc1,fc2, v_eps)
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
    switch pars.type
        case 'sine'
            tau1 = pars.A1 * sin(2*pi*pars.f1*t + pars.phi1);
            tau2 = pars.A2 * sin(2*pi*pars.f2*t + pars.phi2);
        case 'multisine'
            tau1 = 0; tau2 = 0;
            if isempty(pars.multi_harms)
                pars.multi_harms = 1:3;
            end
            for jj = 1:numel(pars.multi_harms)
                hh = pars.multi_harms(jj);
                ph = pars.multi_phases(mod(jj-1,numel(pars.multi_phases))+1);
                tau1 = tau1 + (pars.A1/numel(pars.multi_harms)) * sin(2*pi*(pars.f1*hh)*t + ph);
                tau2 = tau2 + (pars.A2/numel(pars.multi_harms)) * sin(2*pi*(pars.f2*hh)*t + ph*1.3);
            end
        case 'chirp'
            f0 = 0.1; f1 = 5.0;
            T = max(1, pars.duration);
            instantaneous_phase = 2*pi*(f0*t + (f1-f0)/(2*T)*t^2);
            tau1 = pars.A1 * sin(instantaneous_phase + pars.phi1);
            tau2 = pars.A2 * sin(instantaneous_phase*1.07 + pars.phi2);
        case 'prbs'
            period = pars.prbs_period;
            % make a fast toggling pseudo-PRBS using sign(sin)
            val1 = sign(sin(2*pi*(1/period)*t + pars.phi1));
            val2 = sign(sin(2*pi*(1/period)*t + pars.phi2 + 0.13));
            tau1 = pars.A1 * (val1);
            tau2 = pars.A2 * (val2);
        % case 'bandnoise'
        %     % approximate band-limited noise with a sum of random-phase sines
        %     tau1 = 0; tau2 = 0;
        %     K = 6;
        %     for kk = 1:K
        %         f_kk = kk * (pars.bandnoise_cutoff/(2*K) + 0.05);
        %         tau1 = tau1 + (pars.A1/K) * sin(2*pi*f_kk*t + 2*pi*rand());
        %         tau2 = tau2 + (pars.A2/K) * sin(2*pi*(f_kk*1.02)*t + 2*pi*rand());
        %     end
        % case 'step'
        %     T = max(1, pars.duration);
        %     t1 = T*(0.15 + 0.4*rand());
        %     t2 = T*(0.45 + 0.4*rand());
        %     if t < t1
        %         tau1 = 0; tau2 = 0;
        %     elseif t < t2
        %         tau1 = pars.A1; tau2 = -pars.A2;
        %     else
        %         tau1 = -0.6*pars.A1; tau2 = 0.6*pars.A2;
        %     end
        % case 'randompulse'
        %     tau1 = 0; tau2 = 0;
        %     if mod(floor(t*10), 50) < 3
        %         tau1 = pars.A1 * (2*rand()-1);
        %     end
        %     if mod(floor((t+0.7)*10), 60) < 4
        %         tau2 = pars.A2 * (2*rand()-1);
        %     end
        otherwise
            tau1 = pars.A1 * sin(2*pi*pars.f1*t + pars.phi1);
            tau2 = pars.A2 * sin(2*pi*pars.f2*t + pars.phi2);
    end
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
