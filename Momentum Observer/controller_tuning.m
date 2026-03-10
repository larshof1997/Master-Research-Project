clear all; clc;
%%Time
dt = 0.001;          % smaller step for accuracy (especially ISA sign())
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

%% Initial condition (shared across all controllers)
x0_plant = [0.5, -0.3, 0, 0];  % [q1, q2, dq1, dq2]

%% ========================================================================
%  Ferguson 2025 controller
%  ========================================================================

%% Ferguson tuning (Lyapunov-based, same as your original)
kd_ferg = 1;
M0 = mass_fn([0;0]);
T0 = sqrtm(inv(M0));

Kp_fn = @(kp) kp*eye(2);
Kd_fn = @(kd) kd*eye(2);
Q_fn = @(kp, kd, alpha) [Kp_fn(kp), alpha*Kp_fn(kp); ...
                          alpha*Kp_fn(kp), eye(2) + alpha^2*Kp_fn(kp)];
Rcl_fn = @(kp, kd, alpha) [alpha*T0, zeros(2); zeros(2), D0+Kd_fn(kd)];

cost_ferg = @(x) -min(eig(Q_fn(x(1),kd_ferg,x(2))*Rcl_fn(x(1),kd_ferg,x(2))*Q_fn(x(1),kd_ferg,x(2)))) ...
                  / max(eig(Q_fn(x(1),kd_ferg,x(2))));

opts_fmin = optimoptions('fmincon','Display','off');
x_opt_f = fmincon(cost_ferg, [6; 0.2], -eye(2), zeros(2,1), [],[],[],[],[], opts_fmin);
kp_ferg    = x_opt_f(1);
alpha_ferg = x_opt_f(2);
kappa_ferg = 2*min(eig(Q_fn(kp_ferg,kd_ferg,alpha_ferg) * ...
             Rcl_fn(kp_ferg,kd_ferg,alpha_ferg) * ...
             Q_fn(kp_ferg,kd_ferg,alpha_ferg))) / ...
             max(eig(Q_fn(kp_ferg,kd_ferg,alpha_ferg)));

fprintf('=== Ferguson 2025 ===\n');
fprintf('  kp = %.4f, kd = %.4f, alpha = %.4f, kappa = %.4f\n', ...
    kp_ferg, kd_ferg, alpha_ferg, kappa_ferg);

%% Ferguson simulation
Kp_f = kp_ferg * eye(2);
Kd_f = kd_ferg * eye(2);

x_ferg = zeros(N, 4);
x_ferg(1,:) = x0_plant;
u_ferg = zeros(N, 2);

xp_obs = [0 0];
phi_obs = 0;

