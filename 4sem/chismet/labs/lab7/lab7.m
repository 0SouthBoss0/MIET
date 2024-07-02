clc, clear
hold on, grid on
fprintf('Laboratornaya rabota 7. Metod Ejlera. Skhemy Runge-Kutta resheniya ODU.\n')

fprintf('----------Zadanie 1.----------\n')
f = @(x, y) x^2;
metod_ejlera(f, 0, 1, 1, 10)

fprintf('----------Zadanie 2.----------\n')
X0 =[0 15];
Y0=[1;0];

[T Y] = ode23('oscil',X0 , Y0);
figure(2)
hold on, grid on
ylabel('y')
plot(T,Y(:,1),'r-')

figure(3)
hold on, grid on
plot(T,Y(:,2),'r-')


[T Y] = ode45('oscil',X0, Y0);
figure(2)
plot(T,Y(:,1),'g-')
ezplot(@(t) exp(-t)*(87/85*cos(3*t)+26/85*sin(3*t))+1/85*(9*sin(t)-2*cos(t)), [0,15])


figure(3)
plot(T,Y(:,2),'g-')
ylabel('y''')
syms t
ezplot( diff(exp(-t)*(87/85*cos(3*t)+26/85*sin(3*t))+1/85*(9*sin(t)-2*cos(t)),1), [0,15])

fprintf('----------Zadanie 3.----------\n')
figure(4)
X0 = [0.01 15];
Y0=[log(0.01);100];
[T Y] = ode23('oscil2',X0 , Y0 );
plot(T,Y(:,1), 'r')
hold on, grid on

[T Y] = ode45('oscil2', X0, Y0);
plot(T,Y(:,1), 'g')
ylabel('y')

ezplot(log(t))
