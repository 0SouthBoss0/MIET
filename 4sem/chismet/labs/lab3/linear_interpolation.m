function [func, f_plot] = linear_interpolation(f, x0, x1)
func = @(x)(f(x0) + ((f(x1)-f(x0))/(x1-x0))*(x-x0));
x = linspace(x0, x1);
f_plot = f(x0) + ((f(x1)-f(x0))/(x1-x0))*(x-x0);
end
