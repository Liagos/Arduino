s = serial('/dev/tty.usbmodem641','Baudrate',9600); %set port and transfer rate
fopen(s); %open port command
pause(3) %3 second pause
 
temperatures=[]; %create a table for temperatures measurements
alcohol=[]; %create a table for alcohol measurements
flex=[]; %create a table for pressure measurements
light=[]; %create a table for light sensor measurements

tstart = 0; %set start time
tend = 10000000; %set end time
step = 1000;%set step%
time = tstart:step:tend; %set how the time is running

t = tstart; %start command



while (t <= tend) %loop command while the condition is true
fprintf(s,'%s/n','1'); %place data in text document
    
line = fgets(s); %reads line from file

remain = line; %set to remain the variable line
[token,remain] = strtok(remain,'/'); %with strtok s specific part of the flow is selected
temperatures = [temperatures; str2double(token)]; %set our measurements to the temperatures table
subplot(2,2,1) %creates axes at 2,2,1\\
plot(temperatures);%plot command
grid; %place grid
xlabel('Time') %X axes label
ylabel('Temperature')%Y axes label
title('Temperature Sensor') %title

[token,remain] = strtok(remain,'/'); %with strtok a specific part of the flow is selected
alcohol = [alcohol; str2double(token)]; %set our measurements to alcohol table
subplot(2,2,2) %create axes at 2,2,2
plot(alcohol); %plot command
grid; %place grid
xlabel('Time') %X axes label
ylabel('Alcohol') %Y axes label
title('Alcohol Sensor') %title

[token,remain] = strtok(remain,'/'); %with strtok s specific part of the flow is selected
flex = [flex; str2double(token)]; %set our measurements to flex table
subplot(2,2,3) %create axes at 2,2,3
plot(flex); %plot command
grid; %place grid
xlabel('Time') %X axes label
ylabel('Pressure(Kgs)') %Y axes label
title('Flex Sensor') %title
 
[token,remain] = strtok(remain,'/'); %with strtok s specific part of the flow is selected
light = [light; str2double(token)]; %set our measurements to light table
subplot(2,2,4) %create axes at 2,2,4
plot(light); %plot command
grid; %place grid
xlabel('Time') %X axes label
ylabel('LUX') %Y axes label
title('LDR Sensor') %title


t = t + step; %set a counter for the step
drawnow %refresh layouts

end %end of loop


%%

fprintf(s,'%s/n','0');%place data in text document
fclose(s); %close port command
delete (s); %delete port command
clear s; %clears variable s