%% Combined Teensy + Quanser logging
clear; clc;

%% ---- Setup ----
% Teensy serial
s = serial("COM5", 'BaudRate',115200); % replace with your Teensy COM port

% Quanser Q8-USB
io = q8('q8_usb');  % adjust if using a different board

% Analog output channel 1 (motor voltage)
ao_chan = 1;

% Analog input channel 3 (motor current)
ai_chan = 3;

% Logging
Tlog = 5; % seconds
dt = 0.001; % 1 kHz loop
data = []; % [timestamp_us, motor voltage, motor current, torque voltage]

%% ---- Main loop ----
tic;
t_next = tic; % use tic for rough timing
step = 0;
while toc < Tlog
    step = step + 1;
    
    % ---- Motor control signal ----
    t_sec = toc;
    motor_voltage = 2*sin(2*pi*0.5*t_sec); % example waveform ±2 V
    writeAnalog(io, ao_chan, motor_voltage);
    
    % ---- Motor current measurement ----
    motor_current = readAnalog(io, ai_chan); % in volts
    
    % ---- Read Teensy torque if available ----
    torque_voltage = NaN;
    timestamp_us  = NaN;
    if s.NumBytesAvailable >= 8
        pkt = read(s, 8, "uint8");
        torque_voltage = typecast(pkt(1:4), 'single');
        timestamp_us   = typecast(pkt(5:8), 'uint32');
    end
    
    % ---- Save data ----
    data = [data; double(timestamp_us), motor_voltage, motor_current, double(torque_voltage)];
    
    % ---- Wait until next timestep ----
    pause(dt); % approximate 1 kHz
end

%% ---- Cleanup ----
clear s;
writeAnalog(io, ao_chan, 0); % stop motor
close(io);

%% ---- Save ----
csvwrite('experiment_data.csv', data);
save('experiment_data.mat', 'data');
