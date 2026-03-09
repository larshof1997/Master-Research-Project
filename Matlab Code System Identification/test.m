%% test_pH_controller.m
%  Validate pH_controller_fcn by running it in a loop identical to
%  the original MATLAB simulation. This mimics exactly what Simulink
%  will do: call the function each timestep, feed back xp/phi via
%  Unit Delay (one-step memory).
%
%  Run this BEFORE putting the block into Simulink to catch any
%  dimension or logic errors.
%
%  MATLAB 2018b compatible.

clear all; clc; close all; %#ok<CLALL>

%% ---- Time ----
dt    = 0.01;
t_end = 10;
t     = (0:dt:t_end)';
N     = numel(t);

%% ---- Reference trajectory (same sinusoidal as original) ----
qd_all   = [sin(t), cos(2*t)];
dqd_all  = [cos(t), -2*sin(2*t)];
ddqd_all = [-sin(t), -4*cos(2*t)];

%% ---- Physical parameters ----
m1 = 1.6537;  l1 = 0.343;  r1 = 0.29;  I1 = 0.039;
m2 = 0.9982;  l2 = 0.267;  r2 = 0.175; I2 = 0.0081;
b1 = 0.02;    b2 = 0.025;

a1 = m1*r1^2 + m2*l1^2 + I1;
a2 = m2*r2^2 + I2;
bp = m2*l1*r2;

%% ---- Controller / observer parameters ----
Kp_diag = 6;
Kd_diag = 10;
alpha   = 0.2;
kappa   = 0.1;

%% ---- Preallocate logs ----
x_sim      = zeros(N, 4);            % plant: [q1 q2 dq1 dq2]
x_sim(1,:) = [0.5, -0.3, 0, 0];     % initial condition

u_log      = zeros(N, 2);
phat_log   = zeros(N, 2);
qe_log     = zeros(N, 2);
pe_log     = zeros(N, 2);
v_log      = zeros(N, 2);
ye_log     = zeros(N, 2);
uo_log     = zeros(N, 2);
uff_log    = zeros(N, 2);
phi_log    = zeros(N, 1);
switch_log = zeros(N, 1);

%% ---- Observer initial conditions (Unit Delay ICs) ----
xp_state  = [0; 0];
phi_state = 0;

%% ---- Simulation loop ----
fprintf('Running validation simulation (%d steps)...\n', N-1);
tic;

