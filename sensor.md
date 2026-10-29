clear s
freeports = serialportlist("available") % Shows available serial ports
%
%Choose which port to use for Arduino (proabably best to hardcode)
%
ports = "COM4";%freeports(2)
baudrate = 9600;
s = serialport(ports,baudrate);
pause(2);
% Set up the figure once before starting the loop
figure;
axis equal;
xlabel('X Distance (cm)');
ylabel('Y Distance (cm)');
title('2D Scan Map');
hold on; % Keeps existing points on the plot when new plot() commands run
distance1 = [];
X = [];
Y = [];
%initialize a timeout in case MATLAB cannot connect to the arduino
timeout = 0;
fprintf('start')
% main loop to read data from the Arduino, then display it%
while timeout < 5 % % check if data was received %
while s.NumBytesAvailable > 0
%
% reset timeout
%
timeout = 0;
%
% data was received, convert it into array of integers
%

numlist = readline(s)
values = eval(strcat('[',numlist,']'));

%
% if you want to store the integers in four variables
%
a = values(1);
b = values(2);
c = values(3);
d = values(4);
%
% fprintf the results
%
if (b >= 0)
        %
        % fprintf the valid results
        %
        fprintf('a,b,c,d = %d,%.1f,%.1f,%.1f\n', a, b, c, d);
        distance1(end+1) = b
        X(end+1) = c
        Y(end+1) = d

        % % Plot full trace line connecting points sequentially
        plot(X, Y, 'bo', 'LineWidth', 1.5, 'MarkerFaceColor', 'r', 'MarkerSize', 4);
        drawnow;
end
%
end
pause(0.5);
timeout = timeout + 1;
end

