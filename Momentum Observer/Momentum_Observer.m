%% Load dataset
S = load('planar_2dof_dataset_gaussian_noise_linear_friction.mat');
dataset = S.dataset;

run_idx = 5;
r = dataset.runs(run_idx);

t           = r.time;
dt          = t(2) - t(1);
N           = numel(t);
tau_applied = r.u_applied;   % Nx2
x_true      = r.x_true;     % Nx4: [th1 th2 dth1 dth2]
x_meas      = r.y_meas;
p_true      = r.p;           % Nx2: canonical momentum

%% Physical constants (true)
m1_true = 1.6537;  l1_true = 0.343;  r1_true = 0.29;  I1_true = 0.039;
m2_true = 0.9982;  l2_true = 0.267;  r2_true = 0.175; I2_true = 0.0081;
% Friction
b1 = 0.02;
b2 = 0.025;

%% Physical constants (perturbed ±5%)
rng('shuffle');
perturb = @() 1 + 0.05*(2*rand - 1);   % <-- FIX: was 0.

m1 = m1_true * perturb();  l1 = l1_true * perturb();
r1 = r1_true * perturb();  I1 = I1_true * perturb();
m2 = m2_true * perturb();  l2 = l2_true * perturb();
r2 = r2_true * perturb();  I2 = I2_true * perturb();
b1 = b1 * perturb();       b2 = b2 * perturb();

a1 = m1*r1^2 + m2*l1^2 + I1;
a2 = m2*r2^2 + I2;
b  = m2*l1*r2;

% Functions
mass_fn = @(q) M_mat(q(2), a1, a2, b);
D0      = D_mat(b1, b2);
G0      = eye(2);              

% Potential energy gradient (zero for horizontal planar arm)
gradV   = @(q) [0; 0];         % add gravity terms if vertical

% Observer
kappa = 10;
ph    = @(q, xp, phi) xp + phi*q;

