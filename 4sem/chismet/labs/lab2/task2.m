function [x, i] = task2(f, a, b, eps)
i = 0;
x = 0;
while (b - a) > eps
    c = (a + b) / 2;
    i = i + 1;
    if f(a) * f(b) == 0
        x = c;
        break
    elseif f(a) * f(c) < 0
        b = c;
    else
        a = c;
    end
end
x = a;
end
