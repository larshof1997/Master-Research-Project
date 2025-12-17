%% EKF joint + parameter estimation for 2-DOF manipulator
clear; clc;

%% Load dataset 
S = load('planar_2dof_dataset_gaussian_noise.mat');
dataset = S.dataset;

run_idx = 1;                         % choose which run to use
r = dataset.runs(run_idx);

t   = r.time(:);                     % Nx1
dt  = t(2) - t(1);
N   = numel(t);

u   = r.u_applied;                   % Nx2, applied joint torques
y_meas = r.y_meas;                   % Nx4, noisy [th1 th2 dth1 dth2]
x_true = r.x_true;                   % Nx4, true states

%% True parameters (for comparison only)
I1_true = 0.039;
I2_true = 0.0081;
fp = r.friction_params;              % b1,b2,fc1,fc2,v_eps stored here
psi_true = [I1_true; I2_true; fp.fc1; fp.fc2; fp.b1; fp.b2; fp.v_eps];

%% EKF setup
% state: x = [theta1; theta2; dtheta1; dtheta2; psi(1:7)]
nx = 2 + 9;

% initial parameter guess (you can copy your lsqnonlin psi0)
psi0 = [0.05; 0.01; 0.1; 0.1; 0.03; 0.03; 5e-2];

% parameter bounds (for optional clamping)
lb = [0;0;0;0;0;0;0];
ub = [0.5;0.1;0.5;0.5;0.1;0.1;0.1];

% initial state guess: first measurement + psi0
x0 = [y_meas(1,1:2)'; y_meas(1,3:4)'; psi0];

% initial covariance
P0 = 1e-2*eye(nx);                   % fairly uncertain

% process noise covariance Q
% small for states, slightly larger for parameters (random walk)
Q = diag([1e-6*ones(2,1); 1e-8*ones(9,1)]);

% measurement noise covariance R (read from run struct)
ns = r.noise_sigmas;
R = diag([ns.sigma_th1^2, ns.sigma_th2^2]);

% measurement Jacobian: z = [theta1; theta2]
H = [eye(2), zeros(2,9)];   % 2x11

%% Run EKF
x_hat = zeros(nx,N);
P_hat = zeros(nx,nx,N);

x_hat(:,1) = x0;
P = P0;

for k = 1:N-1
    % prediction step
    uk = u(k,:).';                             % 2x1
    [x_pred,Fk] = f_discrete_state(x_hat(:,k), uk, dt);
    P_pred = Fk*P*Fk' + Q;

    % measurement update (use measurement at k+1)
    z  = y_meas(k+1,1:2).';                     % 4x1
    z_hat = H*x_pred;                          % 4x1

    S_k = H*P_pred*H' + R;                     % 4x4
    K   = P_pred*H'/S_k;                       % 11x4

    x_upd = x_pred + K*(z - z_hat);
    P     = (eye(nx) - K*H)*P_pred;

    % optional: clamp parameters to bounds
    psi = x_upd(5:end);
    psi = max(lb, min(ub, psi));
    x_upd(5:end) = psi;

    % store
    x_hat(:,k+1) = x_upd;
    P_hat(:,:,k+1) = P;
end

psi_hat_ekf = x_hat(5:end,end);

