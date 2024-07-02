function [] = rynge()
figure
hold on; grid on;
xlabel('x'); ylabel('y');

f = @(x)1./(1+25.*x.^2);
% построение графика функции
plot(linspace(-5, 5), f(linspace(-5, 5)), 'r');

i=-5:1:5;
% коэффициенты полинома Лагранжа по узлам i
lagrange_polynomial = lagrange_poly(i, f(i))
% формирование функции полинома по коэффициентам
poly_function = @(x) polyval(lagrange_polynomial, x);
% построение графика полинома
plot(linspace(-5, 5), arrayfun(poly_function, linspace(-5, 5)), 'b');

% сравнение значения функции и полинома Лагранжа
f(4.5)
poly_function(4.5)
delta = (poly_function(4.5) - f(4.5))



end