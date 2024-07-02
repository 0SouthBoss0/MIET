function [integral] = metod_trapecij(f, x_start, x_end, n)
    % рассчитываем шаг разбиения
    h = (x_end - x_start) / n;

    % создаем вектор значений функции в узлах разбиения
    x = linspace(x_start, x_end, n+1);
    y = f(x);

    % применяем метод трапеций для вычисления интеграла
    integral = h/2 * (y(1) + 2*sum(y(2:n)) + y(n+1));
end
