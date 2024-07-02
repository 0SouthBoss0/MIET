function [integral] = metod_simpsona(f, x_start, x_end, n)
    % рассчитываем шаг разбиения
    h = (x_end - x_start) / n;

    % создаем вектор значений функции в узлах разбиения
    x = linspace(x_start, x_end, 2*n+1);
    y = f(x);

    % Применяем метод Симпсона для вычисления интеграла
    integral = h/6 * (y(1) + 4*sum(y(2:2:2*n)) + 2*sum(y(3:2:2*n-1)) + y(2*n+1));
end