fprintf('True psi:     %s\n', mat2str(psi_true',4));
fprintf('EKF psi_hat:  %s\n', mat2str(psi_hat_ekf',4));

mse = computeMSEJointStates(x_true(:,1:4), x_hat(1:4,:))

%% Plots: joint states
figure('Color','w','Name','EKF joint angle estimates');
subplot(2,1,1); hold on; grid on;
plot(t, x_true(:,1),'k','LineWidth',1.5);
plot(t, x_hat(1,:),'r--','LineWidth',1.5);
xlabel('t [s]'); ylabel('\theta_1 [rad]');
legend('true','EKF'); title('Joint 1 angle');

subplot(2,1,2); hold on; grid on;
plot(t, x_true(:,2),'k','LineWidth',1.5);
plot(t, x_hat(2,:),'r--','LineWidth',1.5);
xlabel('t [s]'); ylabel('theta_2 [rad]');
legend('true','EKF'); title('Joint 2 angle');

figure('Color','w','Name','EKF joint velocity estimates');
subplot(2,1,1); hold on; grid on;
plot(t, x_true(:,3),'k','LineWidth',1.5);
plot(t, x_hat(3,:),'r--','LineWidth',1.5);
xlabel('t [s]'); ylabel('\theta_1 [rad/s]');
legend('true','EKF'); title('Joint 1 velocity');

subplot(2,1,2); hold on; grid on;
plot(t, x_true(:,4),'k','LineWidth',1.5);
plot(t, x_hat(4,:),'r--','LineWidth',1.5);
xlabel('t [s]'); ylabel('theta_2 [rad/s]');
legend('true','EKF'); title('Joint 2 velocity');

%% Plots: parameter estimates
psi_names = {'I_1','I_2','f_{c1}','f_{c2}','b_1','b_2','v_\epsilon'};

figure('Color','w','Name','EKF parameter estimates');
for i = 1:7
    subplot(4,2,i); hold on; grid on;
    plot(t, psi_true(i)*ones(N,1),'k','LineWidth',1.5);
    plot(t, x_hat(4+i,:),'r--','LineWidth',1.2);
    ylabel(psi_names{i});
    if i >= 6, xlabel('t [s]'); end
    legend('true','EKF');
end

%% Local functions: dynamics and Jacobian

function [x_next,Fk] = f_discrete_state(x,u,dt)
% One-step discrete-time state update and Jacobian
% x_next = x + dt*f(x,u)
    f = f_cont_state(x,u);
    x_next = x + dt*f;

    % numerical Jacobian of f wrt x
    A = numJacobian(@(xx) f_cont_state(xx,u), x);
    % A = EKF_jacobian(x,u);
    Fk = eye(numel(x)) + dt*A;
end

function dx = f_cont_state(x,u)
% Continuous-time dynamics for state [q; qd; psi]
    q   = x(1:2);
    qd  = x(3:4);
    psi = x(5:end);   % [I1 I2 fc1 fc2 b1 b2 v_eps]

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

    ddq = M \ (u - C*qd - tau_f);

    dx = zeros(size(x));
    dx(1:2) = qd;
    dx(3:4) = ddq;
    % parameters random walk: d psi / dt = 0 (modelled by process noise in Q)
end

function A = numJacobian(f,x)
% Numerical Jacobian of vector function f at x
    n  = numel(x);
    f0 = f(x);
    m  = numel(f0);
    A  = zeros(m,n);

    epsRel = 1e-6;
    epsAbs = 1e-8;

    for j = 1:n
        h = epsRel*max(1,abs(x(j))) + epsAbs;
        xj = x;
        xj(j) = xj(j) + h;
        fj = f(xj);
        A(:,j) = (fj - f0)/h;
    end
end

function F = EKF_jacobian(x,u)
% Analytic Jacobian F = df/dx for the 2-DOF manipulator EKF
%
% State:
%   x = [q1; q2; dq1; dq2; I1; I2; fc1; fc2; b1; b2; v_eps]
%
% Input:
%   u : applied torques (2x1)
%
% Output:
%   F : 11x11 Jacobian matrix

%% --- Unpack state ---
q1   = x(1);
q2   = x(2);
dq1  = x(3);
dq2  = x(4);

I1   = x(5);
I2   = x(6);
fc1  = x(7);
fc2  = x(8);
b1   = x(9);
b2   = x(10);
v_eps = x(11);

q = [q1; q2];
dq = [dq1; dq2];

%% --- Physical constants ---
m1 = 1.6537;  l1 = 0.343;  r1 = 0.29;
m2 = 0.9982;  l2 = 0.267;  r2 = 0.175;
b  = m2 * l1 * r2;

a1 = m1*r1^2 + m2*l1^2 + I1;
a2 = m2*r2^2 + I2;

c2 = cos(q2);
s2 = sin(q2);

%% --- Mass & Coriolis ---
M = [a1 + a2 + 2*b*c2,  a2 + b*c2;
     a2 + b*c2,         a2];

C = [-b*s2*dq2,           -b*s2*(dq1 + dq2);
      b*s2*dq1,           0];

%% --- Friction ---
z1 = dq1 / v_eps;
z2 = dq2 / v_eps;

tau_f = [b1*dq1 + fc1*tanh(z1);
         b2*dq2 + fc2*tanh(z2)];

%% --- Acceleration ---
Gamma = u - C*dq - tau_f;
ddq = M \ Gamma;

%% =======================================================================
%                        PARTIAL DERIVATIVES
% =======================================================================

%% --- dM/dq ---
dMdq1 = zeros(2);
dMdq2 = [-2*b*s2, -b*s2;
         -b*s2,   0];

%% --- dC/dq ---
dCdq2 = [-b*cos(q2)*dq2,          -b*cos(q2)*(dq1+dq2);
          b*cos(q2)*dq1,          0];
dCdq1 = zeros(2);

%% --- dC/ddq ---
dCddq1 = [ 0,       -b*s2;
           b*s2,    0];

dCddq2 = [-b*s2,  -b*s2;
           0,      0];

%% --- d(tau_f)/ddq ---
dtaudq = zeros(2,2);
dtaudq(1,1) = b1 + fc1/v_eps * sech(z1)^2;
dtaudq(2,2) = b2 + fc2/v_eps * sech(z2)^2;

%% --- d(tau_f)/dpsi ---
dtaudpsi = zeros(2,7);
dtaudpsi(1,3) = tanh(z1);                    % fc1
dtaudpsi(1,5) = dq1;                         % b1
dtaudpsi(1,7) = -(fc1*dq1/v_eps^2)*sech(z1)^2;

dtaudpsi(2,4) = tanh(z2);                    % fc2
dtaudpsi(2,6) = dq2;                         % b2
dtaudpsi(2,7) = -(fc2*dq2/v_eps^2)*sech(z2)^2;

%% --- dGamma/dq ---
dGdq1 = -(dCdq1)*dq;
dGdq2 = -(dCdq2)*dq;

%% --- dGamma/ddq ---
dGddq1 = -(dCddq1*dq + C*[1;0]) - dtaudq(:,1);
dGddq2 = -(dCddq2*dq + C*[0;1]) - dtaudq(:,2);

%% --- dGamma/dpsi ---
dGdpsi = -dtaudpsi;

%% --- dM/dparams (I1, I2) ---
dMdI1 = [1 0; 0 0];
dMdI2 = [1 1; 1 1];
dMdpsi = cat(3, dMdI1, dMdI2);

%% =======================================================================
%                ASSEMBLE SECOND ROW OF F: ∂ddq/∂(...)
% =======================================================================
Minv = inv(M);

% q-derivatives
d2q_dq1 = Minv*( dGdq1 - dMdq1*ddq );
d2q_dq2 = Minv*( dGdq2 - dMdq2*ddq );

% dq-derivatives
d2q_ddq1 = Minv*( dGddq1 - dCddq1*ddq );
d2q_ddq2 = Minv*( dGddq2 - dCddq2*ddq );

% parameter derivatives (7 parameters)
d2q_dpsi = zeros(2,7);
for j = 1:7
    if j <= 2
        dMpsi = dMdpsi(:,:,j);
    else
        dMpsi = zeros(2);
    end
    d2q_dpsi(:,j) = Minv*( dGdpsi(:,j) - dMpsi*ddq );
end

%% =======================================================================
%                        BUILD THE FULL JACOBIAN
% =======================================================================

F = zeros(11,11);

% dq/dq = 0
% dq/ddq = I
F(1:2,3:4) = eye(2);

% second row block: ∂ddq/∂(...)
F(3:4,1)     = d2q_dq1;
F(3:4,2)     = d2q_dq2;
F(3:4,3)     = d2q_ddq1;
F(3:4,4)     = d2q_ddq2;
F(3:4,5:11)  = d2q_dpsi;

% parameter dynamics: dot psi = 0
% so last 7 rows of F are zero

end

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
