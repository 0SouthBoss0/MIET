function [] = rynge()
figure
hold on; grid on;
xlabel('x'); ylabel('y');

f = @(x)1./(1+25.*x.^2);
% ���������� ������� �������
plot(linspace(-5, 5), f(linspace(-5, 5)), 'r');

i=-5:1:5;
% ������������ �������� �������� �� ����� i
lagrange_polynomial = lagrange_poly(i, f(i))
% ������������ ������� �������� �� �������������
poly_function = @(x) polyval(lagrange_polynomial, x);
% ���������� ������� ��������
plot(linspace(-5, 5), arrayfun(poly_function, linspace(-5, 5)), 'b');

% ��������� �������� ������� � �������� ��������
f(4.5)
poly_function(4.5)
delta = (poly_function(4.5) - f(4.5))



end