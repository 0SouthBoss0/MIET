function [] = task5(f, poly_f)
figure
hold on; grid on;
xlabel('x'); ylabel('y');

plot(linspace(-1, 3), f(linspace(-1, 3)), 'r')
plot(linspace(-1, 3), poly_f(linspace(-1, 3)), 'b')


end