for k = 1:N-1
    q_k  = x_ferg(k,1:2);
    dq_k = x_ferg(k,3:4);

    phat_k = xp_obs' + phi_obs*q_k';
    out = observer_matrices(q_k, phat_k, bp, a1, a2, D0, G0);

    % Jump logic
    while min(eig(phi_obs*out.T - 0.5*(out.Sbar + out.Sbar'))) - kappa_ferg <= 0
        xp_obs = xp_obs - kappa_ferg * q_k;
        phi_obs = phi_obs + kappa_ferg;
        phat_k = xp_obs' + phi_obs*q_k';
        out = observer_matrices(q_k, phat_k, bp, a1, a2, D0, G0);
    end

    qd_k   = qd(k,:)';
    dqd_k  = dqd(k,:)';
    ddqd_k = ddqd(k,:)';

    pd_k = out.Ti * dqd_k;
    qe_k = q_k' - qd_k;
    pe_k = phat_k(:) - pd_k;

    dTi_dq2 = get_dTi_dq(q_k, out.Ti, bp);
    dpd_dq  = [zeros(2,1), dTi_dq2 * dqd_k];

    % KPES
    z_k = qe_k + alpha_ferg * pe_k;
    v_k = alpha_ferg*(out.S - out.D - Kd_f)*Kp_f*z_k - out.T*Kp_f*z_k - Kd_f*pe_k;

    % Passive output & observer input
    dHe_dqe = Kp_f * z_k;
    dHe_dpe = pe_k + alpha_ferg * Kp_f * z_k;
    ye_k = -out.T * [eye(2), phi_obs*eye(2) - dpd_dq'] * [dHe_dqe; dHe_dpe];
    uo_k = -out.G \ ye_k;

    % Feedforward + total control
    u_ff = out.G \ (-(out.S - out.D)*pd_k + out.T*gradV(q_k') ...
           + dpd_dq*(out.T*phat_k(:)) + out.Ti*ddqd_k + v_k);
    u_k = -uo_k + u_ff;
    u_ferg(k,:) = u_k';

    % Observer flow (RK4)
    obs_rhs = @(xp_) obs_flow_vec(q_k, xp_, phi_obs, out, u_k, gradV, uo_k);
    ok1 = obs_rhs(xp_obs);
    ok2 = obs_rhs(xp_obs + 0.5*dt*ok1);
    ok3 = obs_rhs(xp_obs + 0.5*dt*ok2);
    ok4 = obs_rhs(xp_obs + dt*ok3);
    xp_obs = xp_obs + (dt/6)*(ok1 + 2*ok2 + 2*ok3 + ok4);

    % Plant (RK4)
    pk1 = f_dyn(x_ferg(k,:)', u_k, a1, a2, bp, b1, b2)';
    pk2 = f_dyn(x_ferg(k,:)' + 0.5*dt*pk1', u_k, a1, a2, bp, b1, b2)';
    pk3 = f_dyn(x_ferg(k,:)' + 0.5*dt*pk2', u_k, a1, a2, bp, b1, b2)';
    pk4 = f_dyn(x_ferg(k,:)' + dt*pk3', u_k, a1, a2, bp, b1, b2)';
    x_ferg(k+1,:) = x_ferg(k,:) + (dt/6)*(pk1 + 2*pk2 + 2*pk3 + pk4);
end

%% ========================================================================
%  Cruz 2021 controller
%  ========================================================================
%
%  Control law (from the reference):
%    qt    = q - qd
%    nu    = x_f + B*qt
%    dx_f  = -A * sat(nu, 1/r1)
%    tau_ff = gradV(q) + M(q)*ddqd + C(q,dqd)*dqd + D0*dqd
%    tau_pd = -P * sat(qt, power) - D_ctrl * sat(nu, power)
%    u      = G0 \ (tau_ff + tau_pd)
%
%  power = (2 - r1)/r1,   r1 in (1, 2)

fprintf('\n=== Cruz 2021 tuning (simulation-based) ===\n');

r1_cruz    = 1.5;
power_cruz = (2 - r1_cruz) / r1_cruz;   % = 1/3
delta_cruz = 100;

% Simulation-based cost: run sim and return integral of ||qe||^2
% Optimise [p1, p2, d1, d2, a_f]
cost_cruz_wrap = @(x) sim_cruz_cost(x, r1_cruz, power_cruz, delta_cruz, ...
    x0_plant, dt, t, qd, dqd, ddqd, a1, a2, bp, b1, b2, D0, G0);

x0_cruz = [7; 4; 4; 2; 7];
lb_cruz = [0.5; 0.5; 0.1; 0.1; 0.5];
ub_cruz = [100; 100; 50; 50; 50];

opts_sim = optimoptions('fmincon','Display','iter','MaxFunctionEvaluations',300, ...
    'FiniteDifferenceStepSize',0.5, 'OptimalityTolerance',1e-4);
x_opt_cruz = fmincon(cost_cruz_wrap, x0_cruz, [],[],[],[], lb_cruz, ub_cruz, [], opts_sim);

P_cruz = diag(x_opt_cruz(1:2));
D_cruz = diag(x_opt_cruz(3:4));
A_cruz = x_opt_cruz(5) * eye(2);
B_cruz = eye(2);

fprintf('  P  = diag(%.2f, %.2f)\n', x_opt_cruz(1), x_opt_cruz(2));
fprintf('  D  = diag(%.2f, %.2f)\n', x_opt_cruz(3), x_opt_cruz(4));
fprintf('  A  = %.2f * I\n', x_opt_cruz(5));
fprintf('  r1 = %.2f,  power = %.4f\n', r1_cruz, power_cruz);

%% Cruz 2021 simulation (full, fine dt)
x_cruz = zeros(N, 4);
x_cruz(1,:) = x0_plant;
u_cruz = zeros(N, 2);
xf_cruz = zeros(2,1);

for k = 1:N-1
    q_k  = x_cruz(k,1:2)';
    dq_k = x_cruz(k,3:4)';

    qd_k   = qd(k,:)';
    dqd_k  = dqd(k,:)';
    ddqd_k = ddqd(k,:)';

    qt_k = q_k - qd_k;
    nu_k = xf_cruz + B_cruz * qt_k;

    M_k = mass_fn(q_k);
    C_k = C_mat(q_k(2), dqd_k(1), dqd_k(2), bp);
    tau_ff = gradV(q_k) + M_k*ddqd_k + C_k*dqd_k + D0*dqd_k;
    tau_pd = -P_cruz*sat_vec_fn(qt_k, power_cruz, delta_cruz) ...
             -D_cruz*sat_vec_fn(nu_k, power_cruz, delta_cruz);

    u_k = G0 \ (tau_ff + tau_pd);
    u_cruz(k,:) = u_k';

    % Filter dynamics (RK4)
    dxf = @(xf_) -A_cruz * sat_vec_fn(xf_ + B_cruz*qt_k, 1/r1_cruz, delta_cruz);
    fk1 = dxf(xf_cruz);
    fk2 = dxf(xf_cruz + 0.5*dt*fk1);
    fk3 = dxf(xf_cruz + 0.5*dt*fk2);
    fk4 = dxf(xf_cruz + dt*fk3);
    xf_cruz = xf_cruz + (dt/6)*(fk1 + 2*fk2 + 2*fk3 + fk4);

    % Plant (RK4)
    pk1 = f_dyn(x_cruz(k,:)', u_k, a1, a2, bp, b1, b2)';
    pk2 = f_dyn(x_cruz(k,:)'+0.5*dt*pk1', u_k, a1, a2, bp, b1, b2)';
    pk3 = f_dyn(x_cruz(k,:)'+0.5*dt*pk2', u_k, a1, a2, bp, b1, b2)';
    pk4 = f_dyn(x_cruz(k,:)'+dt*pk3', u_k, a1, a2, bp, b1, b2)';
    x_cruz(k+1,:) = x_cruz(k,:) + (dt/6)*(pk1 + 2*pk2 + 2*pk3 + pk4);
end

%% ========================================================================
%  Rascon 2020 IET controller
%  ========================================================================
%
%  Control law:
%    z1    = q - qd
%    tau_c = -K1*z1 - z3
%    dz3   = -K1*z1 - K2*z3
%    u     = G0 \ (gradV + M*ddqd + C(q,dqd)*dqd + D0*dqd + tau_c)

fprintf('\n=== Rascon 2020 IET tuning (simulation-based) ===\n');

cost_riet_wrap = @(x) sim_riet_cost(x, x0_plant, dt, t, qd, dqd, ddqd, ...
    a1, a2, bp, b1, b2, D0, G0);

x0_riet = [50; 10];
lb_riet = [1; 1];
ub_riet = [200; 200];

opts_sim2 = optimoptions('fmincon','Display','iter','MaxFunctionEvaluations',200, ...
    'FiniteDifferenceStepSize',1.0, 'OptimalityTolerance',1e-4);
x_opt_riet = fmincon(cost_riet_wrap, x0_riet, [],[],[],[], lb_riet, ub_riet, [], opts_sim2);

K1_iet = x_opt_riet(1) * eye(2);
K2_iet = x_opt_riet(2) * eye(2);

fprintf('  K1 = %.2f\n', x_opt_riet(1));
fprintf('  K2 = %.2f\n', x_opt_riet(2));

%% Rascon IET simulation (full)
x_riet = zeros(N, 4);
x_riet(1,:) = x0_plant;
u_riet = zeros(N, 2);
z3_riet = zeros(2,1);

for k = 1:N-1
    q_k  = x_riet(k,1:2)';
    dq_k = x_riet(k,3:4)';

    qd_k   = qd(k,:)';
    dqd_k  = dqd(k,:)';
    ddqd_k = ddqd(k,:)';

    z1_k = q_k - qd_k;
    tau_c = -K1_iet*z1_k - z3_riet;

    M_k = mass_fn(q_k);
    C_k = C_mat(q_k(2), dqd_k(1), dqd_k(2), bp);
    tau_ff = gradV(q_k) + M_k*ddqd_k + C_k*dqd_k + D0*dqd_k;

    u_k = G0 \ (tau_ff + tau_c);
    u_riet(k,:) = u_k';

    % z3 dynamics (RK4)
    dz3 = @(z3_) -K1_iet*z1_k - K2_iet*z3_;
    zk1 = dz3(z3_riet);
    zk2 = dz3(z3_riet + 0.5*dt*zk1);
    zk3 = dz3(z3_riet + 0.5*dt*zk2);
    zk4 = dz3(z3_riet + dt*zk3);
    z3_riet = z3_riet + (dt/6)*(zk1 + 2*zk2 + 2*zk3 + zk4);

    % Plant (RK4)
    pk1 = f_dyn(x_riet(k,:)', u_k, a1, a2, bp, b1, b2)';
    pk2 = f_dyn(x_riet(k,:)'+0.5*dt*pk1', u_k, a1, a2, bp, b1, b2)';
    pk3 = f_dyn(x_riet(k,:)'+0.5*dt*pk2', u_k, a1, a2, bp, b1, b2)';
    pk4 = f_dyn(x_riet(k,:)'+dt*pk3', u_k, a1, a2, bp, b1, b2)';
    x_riet(k+1,:) = x_riet(k,:) + (dt/6)*(pk1 + 2*pk2 + 2*pk3 + pk4);
end

%% ========================================================================
%  Rascon 2020 ISA controller  (sliding mode, position-only)
%  ========================================================================
%
%  Control law:
%    z1    = q - qd
%    tau_c = C(q,dqd)*dqd - K1*sign(z1) - K2*z1
%    u     = G0 \ (gradV + M*ddqd + tau_c)
%
%  NOTE: no D0*dqd in feedforward (matches reference exactly).

fprintf('\n=== Rascon 2020 ISA tuning (simulation-based) ===\n');

cost_risa_wrap = @(x) sim_risa_cost(x, x0_plant, dt, t, qd, dqd, ddqd, ...
    a1, a2, bp, b1, b2, D0, G0);

x0_risa = [10; 10];
lb_risa = [0.5; 0.5];
ub_risa = [200; 200];

x_opt_risa = fmincon(cost_risa_wrap, x0_risa, [],[],[],[], lb_risa, ub_risa, [], opts_sim2);

K1_isa = x_opt_risa(1) * eye(2);
K2_isa = x_opt_risa(2) * eye(2);

fprintf('  K1 = %.2f\n', x_opt_risa(1));
fprintf('  K2 = %.2f\n', x_opt_risa(2));

%% Rascon ISA simulation (full)
x_risa = zeros(N, 4);
x_risa(1,:) = x0_plant;
u_risa = zeros(N, 2);

for k = 1:N-1
    tk = t(k);

    % Embed control in RK4 for proper sign() evaluation at sub-steps
    x_curr = x_risa(k,:)';
    pk1 = f_dyn_risa(x_curr,            tk,         a1,a2,bp,b1,b2, K1_isa, K2_isa, G0);
    pk2 = f_dyn_risa(x_curr+0.5*dt*pk1, tk+0.5*dt,  a1,a2,bp,b1,b2, K1_isa, K2_isa, G0);
    pk3 = f_dyn_risa(x_curr+0.5*dt*pk2, tk+0.5*dt,  a1,a2,bp,b1,b2, K1_isa, K2_isa, G0);
    pk4 = f_dyn_risa(x_curr+dt*pk3,     tk+dt,      a1,a2,bp,b1,b2, K1_isa, K2_isa, G0);
    x_risa(k+1,:) = (x_curr + (dt/6)*(pk1 + 2*pk2 + 2*pk3 + pk4))';

    % Log control for plotting
    q_k    = x_risa(k,1:2)';
    qd_k   = qd(k,:)';
    dqd_k  = dqd(k,:)';
    ddqd_k = ddqd(k,:)';
    z1_k   = q_k - qd_k;
    M_k    = mass_fn(q_k);
    C_k    = C_mat(q_k(2), dqd_k(1), dqd_k(2), bp);
    tau_c  = C_k*dqd_k - K1_isa*sign(z1_k) - K2_isa*z1_k;
    u_risa(k,:) = (G0 \ (gradV(q_k) + M_k*ddqd_k + tau_c))';
end

%% ========================================================================
%  Compute comparison metrics
%  ========================================================================

qe_norm_ferg = zeros(N,1);
qe_norm_cruz = zeros(N,1);
qe_norm_riet = zeros(N,1);
qe_norm_risa = zeros(N,1);

uDiffNorm_ferg = zeros(N,1);
uDiffNorm_cruz = zeros(N,1);
uDiffNorm_riet = zeros(N,1);
uDiffNorm_risa = zeros(N,1);

for k = 1:N
    tk = t(k);
    qd_k   = [sin(tk); cos(2*tk)];
    dqd_k  = [cos(tk); -2*sin(2*tk)];
    ddqd_k = [-sin(tk); -4*cos(2*tk)];

    M_d = mass_fn(qd_k);
    C_d = C_mat(qd_k(2), dqd_k(1), dqd_k(2), bp);
    uRef_k = G0 \ (M_d*ddqd_k + C_d*dqd_k + D0*dqd_k);

    qe_norm_ferg(k) = norm(x_ferg(k,1:2)' - qd_k);
    qe_norm_cruz(k) = norm(x_cruz(k,1:2)' - qd_k);
    qe_norm_riet(k) = norm(x_riet(k,1:2)' - qd_k);
    qe_norm_risa(k) = norm(x_risa(k,1:2)' - qd_k);

    uDiffNorm_ferg(k) = norm(u_ferg(k,:)' - uRef_k);
    uDiffNorm_cruz(k) = norm(u_cruz(k,:)' - uRef_k);
    uDiffNorm_riet(k) = norm(u_riet(k,:)' - uRef_k);
    uDiffNorm_risa(k) = norm(u_risa(k,:)' - uRef_k);
end

%% ========================================================================
%  Comparison plots
%  ========================================================================

set(0,'DefaultTextInterpreter','latex');
set(0,'DefaultLegendInterpreter','latex');
set(0,'DefaultAxesFontSize',11);
set(0,'DefaultLineLineWidth',1.5);

figure('Name','Comparison','Color','w','Position',[100 100 1200 500]);

% Left: control effort deviation
ax1 = subplot(1,2,1); hold on; grid on;
plot(t, uDiffNorm_ferg, 'DisplayName','Ferguson 2025');
plot(t, uDiffNorm_cruz, 'DisplayName','Cruz 2021');
plot(t, uDiffNorm_riet, 'DisplayName','Rascon 2020 IET');
plot(t, uDiffNorm_risa, 'DisplayName','Rascon 2020 ISA');
set(ax1,'YScale','log');
xlabel('Time [s]'); ylabel('$\|u(t) - u_d(t)\|$');
legend('Location','best');

% Inset
axes('Position',[0.17 0.17 0.12 0.22]); hold on; box on; grid on;
plot(t, uDiffNorm_ferg); plot(t, uDiffNorm_cruz);
plot(t, uDiffNorm_riet); plot(t, uDiffNorm_risa);
xlim([0 0.5]); set(gca,'YScale','log');

% Right: tracking error
ax2 = subplot(1,2,2); hold on; grid on;
plot(t, qe_norm_ferg, 'DisplayName','Ferguson 2025');
plot(t, qe_norm_cruz, 'DisplayName','Cruz 2021');
plot(t, qe_norm_riet, 'DisplayName','Rascon 2020 IET');
plot(t, qe_norm_risa, 'DisplayName','Rascon 2020 ISA');
set(ax2,'YScale','log');
xlabel('Time [s]'); ylabel('$\|q(t) - q_d(t)\|$');
legend('Location','best');

% Inset
axes('Position',[0.62 0.17 0.12 0.22]); hold on; box on; grid on;
plot(t, qe_norm_ferg); plot(t, qe_norm_cruz);
plot(t, qe_norm_riet); plot(t, qe_norm_risa);
xlim([0 0.5]); set(gca,'YScale','log');

%% Per-joint tracking
figure('Name','Per-joint tracking','Color','w','Position',[100 100 1400 700]);
for j = 1:2
    subplot(2,2,j); hold on; grid on;
    plot(t, qd(:,j), 'k--', 'LineWidth',1.0, 'DisplayName','$q_d$');
    plot(t, x_ferg(:,j), 'DisplayName','Ferguson');
    plot(t, x_cruz(:,j), 'DisplayName','Cruz');
    plot(t, x_riet(:,j), 'DisplayName','Rascon IET');
    plot(t, x_risa(:,j), 'DisplayName','Rascon ISA');
    xlabel('Time [s]'); ylabel(sprintf('$q_%d$ [rad]',j));
    legend('Location','best'); title(sprintf('Joint %d tracking',j));
end
for j = 1:2
    subplot(2,2,2+j); hold on; grid on;
    plot(t, u_ferg(:,j), 'DisplayName','Ferguson');
    plot(t, u_cruz(:,j), 'DisplayName','Cruz');
    plot(t, u_riet(:,j), 'DisplayName','Rascon IET');
    plot(t, u_risa(:,j), 'DisplayName','Rascon ISA');
    xlabel('Time [s]'); ylabel(sprintf('$u_%d$ [Nm]',j));
    legend('Location','best'); title(sprintf('Joint %d torque',j));
end

%% ========================================================================
%  SIMULATION-BASED COST FUNCTIONS  (for tuning)
%  ========================================================================
%  These run a coarser simulation (larger substep, Euler integration,
%  first 3 seconds only) to evaluate how well a given set of gains tracks
%  the reference. The cost is  J = integral ||q - qd||^2 dt.

function J = sim_cruz_cost(x, r1, power, delta, x0, dt, t, qd, dqd, ddqd, ...
                           a1, a2, bp, b1, b2, D0, G0)
    P_  = diag(x(1:2));
    Dc_ = diag(x(3:4));
    Af_ = x(5) * eye(2);
    Bf_ = eye(2);
    gradV_ = @(q) [0;0];
    mass_  = @(q) M_mat(q(2), a1, a2, bp);
    
    N_ = numel(t);
    x_s = x0(:)';      % row vector [q1 q2 dq1 dq2]
    xf_ = zeros(2,1);
    J = 0;
    
    % Subsample for speed: step every ds samples
    ds = max(1, round(0.01/dt));   % effective ~0.01s steps
    dt_s = dt * ds;
    t_lim = min(N_-1, round(5/dt));  % simulate 5 seconds
    
    for k = 1:ds:t_lim
        q_  = x_s(1:2)';
        qd_ = qd(k,:)';  dqd_ = dqd(k,:)';  ddqd_ = ddqd(k,:)';
        
        qt_ = q_ - qd_;
        nu_ = xf_ + Bf_*qt_;
        
        M_  = mass_(q_);
        C_  = C_mat(q_(2), dqd_(1), dqd_(2), bp);
        tau_ff_ = gradV_(q_) + M_*ddqd_ + C_*dqd_ + D0*dqd_;
        tau_pd_ = -P_*sat_vec_fn(qt_, power, delta) - Dc_*sat_vec_fn(nu_, power, delta);
        u_  = G0 \ (tau_ff_ + tau_pd_);
        u_  = max(min(u_, 100), -100);
        
        % Filter (Euler)
        xf_ = xf_ + dt_s * (-Af_ * sat_vec_fn(xf_ + Bf_*qt_, 1/r1, delta));
        
        % Plant (Euler)
        dx_ = f_dyn([x_s'; zeros(0,1)], u_, a1, a2, bp, b1, b2);
        x_s = x_s + dt_s * dx_';
        
        if any(abs(x_s) > 50)
            J = 1e8;
            return;
        end
        
        J = J + norm(qt_)^2 * dt_s;
    end
end

function J = sim_riet_cost(x, x0, dt, t, qd, dqd, ddqd, ...
                           a1, a2, bp, b1, b2, D0, G0)
    K1_ = x(1) * eye(2);
    K2_ = x(2) * eye(2);
    gradV_ = @(q) [0;0];
    mass_  = @(q) M_mat(q(2), a1, a2, bp);
    
    N_ = numel(t);
    x_s = x0(:)';
    z3_ = zeros(2,1);
    J = 0;
    
    ds = max(1, round(0.01/dt));
    dt_s = dt * ds;
    t_lim = min(N_-1, round(5/dt));
    
    for k = 1:ds:t_lim
        q_  = x_s(1:2)';
        qd_ = qd(k,:)';  dqd_ = dqd(k,:)';  ddqd_ = ddqd(k,:)';
        
        z1_ = q_ - qd_;
        tau_c_ = -K1_*z1_ - z3_;
        
        M_  = mass_(q_);
        C_  = C_mat(q_(2), dqd_(1), dqd_(2), bp);
        tau_ff_ = gradV_(q_) + M_*ddqd_ + C_*dqd_ + D0*dqd_;
        u_  = G0 \ (tau_ff_ + tau_c_);
        u_  = max(min(u_, 100), -100);
        
        z3_ = z3_ + dt_s * (-K1_*z1_ - K2_*z3_);
        
        dx_ = f_dyn([x_s'; zeros(0,1)], u_, a1, a2, bp, b1, b2);
        x_s = x_s + dt_s * dx_';
        
        if any(abs(x_s) > 50)
            J = 1e8;
            return;
        end
        
        J = J + norm(z1_)^2 * dt_s;
    end
end

function J = sim_risa_cost(x, x0, dt, t, qd, dqd, ddqd, ...
                           a1, a2, bp, b1, b2, D0, G0)
    K1_ = x(1) * eye(2);
    K2_ = x(2) * eye(2);
    mass_  = @(q) M_mat(q(2), a1, a2, bp);
    
    N_ = numel(t);
    x_s = x0(:)';
    J = 0;
    
    ds = max(1, round(0.005/dt));  % finer for sign()
    dt_s = dt * ds;
    t_lim = min(N_-1, round(5/dt));
    
    for k = 1:ds:t_lim
        q_  = x_s(1:2)';
        qd_ = qd(k,:)';  dqd_ = dqd(k,:)';  ddqd_ = ddqd(k,:)';
        
        z1_ = q_ - qd_;
        M_  = mass_(q_);
        C_  = C_mat(q_(2), dqd_(1), dqd_(2), bp);
        tau_c_ = C_*dqd_ - K1_*sign(z1_) - K2_*z1_;
        u_  = G0 \ ([0;0] + M_*ddqd_ + tau_c_);
        u_  = max(min(u_, 100), -100);
        
        dx_ = f_dyn([x_s'; zeros(0,1)], u_, a1, a2, bp, b1, b2);
        x_s = x_s + dt_s * dx_';
        
        if any(abs(x_s) > 50)
            J = 1e8;
            return;
        end
        
        J = J + norm(z1_)^2 * dt_s;
    end
end

%% ========================================================================
%  Plant & observer helper functions
%  ========================================================================

function M = M_mat(theta2, a1, a2, b)
    c2 = cos(theta2);
    M = [a1 + a2 + 2*b*c2,  a2 + b*c2;
         a2 + b*c2,          a2];
end

function D = D_mat(b1, b2)
    D = [b1 0; 0 b2];
end

function C = C_mat(theta2, dtheta1, dtheta2, b)
    s2 = sin(theta2);
    C = [-b*s2*dtheta2,           -b*s2*(dtheta1 + dtheta2);
          b*s2*dtheta1,            0];
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

function dx = f_dyn_risa(x, t, a1, a2, bp, b1, b2, K1, K2, G0)
    q  = x(1:2);
    dq = x(3:4);
    qd_t   = [sin(t); cos(2*t)];
    dqd_t  = [cos(t); -2*sin(2*t)];
    ddqd_t = [-sin(t); -4*cos(2*t)];
    
    z1 = q - qd_t;
    M  = M_mat(q(2), a1, a2, bp);
    C_dqd = C_mat(q(2), dqd_t(1), dqd_t(2), bp);
    tau_c = C_dqd*dqd_t - K1*sign(z1) - K2*z1;
    u = G0 \ ([0;0] + M*ddqd_t + tau_c);
    
    C_full = C_mat(q(2), dq(1), dq(2), bp);
    F = [b1*dq(1); b2*dq(2)];
    ddq = M \ (u - C_full*dq - F);
    dx = [dq; ddq];
end

%% Observer functions (Ferguson)

function out = observer_matrices(q, phat, b, a1, a2, D0, G0)
    q = q(:); phat = phat(:);
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
    A_obs = [zeros(2,1), dTi_dq2 * phat];
    out.S = T * (A_obs' - A_obs) * T;
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

function dxp = obs_flow_vec(q, xp, phi, out, u, gradV, uo)
    phat = xp(:) + phi*q(:);
    dxp_col = (out.S - out.D - phi*out.T)*phat ...
              - out.T*gradV(q(:)) + out.G*(u(:) + uo(:));
    dxp = dxp_col';
end

function Asqrt = sym_sqrt(A)
    [V, W] = eig(A, 'vector');
    W = max(W, 1e-12);
    Asqrt = V * diag(sqrt(W)) * V';
end

%% Saturation (Cruz 2021)

function out = sat_vec_fn(x, p, delta)
    out = zeros(size(x));
    for i = 1:length(x)
        if abs(x(i)) < delta
            out(i) = sign(x(i)) * abs(x(i))^p;
        else
            out(i) = sign(x(i)) * delta^p;
        end
    end
end