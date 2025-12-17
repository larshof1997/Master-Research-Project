% Adjust COM port to match your Teensy
port = 'COM5';
baud = 921600;

% Create serial object
s = serial(port, 'BaudRate', baud);
fopen(s);

% Open CSV for logging
timestamp = datetime('now','Format','yyyyMMdd_HHmmss');
filename = sprintf('teensy_analog_data_%s.csv', timestamp);

fid = fopen(filename, 'w');
fprintf(fid, 'time_s,analog_value\n');

disp('Logging started. Press Ctrl+C to stop.');
startTime = tic;

while true
    if s.BytesAvailable > 0
        line = fgetl(s);          % read one line
        value = str2double(line); % convert ASCII to number
        if ~isnan(value)
            t = toc(startTime);
            fprintf(fid, '%.6f,%d\n', t, value);
            fprintf('%.6f s: %d\n', t, value);
        end
    end
end

% Clean up (after stopping loop)
fclose(fid);
fclose(s);
delete(s);
clear s;
fclose(fid);