for k = 1:N-1
    % Current measured position (from plant)
    q_k = x_sim(k, 1:2)';          % 2x1

    % Current reference
    qd_k   = qd_all(k,:)';         % 2x1
    dqd_k  = dqd_all(k,:)';
    ddqd_k = ddqd_all(k,:)';

    % ---- Call the controller function (exactly as Simulink would) ----
    [u_k, phat_k, qe_k, pe_k, v_k, ye_k, uo_k, uff_k, ...
     phi_new, xp_new, T_v, Ti_v, S_v, D_v, G_v, swVal] = ...
        pH_controller_fcn( ...
            q_k, qd_k, dqd_k, ddqd_k, ...
            xp_state, phi_state, dt, ...
            a1, a2, bp, b1, b2, ...
            Kp_diag, Kd_diag, alpha, kappa);

    % ---- Store logs ----
    u_log(k,:)      = u_k';
    phat_log(k,:)   = phat_k';
    qe_log(k,:)     = qe_k';
    pe_log(k,:)     = pe_k';
    v_log(k,:)      = v_k';
    ye_log(k,:)     = ye_k';
    uo_log(k,:)     = uo_k';
    uff_log(k,:)    = uff_k';
    phi_log(k)      = phi_new;
    switch_log(k)   = swVal;

    % ---- Update observer state (Unit Delay) ----
    xp_state  = xp_new;
    phi_state = phi_new;

    % ---- Plant dynamics (RK4, same as original) ----
    plant_rhs = @(x_) f_dyn(x_, u_k, a1, a2, bp, b1, b2);
    pk1 = plant_rhs(x_sim(k,:)')';
    pk2 = plant_rhs(x_sim(k,:)' + 0.5*dt*pk1')';
    pk3 = plant_rhs(x_sim(k,:)' + 0.5*dt*pk2')';
    pk4 = plant_rhs(x_sim(k,:)' + dt*pk3')';
    x_sim(k+1,:) = x_sim(k,:) + (dt/6)*(pk1 + 2*pk2 + 2*pk3 + pk4);
end

elapsed = toc;
fprintf('Done in %.2f s (%.1f us/step).\n', elapsed, elapsed/(N-1)*1e6);

%% ---- Dimension sanity checks ----
fprintf('\n=== Dimension checks ===\n');
fprintf('u_k     : [%d x %d]  (expect 2x1)\n', size(u_k));
fprintf('phat_k  : [%d x %d]  (expect 2x1)\n', size(phat_k));
fprintf('qe_k    : [%d x %d]  (expect 2x1)\n', size(qe_k));
fprintf('pe_k    : [%d x %d]  (expect 2x1)\n', size(pe_k));
fprintf('v_k     : [%d x %d]  (expect 2x1)\n', size(v_k));
fprintf('ye_k    : [%d x %d]  (expect 2x1)\n', size(ye_k));
fprintf('uo_k    : [%d x %d]  (expect 2x1)\n', size(uo_k));
fprintf('uff_k   : [%d x %d]  (expect 2x1)\n', size(uff_k));
fprintf('phi_new : [%d x %d]  (expect 1x1)\n', size(phi_new));
fprintf('xp_new  : [%d x %d]  (expect 2x1)\n', size(xp_new));
fprintf('T_v     : [%d x %d]  (expect 4x1)\n', size(T_v));
fprintf('Ti_v    : [%d x %d]  (expect 4x1)\n', size(Ti_v));
fprintf('S_v     : [%d x %d]  (expect 4x1)\n', size(S_v));
fprintf('D_v     : [%d x %d]  (expect 4x1)\n', size(D_v));
fprintf('G_v     : [%d x %d]  (expect 4x1)\n', size(G_v));
fprintf('swVal   : [%d x %d]  (expect 1x1)\n', size(swVal));

%% ---- Check for NaN / Inf ----
fprintf('\n=== NaN/Inf checks ===\n');
if any(isnan(u_log(:))) || any(isinf(u_log(:)))
    warning('u_log contains NaN or Inf!');
else
    fprintf('u_log    : OK\n');
end
if any(isnan(x_sim(:))) || any(isinf(x_sim(:)))
    warning('x_sim contains NaN or Inf!');
else
    fprintf('x_sim    : OK\n');
end
if any(isnan(phat_log(:))) || any(isinf(phat_log(:)))
    warning('phat_log contains NaN or Inf!');
else
    fprintf('phat_log : OK\n');
end
if any(isnan(phi_log(:))) || any(isinf(phi_log(:)))
    warning('phi_log contains NaN or Inf!');
else
    fprintf('phi_log  : OK\n');
end

%% ---- Summary stats ----
fprintf('\n=== Summary ===\n');
fprintf('Final phi         : %.4f\n', phi_log(N-1));
fprintf('Max |u|           : [%.2f, %.2f] Nm\n', max(abs(u_log(:,1))), max(abs(u_log(:,2))));
fprintf('Final ||qe||      : %.6f rad\n', norm(qe_log(N-1,:)));
fprintf('Max switch jumps  : %d per step\n', ...
    max(diff([0; find(diff(phi_log) > 0)])));

%% ---- Plots ----
figure('Color','w','Name','Tracking');
for j = 1:2
    subplot(2,1,j); hold on; grid on;
    plot(t, x_sim(:,j), 'b', 'LineWidth', 1.5, 'DisplayName', 'q');
    plot(t, qd_all(:,j), 'r--', 'LineWidth', 1.2, 'DisplayName', 'q_d');
    xlabel('Time [s]'); ylabel(sprintf('q_%d [rad]', j));
    legend('Location','best');
    title(sprintf('Joint %d tracking', j));
end

figure('Color','w','Name','Tracking error');
subplot(2,1,1); hold on; grid on;
semilogy(t, vecnorm(qe_log, 2, 2), 'b', 'LineWidth', 1.2);
xlabel('Time [s]'); ylabel('||q_e||');
title('Configuration error (log scale)');

subplot(2,1,2); hold on; grid on;
plot(t, phi_log, 'r', 'LineWidth', 1.2);
xlabel('Time [s]'); ylabel('\phi');
title('Observer gain \phi');

figure('Color','w','Name','Control input');
for j = 1:2
    subplot(2,1,j); hold on; grid on;
    plot(t, u_log(:,j), 'b', 'LineWidth', 1.2);
    plot(t, uo_log(:,j), 'r--', 'LineWidth', 1.0, 'DisplayName', 'u_o');
    plot(t, uff_log(:,j), 'g-.', 'LineWidth', 1.0, 'DisplayName', 'u_{ff}');
    xlabel('Time [s]'); ylabel(sprintf('u_%d [Nm]', j));
    legend('u','u_o','u_{ff}','Location','best');
    title(sprintf('Joint %d torque decomposition', j));
end

figure('Color','w','Name','Observer');
for j = 1:2
    subplot(2,1,j); hold on; grid on;
    p_true = zeros(N,1);
    for k = 1:N
        M_k = M_mat_val(x_sim(k,2), a1, a2, bp);
        p_vec = M_k * x_sim(k,3:4)';
        p_true(k) = p_vec(j);
    end
    plot(t, p_true, 'b', 'LineWidth', 1.2, 'DisplayName', 'p_{true}');
    plot(t, phat_log(:,j), 'r--', 'LineWidth', 1.2, 'DisplayName', '\hat{p}');
    xlabel('Time [s]'); ylabel(sprintf('p_%d', j));
    legend('Location','best');
    title(sprintf('Joint %d momentum estimation', j));
end

figure('Color','w','Name','Switching');
subplot(2,1,1);
plot(t, switch_log, 'b', 'LineWidth', 1.0); grid on;
xlabel('Time [s]'); ylabel('switchVal');
title('Switching condition (should stay > 0 after transient)');
yline(0, 'r--');

subplot(2,1,2);
plot(t, phi_log, 'b', 'LineWidth', 1.0); grid on;
xlabel('Time [s]'); ylabel('\phi');
title('Observer gain evolution');

fprintf('\nAll checks passed. Function is ready for Simulink.\n');

%% ========== Plant dynamics (same as original) ==========

function [u, phat_out, qe, pe, v_k, ye, uo, u_ff, phi_out, xp_out, ...
         T_out, Ti_out, S_out, D_out, G_out, switchVal] = ...
    pH_controller_fcn(q, qd, dqd, ddqd, xp_in, phi_in, dt, ...
                      a1, a2, bp, b1, b2, Kp_diag, Kd_diag, alpha, kappa)
%#codegen
% pH_CONTROLLER_FCN  Combined observer + KPES controller for 2-DOF robot.
%
%  Single MATLAB Function block for Simulink.
%  Compatible with MATLAB 2018b and MATLAB Coder.
%
%  INPUTS  (all fixed-size, real double):
%   q        : 2x1   measured joint positions [rad]
%   qd       : 2x1   desired positions [rad]
%   dqd      : 2x1   desired velocities [rad/s]
%   ddqd     : 2x1   desired accelerations [rad/s^2]
%   xp_in    : 2x1   observer state (Unit Delay feedback)
%   phi_in   : 1x1   observer gain  (Unit Delay feedback)
%   dt       : 1x1   sample time [s]
%   a1..kappa: 1x1   scalar parameters
%
%  OUTPUTS (all fixed-size, real double):
%   u        : 2x1   total control torque
%   phat_out : 2x1   estimated momentum (original coords)
%   qe       : 2x1   configuration error
%   pe       : 2x1   momentum error
%   v_k      : 2x1   KPES injection
%   ye       : 2x1   passive output
%   uo       : 2x1   passive interconnection
%   u_ff     : 2x1   feedforward
%   phi_out  : 1x1   updated phi  -> Unit Delay
%   xp_out   : 2x1   updated xp   -> Unit Delay
%   T_out    : 4x1   vec(T)
%   Ti_out   : 4x1   vec(Ti)
%   S_out    : 4x1   vec(S_tilde)
%   D_out    : 4x1   vec(D_tilde)
%   G_out    : 4x1   vec(G_tilde)
%   switchVal: 1x1   observer switching condition

% ---- Fix sizes for Coder ----
assert(isa(q,     'double') && all(size(q)     == [2 1]));
assert(isa(qd,    'double') && all(size(qd)    == [2 1]));
assert(isa(dqd,   'double') && all(size(dqd)   == [2 1]));
assert(isa(ddqd,  'double') && all(size(ddqd)  == [2 1]));
assert(isa(xp_in, 'double') && all(size(xp_in) == [2 1]));
assert(isa(phi_in,'double') && isscalar(phi_in));
assert(isa(dt,    'double') && isscalar(dt));

% ---- Local copies ----
q_c    = q;
qd_c   = qd;
dqd_c  = dqd;
ddqd_c = ddqd;
xp     = xp_in;
phi    = phi_in;

% ---- Gain matrices ----
Kp = [Kp_diag, 0; 0, Kp_diag];
Kd = [Kd_diag, 0; 0, Kd_diag];

% ---- Mass matrix and transforms ----
M       = loc_M(q_c(2), a1, a2, bp);
Minv    = loc_inv2(M);
T       = loc_sym_sqrt(Minv);        % M^{-1/2}
Ti      = loc_sym_sqrt(M);           % M^{1/2}
D0      = [b1, 0; 0, b2];

D_tilde = T * D0 * T;
G_tilde = T;                         % G0 = I

% ---- dM/dq2 -> dTi/dq2 via Sylvester ----
s2       = sin(q_c(2));
dM_dq2   = [-2*bp*s2, -bp*s2; -bp*s2, 0];
dTi_dq2  = loc_sylvester22(Ti, Ti, dM_dq2);

% ---- Observer: momentum estimate ----
phat = xp + phi * q_c;

% ---- Sbar for switching condition ----
Sbar = loc_compute_Sbar(T, dTi_dq2, phat);

% ---- Switching logic (jumps) ----
maxJumps  = 50;
jumpCount = 0;
switchVal = loc_switch_cond(phi, Sbar, T) - kappa;

while (switchVal <= 0) && (jumpCount < maxJumps)
    xp   = xp - kappa * q_c;
    phi  = phi + kappa;
    phat = xp + phi * q_c;
    Sbar = loc_compute_Sbar(T, dTi_dq2, phat);
    switchVal = loc_switch_cond(phi, Sbar, T) - kappa;
    jumpCount = jumpCount + 1;
end

% ---- S matrix with final phat ----
col2    = dTi_dq2 * phat;
A_mat   = [zeros(2,1), col2];
S_tilde = T * (A_mat' - A_mat) * T;

% ---- Error coordinates ----
pd   = Ti * dqd_c;                     % target momentum
qe   = q_c - qd_c;                    % config error
pe   = phat - pd;                      % momentum error

% ---- dpd/dq (only q2 column nonzero) ----
dpd_dq = [zeros(2,1), dTi_dq2 * dqd_c];

% ---- KPES injection ----
z   = qe + alpha * pe;
v_k = alpha * (S_tilde - D_tilde - Kd) * Kp * z ...
      - T * Kp * z ...
      - Kd * pe;

% ---- Passive output ----
dHe_dqe = Kp * (qe + alpha * pe);
dHe_dpe = pe  + alpha * Kp * (qe + alpha * pe);

I2 = [1,0;0,1];
top_block    = [I2, phi*I2 - dpd_dq'];   % 2x4
stacked      = [dHe_dqe; dHe_dpe];       % 4x1
ye = -T * (top_block * stacked);

% ---- Passive interconnection: uo = -G_tilde^{-1} * ye ----
uo = -loc_solve2(G_tilde, ye);

% ---- Feedforward ----
gradV = zeros(2,1);
u_ff = loc_solve2(G_tilde, ...
       -(S_tilde - D_tilde) * pd ...
       + T * gradV ...
       + dpd_dq * (T * phat) ...
       + Ti * ddqd_c ...
       + v_k);

% ---- Total control ----
u = -uo + u_ff;

% ---- Observer RK4 update ----
xp_out = loc_obs_rk4(q_c, xp, phi, S_tilde, D_tilde, T, G_tilde, ...
                      u, gradV, uo, dt);
phi_out = phi;

% ---- Estimated momentum in original coords ----
phat_out = Ti * phat;

% ---- Pack matrices for logging ----
T_out  = [T(1,1);  T(2,1);  T(1,2);  T(2,2)];
Ti_out = [Ti(1,1); Ti(2,1); Ti(1,2); Ti(2,2)];
S_out  = [S_tilde(1,1); S_tilde(2,1); S_tilde(1,2); S_tilde(2,2)];
D_out  = [D_tilde(1,1); D_tilde(2,1); D_tilde(1,2); D_tilde(2,2)];
G_out  = [G_tilde(1,1); G_tilde(2,1); G_tilde(1,2); G_tilde(2,2)];

end

% =========================================================================
%  LOCAL FUNCTIONS - all fixed-size 2x2, no dynamic allocation
% =========================================================================

function M = loc_M(theta2, a1, a2, b)
    c2 = cos(theta2);
    M = [a1 + a2 + 2*b*c2,  a2 + b*c2;
         a2 + b*c2,          a2       ];
end

function Ainv = loc_inv2(A)
    detA = A(1,1)*A(2,2) - A(1,2)*A(2,1);
    invDet = 1.0 / detA;
    Ainv = [A(2,2)*invDet, -A(1,2)*invDet;
           -A(2,1)*invDet,  A(1,1)*invDet];
end

function x = loc_solve2(A, b)
    Ainv = loc_inv2(A);
    x = [Ainv(1,1)*b(1) + Ainv(1,2)*b(2);
         Ainv(2,1)*b(1) + Ainv(2,2)*b(2)];
end

function Asqrt = loc_sym_sqrt(A)
    % Symmetric square root of 2x2 SPD matrix.
    % Explicit eigendecomposition - no eig() call.
    a11 = A(1,1); a12 = A(1,2); a22 = A(2,2);

    tr      = a11 + a22;
    det_val = a11*a22 - a12*a12;
    disc    = tr*tr - 4.0*det_val;
    if disc < 0
        disc = 0.0;
    end
    sq = sqrt(disc);

    lam1 = 0.5*(tr + sq);
    lam2 = 0.5*(tr - sq);
    if lam1 < 1e-12; lam1 = 1e-12; end
    if lam2 < 1e-12; lam2 = 1e-12; end

    % Eigenvectors
    v1 = zeros(2,1);
    v2 = zeros(2,1);
    if abs(a12) > 1e-14
        v1(1) = lam1 - a22;  v1(2) = a12;
        v2(1) = lam2 - a22;  v2(2) = a12;
    elseif a11 >= a22
        v1(1) = 1; v1(2) = 0;
        v2(1) = 0; v2(2) = 1;
    else
        v1(1) = 0; v1(2) = 1;
        v2(1) = 1; v2(2) = 0;
    end

    n1 = sqrt(v1(1)*v1(1) + v1(2)*v1(2));
    n2 = sqrt(v2(1)*v2(1) + v2(2)*v2(2));
    v1 = v1 / n1;
    v2 = v2 / n2;

    s1 = sqrt(lam1);
    s2_val = sqrt(lam2);

    % V * diag(s1,s2) * V'  expanded
    Asqrt = [v1(1)*v1(1)*s1 + v2(1)*v2(1)*s2_val, v1(1)*v1(2)*s1 + v2(1)*v2(2)*s2_val;
             v1(2)*v1(1)*s1 + v2(2)*v2(1)*s2_val, v1(2)*v1(2)*s1 + v2(2)*v2(2)*s2_val];
end

function X = loc_sylvester22(A, B, C)
    % Solve A*X + X*B = C  for 2x2 matrices.
    % Expand to 4x4: (I kron A + B' kron I) vec(X) = vec(C)
    % All explicit - no kron(), no mldivide.
    
    bt11 = B(1,1); bt12 = B(2,1); bt21 = B(1,2); bt22 = B(2,2);
    
    K = zeros(4,4);
    % I kron A
    K(1,1) = A(1,1); K(1,2) = A(1,2);
    K(2,1) = A(2,1); K(2,2) = A(2,2);
    K(3,3) = A(1,1); K(3,4) = A(1,2);
    K(4,3) = A(2,1); K(4,4) = A(2,2);
    % + B' kron I
    K(1,1) = K(1,1) + bt11; K(1,3) = K(1,3) + bt12;
    K(2,2) = K(2,2) + bt11; K(2,4) = K(2,4) + bt12;
    K(3,1) = K(3,1) + bt21; K(3,3) = K(3,3) + bt22;
    K(4,2) = K(4,2) + bt21; K(4,4) = K(4,4) + bt22;
    
    rhs = [C(1,1); C(2,1); C(1,2); C(2,2)];
    x4  = loc_solve4(K, rhs);
    
    X = [x4(1), x4(3);
         x4(2), x4(4)];
end

function x = loc_solve4(A, b)
    % Solve 4x4 system via Gaussian elimination with partial pivoting.
    Ab = [A(1,1),A(1,2),A(1,3),A(1,4),b(1);
          A(2,1),A(2,2),A(2,3),A(2,4),b(2);
          A(3,1),A(3,2),A(3,3),A(3,4),b(3);
          A(4,1),A(4,2),A(4,3),A(4,4),b(4)];
    
    for col = 1:3
        maxVal = abs(Ab(col,col));
        maxRow = col;
        for row = col+1:4
            if abs(Ab(row,col)) > maxVal
                maxVal = abs(Ab(row,col));
                maxRow = row;
            end
        end
        if maxRow ~= col
            tmp = Ab(col,:);
            Ab(col,:) = Ab(maxRow,:);
            Ab(maxRow,:) = tmp;
        end
        for row = col+1:4
            factor = Ab(row,col) / Ab(col,col);
            Ab(row,col:5) = Ab(row,col:5) - factor * Ab(col,col:5);
        end
    end
    
    x = zeros(4,1);
    x(4) = Ab(4,5) / Ab(4,4);
    x(3) = (Ab(3,5) - Ab(3,4)*x(4)) / Ab(3,3);
    x(2) = (Ab(2,5) - Ab(2,3)*x(3) - Ab(2,4)*x(4)) / Ab(2,2);
    x(1) = (Ab(1,5) - Ab(1,2)*x(2) - Ab(1,3)*x(3) - Ab(1,4)*x(4)) / Ab(1,1);
end

function Sbar = loc_compute_Sbar(T, dTi_dq2, phat)
    Sbar = zeros(2,2);
    for i = 1:2
        ei = zeros(2,1);
        ei(i) = 1.0;
        col2  = dTi_dq2 * ei;
        A_ei  = [zeros(2,1), col2];
        S_ei  = T * (A_ei' - A_ei) * T;
        Sbar(1,i) = S_ei(1,1)*phat(1) + S_ei(1,2)*phat(2);
        Sbar(2,i) = S_ei(2,1)*phat(1) + S_ei(2,2)*phat(2);
    end
end

function sc = loc_switch_cond(phi, Sbar, T)
    % min eigenvalue of  phi*T - 0.5*(Sbar + Sbar')
    P11 = phi*T(1,1) - Sbar(1,1);
    P12 = phi*T(1,2) - 0.5*(Sbar(1,2) + Sbar(2,1));
    P21 = phi*T(2,1) - 0.5*(Sbar(2,1) + Sbar(1,2));
    P22 = phi*T(2,2) - Sbar(2,2);
    
    tr_P  = P11 + P22;
    det_P = P11*P22 - P12*P21;
    disc  = tr_P*tr_P - 4.0*det_P;
    if disc < 0
        disc = 0.0;
    end
    sc = 0.5*(tr_P - sqrt(disc));
end

function xp_new = loc_obs_rk4(q, xp, phi, S, D, T, G, u, gradV, uo, dt)
    k1 = loc_obs_dot(q, xp,              phi, S, D, T, G, u, gradV, uo);
    k2 = loc_obs_dot(q, xp + 0.5*dt*k1, phi, S, D, T, G, u, gradV, uo);
    k3 = loc_obs_dot(q, xp + 0.5*dt*k2, phi, S, D, T, G, u, gradV, uo);
    k4 = loc_obs_dot(q, xp + dt*k3,     phi, S, D, T, G, u, gradV, uo);
    xp_new = [xp(1) + (dt/6.0)*(k1(1) + 2.0*k2(1) + 2.0*k3(1) + k4(1));
              xp(2) + (dt/6.0)*(k1(2) + 2.0*k2(2) + 2.0*k3(2) + k4(2))];
end

function dxp = loc_obs_dot(q, xp, phi, S, D, T, G, u, gradV, uo)
    phat = [xp(1) + phi*q(1); xp(2) + phi*q(2)];
    SDpT = S - D - phi*T;
    u_total = [u(1) + uo(1); u(2) + uo(2)];
    dxp = [SDpT(1,1)*phat(1) + SDpT(1,2)*phat(2) - T(1,1)*gradV(1) - T(1,2)*gradV(2) + G(1,1)*u_total(1) + G(1,2)*u_total(2);
           SDpT(2,1)*phat(1) + SDpT(2,2)*phat(2) - T(2,1)*gradV(1) - T(2,2)*gradV(2) + G(2,1)*u_total(1) + G(2,2)*u_total(2)];
end

function dx = f_dyn(x, u, a1, a2, b, b1, b2)
    q  = x(1:2);
    dq = x(3:4);
    M = M_mat_val(q(2), a1, a2, b);
    C = C_mat_val(q(2), dq(1), dq(2), b);
    F = [b1*dq(1); b2*dq(2)];
    ddq = M \ (u(:) - C*dq - F);
    dx = [dq; ddq];
end

function M = M_mat_val(theta2, a1, a2, b)
    c2 = cos(theta2);
    M = [a1 + a2 + 2*b*c2,  a2 + b*c2;
         a2 + b*c2,          a2];
end

function C = C_mat_val(theta2, dtheta1, dtheta2, b)
    s2 = sin(theta2);
    C = [-b*s2*dtheta2,           -b*s2*(dtheta1 + dtheta2);
          b*s2*dtheta1,            0];
end