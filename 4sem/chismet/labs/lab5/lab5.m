clc, clear
fprintf('Laboratornaya rabota 5. Integrirovanie funkcij. Formuly trapecij, Simpsona\n')
fprintf('----------Zadanie 1.----------\n')
format long;

f = @(t)t.^3;

fprintf('\nМетод трапеции для y = x^3:');
metod_trapecij(f, 0, 1, 10)
% delta_max_theoretic = (M2 * h^2 * (b-a))/12
% M2 = 6
h = (1 - 0) / 10;
delta_max_theoretic = (6 * h^2 * (1-0))/12
delta_real = abs(1/4 - metod_trapecij(f, 0, 1, 10))

fprintf('\nМетод Симпсона для y = x^3:');
metod_simpsona(f, 0, 1, 10)
% delta_max_theoretic = (M4 * h^4 * (b-a))/2880
% M4 = 0
delta_max_theoretic = 0
delta_real = abs(1/4 - metod_simpsona(f, 0, 1, 10))

f = @(t)t.^2;

fprintf('\nМетод трапеции для y = x^2:');
metod_trapecij(f, 0, 1, 10)
% delta_max_theoretic = (M2 * h^2 * (b-a))/12
% M2 = 2
h = (1 - 0) / 10;
delta_max_theoretic = (2 * h^2 * (1-0))/12
delta_real = abs(1/3 - metod_trapecij(f, 0, 1, 10))

fprintf('\nМетод Симпсона для y = x^2:');
metod_simpsona(f, 0, 1, 10)
% delta_max_theoretic = (M4 * h^4 * (b-a))/2880
% M4 = 0
delta_max_theoretic = 0
delta_real = abs(1/3 - metod_simpsona(f, 0, 1, 10))

f = @(t)t./2;

fprintf('\nМетод трапеции для y = x/2:');
metod_trapecij(f, 0, 1, 10)
% delta_max_theoretic = (M2 * h^2 * (b-a))/12
% M2 = 0
h = (1 - 0) / 10;
delta_max_theoretic = 0
delta_real = abs(1/4 - metod_trapecij(f, 0, 1, 10))

fprintf('\nМетод Симпсона для y = x/2:');
metod_simpsona(f, 0, 1, 10)
% delta_max_theoretic = (M4 * h^4 * (b-a))/2880
% M4 = 0
delta_max_theoretic = 0
delta_real = abs(1/4 - metod_simpsona(f, 0, 1, 10))

fprintf('----------Zadanie 2.----------\n')
f = @(t)4./(1+t.^2);

% 10^-6 = (M2 * h^2 * (b-a))/12
% M2 = 2
% h = 0.00244949
% n = (b-a)/h = 409
fprintf('\nЧисло пи методом трапеции:');
metod_trapecij(f, 0, 1, 409)

% 10^-6 = (M4 * h^4 * (b-a))/2880
% M4 = 96
% h = 0.0740083
% n = (b-a)/h = 14
fprintf('\nЧисло пи методом Симпсона:');
metod_simpsona(f, 0, 1, 14)

fprintf('----------Zadanie 3.----------\n')
f = @(t)4./(1+t.^2);
eps = 10^-6;

n = 5;
h = (1-0)/n;

x_start = 0;
x_end = x_start + h;

integral = 0;
for i = 1:n
    integral = integral + runge(f, x_start, x_end, eps/n);
    x_start = x_end;
    x_end = x_end + h;
end

integral
delta_real = integral-pi
