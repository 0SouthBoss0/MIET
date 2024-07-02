clc,clear
fprintf('Laboratornaya rabota 1. Rasprostranenie oshibok v vychislitelnyh procedurah.\n')
fprintf('Zadanie 1.\n')
p=poly(1:20);
roots(p)
p(2)=p(2)+1e-7;
roots(p)

fprintf('Zadanie 2.\n')
2^1023
2^1024
realmax
realmin

fprintf('Zadanie 3.\n')
format long e
sqrt(2)

fprintf('Zadanie 4.\n')
1e8 + 1e-7
1e8 + 1e-8

fprintf('Zadanie 5.\n')
a = 0;
for i = 1:10^7
  a=a+10^-16;
end
a = a +1;
a

fprintf('Zadanie 6.\n')
for i = 0:1:55
    eps = 2^-i;
    fprintf('Shag: %d: Eps: %d; Result: %d\n', i, eps, (1 + eps - 1) / eps)
end

fprintf('Zadanie 7.\n')
I = exp(-1);
for i = 2:1:30
    I = 1 - i*I;
    fprintf('I%d: %f\n', i, I)
end

fprintf('Zadanie 8.\n')
function1(0)
function1(pi/3)
function1(pi/2)
function1(pi)
function1(2*pi)

function2(12*pi)
function2(14*pi)
function2(16*pi)
