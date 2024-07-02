clc, clear
fprintf('Laboratornaya rabota 4. Differencirovanie funkcii, zadannoj tablichno.\n')
fprintf('----------Zadanie 1.----------\n')

f = @(t)sin(4*pi*t);
ksi = 1.3;

% eps <= M2 * h/2
% M1 = 4pi
% M2 = 16pi^2

% 10^-3 <= 16pi^2 * h/2 
h = 1.27 * 10^-5;
dx_1 = (f(ksi + h) - f(ksi))/h

% 10^-6 <= h/2 ? h = 1.27 * 10^-8
h = 1.27 * 10^-8;
dx_2 = (f(ksi + h) - f(ksi))/h

dx_real = 4*pi*cos(4*pi*1.3)

fprintf('----------Zadanie 2.----------\n')
right_dx = @(t, h) (f(ksi+h)-f(ksi))/h;
central_dx = @(t, h) (f(ksi+h)-f(ksi-h))/(2*h);


h= 1/4
delta_right = right_dx(ksi, h) - dx_real
delta_central = central_dx(ksi, h) - dx_real

h = 1/8
delta_right = right_dx(ksi, h) - dx_real
delta_central = central_dx(ksi, h) - dx_real

h = 1/16
delta_right = right_dx(ksi, h) - dx_real
delta_central = central_dx(ksi, h) - dx_real

h = 1/32
delta_right = right_dx(ksi, h) - dx_real
delta_central = central_dx(ksi, h) - dx_real


fprintf('----------Zadanie 3.----------\n')

for i = 1:60
    h = 1/2^i;
    delta_central = central_dx(ksi, h) - dx_real
end
