function [point] = task6(a)
x = a/2;
eps = 1e-6;
iters = 0;
while (abs(x.^2+x-a - x) > eps) && iters<1000
    x = x.^2+x-a;
    iters = iters + 1;
end
if iters<1000
    point = x;  
else
    point = Inf;
end
end