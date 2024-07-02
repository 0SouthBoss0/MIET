function [] = chebishev(f, poly_f)
figure
hold on; grid on;
xlabel('x'); ylabel('y');

f = @(x)1./(1+25.*x.^2);
% ���������� ������� �������
plot(linspace(-1, 1), f(linspace(-1, 1)), 'r');

i=1:2:19
x_all=[cos(i.*pi./20)]

% ������������ �������� �������� �� ����� i
lagrange_polynomial = lagrange_poly(x_all, f(x_all))
% ������������ ������� �������� �� �������������
poly_function = @(x) polyval(lagrange_polynomial, x);
% ���������� ������� ��������
plot(linspace(-1, 1), arrayfun(poly_function, linspace(-1, 1)), 'b');
end