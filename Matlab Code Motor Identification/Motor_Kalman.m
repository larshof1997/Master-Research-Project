load('motor1VoltageData_1hz')
time     = motorData.time;
voltage  = motorData.voltage(:);
current  = motorData.current(:);
velocity = motorData.velocity(:);
Ts = time(2) - time(1);

La = 0.0544;     % [H]
Ra = 3.4239;     % [Ohm]
ke = 0.0097;     % [V·s/rad]

x0 = [current(1); velocity(1)];
P0 = diag([0.01, 1]);

Qx = (0.003)^2;
Qw = (1.0)^2;
Ri = (0.057)^2;
Rw = 4;

out = kalman_fixedparams(voltage, current, velocity, Ts, x0, P0, ...
                         La, Ra, ke, Qx, Qw, Ri, Rw);

%% 
V_rec = -La * out.di_dt_hat + Ra*out.i_hat + ke*out.w_hat;
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
legend('Measured','KF filtered');

subplot(4,1,3)
plot(time, velocity, 'k:', time, out.w_hat, 'b');
xlabel('Time [s]'); ylabel('Speed [rad/s]');
legend('Measured','KF filtered');

subplot(4,1,4)
plot(time, out.di_dt_hat)
legend('dI_a/dt (model)')
xlabel('Time [s]'); ylabel('dI_a/dt [A/s]');



function out = kalman_fixedparams(Vin, i_meas, w_meas, Ts, x0, P0, ...
                                  La, Ra, ke, Qx, Qw, Ri, Rw)

N  = numel(Vin);
nx = 2;

A = [1 - Ts*Ra/La, -Ts*ke/La;
     0,           1      ];
B = [Ts/La; 0];
H = eye(2);

Q = diag([Qx, Qw]);
R = diag([Ri, Rw]);

x = x0(:);
P = P0;
Xhist   = zeros(nx, N);
Phist   = zeros(nx, nx, N);
di_dt   = zeros(N,1);

for k = 1:N
    x_pred = A*x + B*Vin(k);
    P_pred = A*P*A' + Q;

    y = [i_meas(k); w_meas(k)];
    K = P_pred*H'/(H*P_pred*H' + R);
    x = x_pred + K*(y - H*x_pred);
    P = (eye(nx) - K*H)*P_pred;

    Xhist(:,k)   = x;
    Phist(:,:,k) = P;

    di_dt(k) = (-Ra*x(1) - ke*x(2) + Vin(k))/La;
end

out.x         = Xhist;
out.P         = Phist;
out.i_hat     = Xhist(1,:).';
out.w_hat     = Xhist(2,:).';
out.di_dt_hat = di_dt;
end
