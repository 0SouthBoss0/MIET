function [point, iters] = task3(f, df, x0, kratn, eps)
x = x0;
iters = 0;
while abs(x - kratn*f(x)/df(x) - x) > eps
    x = x - kratn*f(x)/df(x);
    iters = iters + 1;
end
point = x;
end