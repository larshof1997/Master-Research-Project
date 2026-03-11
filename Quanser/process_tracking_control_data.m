%% process_and_save.m
dt       = 0.001;
t_remove = 2.0;

data = simout;   
% assert(size(data, 2) == 14, 'Expected 14 columns, got %d', size(data, 2));

% Trim initial transient
n_remove = round(t_remove / dt);
data     = data(n_remove+1:end, :);
N        = size(data, 1);
t        = (0:N-1)' * dt;

% % Extract signals
% phat      = data(:,  1:2);
% uo        = data(:,  3:4);
% u_ff      = data(:,  5:6);
% u_d       = data(:,  7:8);
% u_pert    = data(:,  9:10);
% q_desired = data(:, 11:12);
% q_meas    = data(:, 13:14);
% u_total   = uo + u_ff + u_d + u_pert;
% e_track   = q_desired - q_meas;

% Extract signals other controllers
q_meas      = data(:,  1:2);
q_desired   = data(:,  3:4);
u_total     = data(:,  5:6);
e_track     = q_desired - q_meas;

fname = sprintf('RasconIET_control');
save(fname, ...
     't','dt','q_desired','q_meas','u_total','e_track');

fprintf('Saved %s (%d samples, %.2f s)\n', fname, N, N*dt);

