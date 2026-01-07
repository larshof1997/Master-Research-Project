clear; clc; close all;

%% ================== SYSTEM PARAMETERS ==================
m1 = 1.6537;  l1 = 0.343;  r1 = 0.29;  I1 = 0.039;
m2 = 0.9982;  l2 = 0.267;  r2 = 0.175; I2 = 0.0081;

a1 = m1 * r1^2 + m2 * l1^2 + I1;
a2 = m2 * r2^2 + I2;
b  = m2 * l1 * r2;

%% ================== FRICTION ==================
b1  = 0.02;
b2  = 0.025;
fc1 = 0;
fc2 = 0;
v_eps = 1e-3;

%% ================== TIME ==================
dt = 1e-3;
T  = 5.0;                         % duration per trajectory (real-robot friendly)
t  = (0:dt:T).';
N  = numel(t);

%% ================== DATASET SIZE ==================
num_traj = 20;

%% ================== STORAGE ==================
runs = repmat(struct( ...
    'time', t, ...
    'q', [], ...
    'dq', [], ...
    'ddq', [], ...
    'x_true', [], ...
    'u_tau', [], ...
    'traj_type', '', ...
    'traj_params', [], ...
    'friction_params', struct('b1',b1,'b2',b2,'fc1',fc1,'fc2',fc2,'v_eps',v_eps) ...
), num_traj, 1);

%% ================== TRAJECTORY DESIGN ==================
traj_id = 0;
rng(1);

for group = 1:4
    for k = 1:5
        traj_id = traj_id + 1;

        switch group
            % A: single joint q2 excitation
            case 1
                traj.type = 'single_q2';
                traj.A  = 0.3 + 0.15*k;        % 0.45..1.05 rad
                traj.f  = 0.3 + 0.1*k;         % 0.4..0.8 Hz

            % B: multisine
            case 2
                traj.type = 'multisine';
                traj.f = 0.3 + 0.1*k;
                traj.A1 = 0.3*[1 0.7 0.5];
                traj.A2 = 0.4*[1 0.8 0.6];
                traj.phi1 = 2*pi*rand(1,3);
                traj.phi2 = 2*pi*rand(1,3);

            % C: Lissajous coverage 
            case 3
                traj.type = 'lissajous';
                traj.A1 = 0.7;
                traj.A2 = 0.6;
                traj.f1 = 0.3 + 0.05*k;
                traj.f2 = 0.5 + 0.07*k;
                traj.phi = 2*pi*rand();

            % D: slow-fast separation
            case 4
                traj.type = 'slowfast';
                traj.A1 = 0.7;
                traj.A2 = 0.5;
        end

        % Generate trajectory 
        [q, dq, ddq] = generate_joint_trajectory(t, traj, dt);

        % Inverse dynamics
        tau = zeros(N,2);
        for i = 1:N
            tau(i,:) = inverse_dynamics( ...
                q(i,:).', dq(i,:).', ddq(i,:).', ...
                a1,a2,b, b1,b2, fc1,fc2, v_eps).';
        end

        %% ===== Store =====
        runs(traj_id).q = q;
        runs(traj_id).dq = dq;
        runs(traj_id).ddq = ddq;
        runs(traj_id).x_true = [q dq];
        runs(traj_id).u_tau = tau;
        runs(traj_id).traj_type = traj.type;
        runs(traj_id).traj_params = traj;
    end
end

%% ================== SAVE ==================
dataset.time = t;
dataset.runs = runs;

save('planar_2dof_20_joint_trajectories_inverse_dynamics.mat','dataset','-v7');
disp('Saved: planar_2dof_20_joint_trajectories_inverse_dynamics.mat');

%% ================== QUICK VISUAL CHECK ==================
r = runs(1);
figure('Color','w');
subplot(2,1,1); plot(t, r.q); grid on; title('Joint positions');
legend('q1','q2');
subplot(2,1,2); plot(t, r.u_tau); grid on; title('Inverse dynamics torques');
legend('\tau_1','\tau_2');

%% ================== FUNCTIONS ==================

function [q, dq, ddq] = generate_joint_trajectory(t, traj, dt)

switch traj.type
    case 'single_q2'
        q1 = zeros(size(t));
        q2 = traj.A * sin(2*pi*traj.f*t);

    case 'multisine'
        q1 = zeros(size(t));
        q2 = zeros(size(t));
        for k = 1:3
            q1 = q1 + traj.A1(k)*sin(2*pi*k*traj.f*t + traj.phi1(k));
            q2 = q2 + traj.A2(k)*sin(2*pi*k*traj.f*t + traj.phi2(k));
        end

    case 'lissajous'
        q1 = traj.A1 * sin(2*pi*traj.f1*t);
        q2 = traj.A2 * sin(2*pi*traj.f2*t + traj.phi);

    case 'slowfast'
        q1 = traj.A1 * sin(2*pi*0.3*t);
        q2 = traj.A2 * sin(2*pi*2.0*t);
end

q  = [q1 q2];
dq = gradient(q, dt);
ddq = gradient(dq, dt);
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
