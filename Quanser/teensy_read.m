delete(instrfindall);  % Clears any lingering/stuck serial objects
clear s;
% Adjust COM port to match your Teensy
port = 'COM5';
baud = 115200;  % match Teensy baud

s = serial('COM5', 'BaudRate', 115200);
pause(1.5);  % Short delay for Teensy USB to settle (1-2 seconds is plenty without the wait loop)
fopen(s);  % Or configure/fclear if using serialport

% Open CSV for logging
timestamp = datetime('now','Format','yyyyMMdd_HHmmss');
filename = sprintf('teensy_analog_data_%s.csv', timestamp);
fid = fopen(filename, 'w');
% fprintf(fid, 'index,analog_value\n');  % just sequential index

disp('Waiting for experiment data... Press Ctrl+C to stop.');

index = 1;
timeout = 1.0;                 % seconds to wait after last reading
lastTime = tic;                 % timer for last received data
empty = false;


while true
    % Read all available lines
    while s.BytesAvailable > 0
        line = fgetl(s);
        if ischar(line) && ~isempty(line)
            value = str2double(line);
            if ~isnan(value)
                fprintf(fid, '%d,%d\n', index, value); % save to CSV
                index = index + 1;
                lastTime = tic;  % reset timeout
            end
        end
    end
    % Stop if timeout exceeded
    if toc(lastTime) > timeout && index > 1
        break;
    end
end

disp('Finished receiving data.');



% Clean up (after stopping loop)
fclose(fid);
fclose(s);
delete(s);
clear s;
