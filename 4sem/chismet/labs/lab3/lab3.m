clc, clear
fprintf('Laboratornaya rabota 3. Interpolyaciya funkcij. Polinomy Lagranzha, Nyutona.\n')
fprintf('----------Zadanie 1.----------\n')

i=0:1:4;
t = i/6;
f = @(t)sin(pi*t);

hold on; grid on;
xlabel('x'); ylabel('y');
% исходная функция
x_all = linspace(t(1), 1);
plot(x_all, sin(pi*x_all), 'r')

% разбиение для узлов интерполяции
h = i/5;
% функции для линейной интерполяции между точками
[f1, f1_plt]  = linear_interpolation(f, h(1), h(2));
[f2, f2_plt] = linear_interpolation(f, h(2), h(3));
[f3, f3_plt] = linear_interpolation(f, h(3), h(4));
[f4, f4_plt] = linear_interpolation(f, h(4), h(5));
[f5, f5_plt] = linear_interpolation(f, h(5), 1);

% построение функций
plot(linspace(h(1), h(2)), f1_plt)
plot(linspace(h(2), h(3)), f2_plt)
plot(linspace(h(3), h(4)), f3_plt)
plot(linspace(h(4), h(5)), f4_plt)
plot(linspace(h(5), 1), f5_plt)

% точки t_i (точки для проверки погрешности)
plot(t(1), f(t(1)), 'r*')
plot(t(2), f(t(2)), 'r*')
plot(t(3), f(t(3)), 'r*')
plot(t(4), f(t(4)), 'r*')
plot(t(5), f(t(5)), 'r*')

% точки h_i (узлы интерполяции)
plot(h(1), f(h(1)), 'o')
plot(h(2), f(h(2)), 'o')
plot(h(3), f(h(3)), 'o')
plot(h(4), f(h(4)), 'o')
plot(h(5), f(h(5)), 'o')

% сравнение интерполяции с функцией в точках t_i
t
func = [f(t(1)), f(t(2)), f(t(3)), f(t(4)), f(t(5))]
interpolation = [f1(t(1)), f2(t(2)), f3(t(3)), f4(t(4)), f5(t(5))]
delta = interpolation - func

fprintf('----------Zadanie 2.----------\n')
% коэффициенты полинома Лагранжа по узлам h
lagrange_polynomial = lagrange_poly(h, f(h))
% формирование функции полинома по коэффициентам
poly_function = @(x) polyval(lagrange_polynomial, x);
% построение графика полинома
plot(x_all, arrayfun(poly_function, x_all), 'g', 'LineStyle', '-.');

% сравнение значения функции и полинома Лагранжа
func
poly_function(t)
delta = (poly_function(t) - func)

% максимальная погрешность в точке
rn = @(x) (pi^5)./(factorial(5)) .* abs (x.*(x-1/5).*(x-2/5).*(x-3/5).*(x-4/5));
rn = rn(t)
fprintf('----------Zadanie 3.----------\n')
lagrange_poly([-1, 0, 1], [3, 2, 5])
lagrange_poly([-1, 0, 1, 2], [3, 2, 5, 4])

fprintf('----------Zadanie 4.----------\n')
fprintf('----------Zadanie 5.----------\n')
% сравнение значения функции и полинома Лагранжа в точке 2
f(2)
poly_function(2)
task5(f, poly_function)

fprintf('----------Zadanie 6.----------\n')
rynge()

fprintf('----------Zadanie 7.----------\n')
chebishev()
