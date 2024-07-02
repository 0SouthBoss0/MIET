function [point] = task5(a)
x = a/2;
eps = 1e-6;
while abs(1/2*(a/x + x) - x) > eps
    x = 1/2*(a/x + x);
end
point = x;
end