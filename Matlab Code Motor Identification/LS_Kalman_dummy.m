load('motor1VoltageData_1hz')
time     = motorData.time;
voltage  = motorData.voltage(:);
current  = motorData.current(:);
velocity = motorData.velocity(:);
Ts = time(2) - time(1);

% ----- Fixed motor parameters (your originals) -----
La = 0.0544;     % [H]
Ra = 3.4239;     % [Ohm]
ke = 0.0097;     % [V·s/rad] (back-EMF constant)

% ----- Initial state and covariance (only [i; omega]) -----
x0 = [current(1); velocity(1)];
P0 = diag([0.01, 1]);         % tune as you like

% ----- Noise settings -----
Qx = (0.003)^2;               % process noise on current dynamics
Qw = (1.0)^2;                 % omega random-walk noise
Ri = (0.057)^2;               % current sensor noise
Rw = 4;                       % omega sensor noise

out = ekf_fixedparams(voltage, current, velocity, Ts, x0, P0, ...
                      La, Ra, ke, Qx, Qw, Ri, Rw);

% Reconstruct voltage using fixed parameters
V_rec = La * out.di_dt_hat + Ra*out.i_hat + ke*out.w_hat;

% ---- Compute MSE for reconstructed training dataset ----
mse_train = mean((voltage - V_rec).^2);
fprintf('MSE (Reconstructed dataset, 1 Hz): %.6f\n', mse_train);

figure(1)
subplot(4,1,1)
plot(time, voltage, 'k:', time, V_rec, 'r')
legend('v_{in}','v_{reconstructed}')
xlabel('Time [s]'); ylabel('Voltage [V]')

subplot(4,1,2)
plot(time, current, 'k:', time, out.i_hat, 'r');
xlabel('Time [s]'); ylabel('Current [A]');
legend('Measured','EKF filtered');

subplot(4,1,3)
plot(time, velocity, 'k:', time, out.w_hat, 'b');
xlabel('Time [s]'); ylabel('Speed [rad/s]');
legend('Measured','EKF filtered');

subplot(4,1,4)
plot(time, out.di_dt_hat)
legend('dI_a/dt (model)')
xlabel('Time [s]'); ylabel('dI_a/dt [A/s]');


% ======================== FUNCTION ========================
function out = ekf_fixedparams(Vin, i_meas, w_meas, Ts, x0, P0, ...
                               La, Ra, ke, Qx, Qw, Ri, Rw)
% EKF for DC motor with FIXED (La, Ra, ke). States: X = [ i ; omega ].
%
% Model:
%   i_{k+1}   = i_k + Ts/La * ( -Ra*i_k - ke*omega_k + Vin_k )
%   omega_{k+1} = omega_k + w_omega      (random walk)
%
% Measurement:
%   y = [ i_meas ; w_meas ] = [ i ; omega ] + v
%
% Extras:
%   di_dt_hat(k) = ( -Ra*i_hat - ke*w_hat + Vin ) / La     (model-based)
%   v_rec(k)     = La*di_dt_hat + Ra*i_hat + ke*w_hat

N  = numel(Vin);
nx = 2;

x = x0(:);
P = P0;

Q = diag([Qx, Qw]);
H = eye(2);
R = diag([Ri, Rw]);

Xhist   = zeros(nx, N);
Phist   = zeros(nx, nx, N);
di_dt   = zeros(N,1);
v_recon = zeros(N,1);

for k = 1:N
    % -------- Prediction --------
    i = x(1);  w = x(2);
    u = Vin(k);

    % State prediction
    fi      = i + Ts/La * ( -Ra*i - ke*w + u );
    fw      = w; % random walk
    x_pred  = [fi; fw];

    % Jacobian A = ∂f/∂x
    dfi_di  = 1 + Ts*(-Ra)/La;
    dfi_dw  = Ts*(-ke)/La;
    A = [ dfi_di, dfi_dw;
          0,      1      ];

    P_pred = A*P*A' + Q;

    % -------- Update --------
    y      = [i_meas(k); w_meas(k)];
    y_pred = H*x_pred;
    S      = H*P_pred*H' + R;
    K      = (P_pred*H')/S;

    x = x_pred + K*(y - y_pred);
    P = (eye(nx) - K*H)*P_pred;

    % store state/cov
    Xhist(:,k)   = x;
    Phist(:,:,k) = P;

    % -------- Reconstruct di/dt and Vin (after update) --------
    if k == 1
        di_dt(k) = 0;             % or copy next sample after the loop
    else
        di_dt(k) = (Xhist(1,k) - Xhist(1,k-1)) / Ts;   % uses i_hat only to compute derivative
    end
end

out.x         = Xhist;
out.P         = Phist;
out.i_hat     = Xhist(1,:).';
out.w_hat     = Xhist(2,:).';
out.di_dt_hat = di_dt;
end
