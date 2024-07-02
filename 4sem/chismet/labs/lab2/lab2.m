clc,clear
fprintf('Laboratornaya rabota 2. Metody dihotomii, Nyutona, prostyh iteracij.\n')
fprintf('Zadanie 1.\n')

f = @(x) x.^3-15.*x.^2+48.*x+64;
df = @(x) 3.*x.^2-30.*x+48;

x = linspace(-10, 10, 1000);
y = f(x);
grid on; hold on;
plot(x,y)

y1=[-200; 200];
x1=[-1.5; -1.5];
x2=[-0.5; -0.5];
x3=[7.5; 7.5];
x4=[8.5; 8.5];

plot(x1,y1,'r')
plot(x2,y1,'r')
plot(x3,y1,'r')
plot(x4,y1,'r')

p = [1 -15 48 64];
roots(p)

fprintf('----------------Zadanie 2.----------------\n')
fprintf('Dihotomia\n')
[point, iters] = task2(f, -1.5, 1.5, 0.0001)

fprintf('----------------Zadanie 3.----------------\n')
fprintf('Newton\n')
[point, iters] = task3(f, df, -4, 1, 0.0001)

fprintf('----------------Zadanie 4.----------------\n')
[point, iters] = task3(f, df, 6, 2, 0.0001)

fprintf('----------------Zadanie 5.----------------\n')
fprintf('MPI\n')
task5(2)

fprintf('----------------Zadanie 6.----------------\n')
fprintf('MPI\n')
phi = @(x, a) x.^2+x-a;
dphi = @(x) 2.*x+1;
%abs(2x+1)<1 <=> -1<x<0; a = x^2 => 1<a<0
task6(0.81)
task6(-0.12)
task6(1.21)

fprintf('----------------Zadanie 7.----------------\n')
fprintf('fzero\n')
fzero(f, [-4; 0])

fprintf('----------------Zadanie 8.----------------\n')
task8();