function [integral] = metod_trapecij(f, x_start, x_end, n)
    % ������������ ��� ���������
    h = (x_end - x_start) / n;

    % ������� ������ �������� ������� � ����� ���������
    x = linspace(x_start, x_end, n+1);
    y = f(x);

    % ��������� ����� �������� ��� ���������� ���������
    integral = h/2 * (y(1) + 2*sum(y(2:n)) + y(n+1));
end
