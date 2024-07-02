function [] = task8()
f = @(x) sin(x)-x./2;
df= @(x) cos(x)-1/2;
x = linspace(-10, 10, 1000);
y = f(x);
grid on; hold on;
plot(x,y)

fprintf('Ditohomia\n')
[point, iters] = task2(f, -4, 1, 0.0001)
[point, iters] = task2(f, -0.5, 0.5, 0.0001)
[point, iters] = task2(f, 1, 3, 0.0001)

fprintf('Newton\n')
[point, iters] = task3(f, df, -4, 1, 0.0001)
[point, iters] = task3(f, df, -0.3, 1, 0.0001)
[point, iters] = task3(f, df, 2, 1, 0.0001)

fprintf('fzero\n')
fzero(f, [-4; -1])
fzero(f, [-0.5; 0.5])
fzero(f, [1; 3])
end