% Switch condition: min eig(φT - symm(S̄)) ≥ κ
switchCond = @(phi, Sbar, T_mat) ...
    min(eig(phi*T_mat - 0.5*(Sbar + Sbar'))) - kappa;

p_est     = zeros(N, 2);

%% Observer
xp  = [0 0];
phi = 0;

for k = 1:N
    q_k    = x_meas(k, 1:2);
    phat_k = ph(q_k, xp, phi);

    out = observer_matrices([q_k, phat_k], D0, G0, b);

    % --- Jump logic: update xp and phi, phat stays the same ---
    while switchCond(phi, out.Sbar, out.T) <= 0
        xp  = xp - kappa * q_k;      
        phi = phi + kappa;
        phat_k = ph(q_k, xp, phi);    % should be unchanged (sanity)
    end

    % --- Flow dynamics (eq 20) ---
    dxp = (out.S - out.D - phi*out.T) * phat_k' ...
          - out.T * gradV(q_k') ...
          + out.G * (tau_applied(k,:))';

    k1 = obs_flow(q_k, xp, phi, out, tau_applied(k,:), gradV)';
    k2 = obs_flow(q_k, xp + 0.5*dt*k1, phi, out, tau_applied(k,:), gradV)';
    k3 = obs_flow(q_k, xp + 0.5*dt*k2, phi, out, tau_applied(k,:), gradV)';
    k4 = obs_flow(q_k, xp + dt*k3, phi, out, tau_applied(k,:), gradV)';
    xp = xp + (dt/6)*(k1 + 2*k2 + 2*k3 + k4);

    % --- Store: convert back to canonical momentum p0 = Ti * phat ---
    p_est(k, :) = (out.Ti * phat_k')';
end

%% --- Plots ---
figure('Color','w','Name','Momentum comparison');
for j = 1:2
    subplot(2,1,j); hold on; grid on;
    plot(t, p_true(:,j), 'b', 'LineWidth', 1.5, 'DisplayName', 'true');
    h = plot(t, p_est(:,j), 'LineStyle', '--', ...
             'LineWidth', 1.2);
    h.Color = 'r';

    xlabel('Time [s]');
    ylabel(sprintf('p_%d', j));
    legend('Location','best');
    title(sprintf('Joint %d momentum', j));
end

figure('Color','w','Name','Estimation error norm');
hold on; grid on;
    err = vecnorm(p_est(:,:) - p_true, 2, 2);
    semilogy(t, err, 'r', 'LineStyle', '--', ...
             'LineWidth', 1.2);
xlabel('Time [s]');
ylabel('||p_{true} - p_{est}||');
legend('Location','best');
title('Momentum estimation error (log scale)');

%% ========== Functions ==========

function M = M_mat(theta2, a1, a2, b)
    c2 = cos(theta2);
    M = [a1 + a2 + 2*b*c2,  a2 + b*c2;
         a2 + b*c2,          a2];
end

function D = D_mat(b1, b2)
    D = [b1 0; 0 b2];
end

function out = observer_matrices(x, D0, G0, b)
    x = x(:);
    n = length(x)/2;
    q    = x(1:n);
    phat = x(n+1:end);

    M  = mass_fn(q);
    T  = sym_sqrt(inv(M));
    Ti = sym_sqrt(M);

    D = T * D0 * T;
    G = T * G0;

    S_fn = @compute_S;

    S = S_fn(q, phat, T, Ti, b);

    Sbar = zeros(n);
    for i = 1:n
        ei = zeros(n,1); ei(i) = 1;
        S_ei = S_fn(q, ei, T, Ti, b);
        Sbar(:,i) = S_ei * phat;
    end

    out.S = S;  out.Sbar = Sbar;  out.D = D;
    out.G = G;  out.T = T;        out.Ti = Ti;
end

function S = compute_S(q, phat, T, Ti, b)
    % dM/dq1 = 0, so dTi/dq1 = 0, so A(:,1) = 0
    s2 = sin(q(2));
    dM_dq2 = [-2*b*s2, -b*s2;
              -b*s2,    0];

    dTi_dq2 = sylvester(Ti, Ti, dM_dq2);

    A = [zeros(2,1), dTi_dq2 * phat];

    S = T * (A' - A) * T;
end

function Asqrt = sym_sqrt(A)
    [V, W] = eig(A, 'vector');
    W = max(W, 1e-12);
    Asqrt = V * diag(sqrt(W)) * V';
end

function dxp = obs_flow(q, xp, phi, out, u, gradV)
    phat = xp(:) + phi*q(:);
    n = length(q);
    dxp = (out.S - out.D - phi*out.T) * phat ...
          - out.T * gradV(q(:)) ...
          + out.G * u(:);
end


%% Controller functions momentum observer
function pd = target_momentum(Ti, qd)
    pd = Ti * qd;
end

function dTi_dq = get_dTi_dq(q, Ti, b)
    % dM/dq1 = 0, so dTi/dq1 = 0, so A(:,1) = 0
    s2 = sin(q(2));
    dM_dq2 = [-2*b*s2, -b*s2;
              -b*s2,    0];

    dTi_dq = sylvester(Ti, Ti, dM_dq2);
end

function u = feedforward(q, qd, qdd, u0, G0, D0, gradV, phat, v)
    out = observer_matrices([q, phat], mass_fn, D0, G0, b); 
    pd = target_momentum(Ti, qd);
    dTi_dq = get_dTi_dq(q, Ti, b);

    u = -u0 + (...
        -(out.S-out.D)*pd...
        + out.T*gradV...
        + dTi_dq*qd*out.T*phat...
        + out.Ti*qdd...
        + v...
        )/out.G;
end

function v = KPES(S, D, T, Kd, Kp, alpha, qe, pe)
    z = qe + alpha * pe;
    v = alpha * (S - D - Kd) * Kp * z ...
        - T * Kp * z ...
        - Kd * pe;
end

