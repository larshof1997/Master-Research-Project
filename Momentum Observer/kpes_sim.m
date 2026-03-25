clear all; clc;

%% Time
dt = 0.01;
t_end = 10;
t = (0:dt:t_end)';
N = numel(t);

%% Load desired trajectory
qd   = [sin(t), cos(2*t)];
dqd  = [cos(t), -2*sin(2*t)];
ddqd = [-sin(t), -4*cos(2*t)];

%% Physical constants (from LS analysis)
a1 = 0.092202;
a2 = 0.023242;
bp = 0.027542;

b1 = 0.396193;
b2 = 0.195026;

mass_fn = @(q) M_mat(q(2), a1, a2, bp);
D0      = D_mat(b1, b2);
G0      = eye(2);
gradV   = @(q) [0; 0];

%% Current saturation and torque constants
i_sat1 = 0.92;
i_sat2 = 1.2;
Kt1 = 3.018583e+00;
Kt2 = 1.111065;

% Torque limits
u_max1 = Kt1 * i_sat1;   % ~2.777 Nm
u_max2 = Kt2 * i_sat2;   % ~1.333 Nm

%% Controller gains (no tuning, directly specified)
kp    = 1.7373;
Kd    = diag([12, 5]);
alpha = 0.1827;
kappa = 0.8564;

Kp = kp * eye(2);

