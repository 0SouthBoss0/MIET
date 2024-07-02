function [answer] = function2(x)
eps = 1e-17;
u = x;
sinx = 0;
i=0;
while abs(u)>eps
    fprintf('Shag: %d: Poschitannyj chlen: %d; Chastichnaya summa ryada: %d\n', i, u, sinx)
    sinx = sinx + u;
    u=u*(-x^2)/((2*i+2)*(2*i+3));
    i=i+1;
end
answer = sinx;