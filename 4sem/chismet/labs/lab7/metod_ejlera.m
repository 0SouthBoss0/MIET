function [] = metod_ejlera(f, x0, f0, X, n)
x_plot = [];
y_plot = [];  

h = (X-x0) / n;
x_plot(1) = x0;
y_plot(1) = f0;
c=2;
    for i = x0+h :h:X
        x_plot(c) = i;
        y_plot(c) = y_plot(c-1) + h * f(x_plot(c-1), (y_plot(c-1)));
        c= c+1;
    end
  plot(x_plot, y_plot, 'r');
  ezplot(@(x) x^3/3+1, [0,1]);
end