%% Observer parameters
ph    = @(q, xp, phi) xp + phi*q;
switchCond = @(phi, Sbar, T_mat) ...
    min(eig(phi*T_mat - 0.5*(Sbar + Sbar'))) - kappa;

%% Preallocate
x_sim    = zeros(N, 4);           % plant state [q1 q2 dq1 dq2]
x_sim(1,:) = [0, 0, 0, 0];       % initial condition: q1=0, q2=1
p_hat    = zeros(N, 2);
u_log    = zeros(N, 2);           % total (saturated) control
u_d_log  = zeros(N, 2);           % KPES feedback (v_k mapped to torque)
uo_log   = zeros(N, 2);           % passive interconnection torque
uff_log  = zeros(N, 2);           % feedforward torque
u_pert_log = zeros(N, 2);         % perturbation (zero here)
qe_log   = zeros(N, 2);
pe_log   = zeros(N, 2);

%% Observer initial conditions
xp  = [0 0];
phi = 0;

%% Simulation loop
for k = 1:N-1

    % Current state
    q_k  = x_sim(k, 1:2);
    dq_k = x_sim(k, 3:4);

    % Observer
    phat_k = ph(q_k, xp, phi);
    out = observer_matrices(q_k, phat_k, bp, a1, a2, D0, G0);
    M_k = mass_fn(q_k');

    % Jump logic
    while switchCond(phi, out.Sbar, out.T) <= 0
        xp     = xp - kappa * q_k;
        phi    = phi + kappa;
        phat_k = ph(q_k, xp, phi);
    end

    % Error coordinates
    qd_k   = qd(k, :)';
    dqd_k  = dqd(k, :)';
    ddqd_k = ddqd(k, :)';

    pd_k = out.Ti * dqd_k;        % target momentum
    qe_k = q_k' - qd_k;           % configuration error
    pe_k = phat_k(:) - pd_k;      % momentum error

    % dpd/dq: only q2 contributes
    dTi_dq2 = get_dTi_dq(q_k, out.Ti, bp);
    dpd_dq  = [zeros(2,1), dTi_dq2 * dqd_k];

    % KPES feedback
    v_k = KPES(out.S, out.D, out.T, Kd, Kp, alpha, qe_k, pe_k);

    % Passive output from tracking error
    dHe_dqe = Kp * (qe_k + alpha * pe_k);
    dHe_dpe = pe_k + alpha * Kp * (qe_k + alpha * pe_k);
    ye_k = -out.T * [eye(2), phi*eye(2) - dpd_dq'] * [dHe_dqe; dHe_dpe];

    % Passive interconnection
    uo_k = -out.G \ ye_k;

    % Feedforward
    u_ff = out.G \ ( ...
        -(out.S - out.D) * pd_k ...
        + out.T * gradV(q_k') ...
        + dpd_dq * (out.T * phat_k(:)) ...
        + out.Ti * ddqd_k ...
        + v_k);

    % Total control input (before saturation)
    u_k = -uo_k + u_ff;

    % Store unsaturated components
    uo_log(k,:)   = uo_k';
    uff_log(k,:)  = u_ff';
    u_d_log(k,:)  = (out.G \ v_k)';   % KPES part mapped to input

    % Apply torque saturation
    u_k(1) = max(-u_max1, min(u_max1, u_k(1)));
    u_k(2) = max(-u_max2, min(u_max2, u_k(2)));

    u_log(k,:) = u_k';

    % Observer flow (RK4)
    obs_rhs = @(xp_) obs_flow(q_k, xp_, phi, out, u_k', gradV, uo_k);
    rk1 = obs_rhs(xp)';
    rk2 = obs_rhs(xp + 0.5*dt*rk1)';
    rk3 = obs_rhs(xp + 0.5*dt*rk2)';
    rk4 = obs_rhs(xp + dt*rk3)';
    xp  = xp + (dt/6)*(rk1 + 2*rk2 + 2*rk3 + rk4);

    % Plant dynamics (RK4) — plant sees saturated torque
    plant_rhs = @(x_) f_dyn(x_, u_k, a1, a2, bp, b1, b2);
    pk1 = plant_rhs(x_sim(k,:)')';
    pk2 = plant_rhs(x_sim(k,:)' + 0.5*dt*pk1')';
    pk3 = plant_rhs(x_sim(k,:)' + 0.5*dt*pk2')';
    pk4 = plant_rhs(x_sim(k,:)' + dt*pk3')';
    x_sim(k+1,:) = x_sim(k,:) + (dt/6)*(pk1 + 2*pk2 + 2*pk3 + pk4);

    % Store
    p_hat(k,:)  = (out.Ti * phat_k(:))';
    qe_log(k,:) = qe_k';
    pe_log(k,:) = pe_k';
end

%% Save .mat file matching Python plotting structure
% Map to expected variable names
phat      = p_hat;
uo        = uo_log;
u_ff_save = uff_log;
u_d       = u_d_log;
u_pert    = u_pert_log;       % zero perturbation
q_desired = qd;
q_meas    = x_sim(:, 1:2);
u_total   = u_log;
e_track   = qe_log;

save('KPES_pert_a1_0.000_a2_0.000.mat', ...
    't', 'dt', ...
    'phat', 'uo', ...
    'u_ff', 'u_d', 'u_pert', ...
    'q_desired', 'q_meas', ...
    'u_total', 'e_track', ...
    'a1', 'a2');

fprintf('Saved KPES_pert_a1_0.000_a2_0.000.mat\n');
fprintf('Torque limits: joint1 = ±%.3f Nm, joint2 = ±%.3f Nm\n', u_max1, u_max2);

%% Plots
figure('Color','w','Name','Tracking');
for j = 1:2
    subplot(2,1,j); hold on; grid on;
    plot(t, x_sim(:,j), 'b', 'LineWidth', 1.5, 'DisplayName', 'q');
    plot(t, qd(:,j), 'r--', 'LineWidth', 1.2, 'DisplayName', 'q_d');
    xlabel('Time [s]'); ylabel(sprintf('q_%d [rad]', j));
    legend('Location','best');
    title(sprintf('Joint %d tracking', j));
end

figure('Color','w','Name','Tracking error norm');
hold on; grid on;
semilogy(t, vecnorm(qe_log, 2, 2), 'b', 'LineWidth', 1.2);
xlabel('Time [s]'); ylabel('||q_e||');
title('Configuration error (log scale)');

figure('Color','w','Name','Control input');
for j = 1:2
    subplot(2,1,j); hold on; grid on;
    plot(t, u_log(:,j), 'b', 'LineWidth', 1.2);
    if j == 1
        yline(u_max1, 'r--', 'LineWidth', 1); yline(-u_max1, 'r--', 'LineWidth', 1);
    else
        yline(u_max2, 'r--', 'LineWidth', 1); yline(-u_max2, 'r--', 'LineWidth', 1);
    end
    xlabel('Time [s]'); ylabel(sprintf('u_%d [Nm]', j));
    title(sprintf('Joint %d torque (saturated)', j));
end

%% ===== Local functions =====

function M = M_mat(theta2, a1, a2, b)
    c2 = cos(theta2);
    M = [a1 + a2 + 2*b*c2,  a2 + b*c2;
         a2 + b*c2,          a2];
end

function D = D_mat(b1, b2)
    D = [b1 0; 0 b2];
end

function dx = f_dyn(x, u, a1, a2, b, b1, b2)
    q  = x(1:2);
    dq = x(3:4);
    M = M_mat(q(2), a1, a2, b);
    C = C_mat(q(2), dq(1), dq(2), b);
    F = [b1*dq(1); b2*dq(2)];
    ddq = M \ (u(:) - C*dq - F);
    dx = [dq; ddq];
end

function C = C_mat(theta2, dtheta1, dtheta2, b)
    s2 = sin(theta2);
    C = [-b*s2*dtheta2,           -b*s2*(dtheta1 + dtheta2);
          b*s2*dtheta1,            0];
end

function out = observer_matrices(q, phat, b, a1, a2, D0, G0)
    q = q(:);  phat = phat(:);
    M  = M_mat(q(2), a1, a2, b);
    T  = sym_sqrt(inv(M));
    Ti = sym_sqrt(M);

    out.D = T * D0 * T;
    out.G = T * G0;
    out.T = T;
    out.Ti = Ti;

    s2 = sin(q(2));
    dM_dq2 = [-2*b*s2, -b*s2; -b*s2, 0];
    dTi_dq2 = sylvester(Ti, Ti, dM_dq2);

    A_mat = [zeros(2,1), dTi_dq2 * phat];
    out.S = T * (A_mat' - A_mat) * T;

    Sbar = zeros(2);
    for i = 1:2
        ei = zeros(2,1); ei(i) = 1;
        A_ei = [zeros(2,1), dTi_dq2 * ei];
        S_ei = T * (A_ei' - A_ei) * T;
        Sbar(:,i) = S_ei * phat;
    end
    out.Sbar = Sbar;
end

function dTi_dq2 = get_dTi_dq(q, Ti, b)
    s2 = sin(q(2));
    dM_dq2 = [-2*b*s2, -b*s2; -b*s2, 0];
    dTi_dq2 = sylvester(Ti, Ti, dM_dq2);
end

function v = KPES(S, D, T, Kd, Kp, alpha, qe, pe)
    z = qe + alpha * pe;
    v = alpha * (S - D - Kd) * Kp * z ...
        - T * Kp * z ...
        - Kd * pe;
end

function dxp = obs_flow(q, xp, phi, out, u, gradV, uo)
    phat = xp(:) + phi*q(:);
    dxp = (out.S - out.D - phi*out.T) * phat ...
          - out.T * gradV(q(:)) ...
          + out.G * (u(:) + uo(:));
end

function Asqrt = sym_sqrt(A)
    [V, W] = eig(A, 'vector');
    W = max(W, 1e-12);
    Asqrt = V * diag(sqrt(W)) * V';
end