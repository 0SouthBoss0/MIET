clc, clear
format long
fprintf('Laboratornaya rabota 6. Reshenie sistem linejnyh uravnenij.\n')
fprintf('----------Zadanie 1.----------\n')

n = 3;
A = round(rand(n)*100)
B = round(rand(n,1)*100)

fprintf('Решение обратной матрицей:')
reversed_matrix(A, B)

fprintf('Решение методом Крамера:')
metod_kramera(A, B)

fprintf('----------Zadanie 2.----------\n')
fprintf('Решение методом Гаусса с выбором главного элемента:')
metod_gaussa_mod(A, B)

fprintf('----------Zadanie 3.----------\n')
fprintf('Решение через приведение к диагональному виду:')
Q = rref([A, B]);
Q(:, n+1)

fprintf('Решение через левое матричное деление:')
A\B

fprintf('Проверка подстановкой:')
A * (A\B)

fprintf('----------Zadanie 4.----------\n')
n = 20;
A = (rand(n)*100000);
X = (rand(n,1)*100000);

while cond(A)<=10^3
    A = (rand(n)*100000);
    X = (rand(n,1)*100000);
end

B = A * X;

fprintf('Максимальная погрешность при использовании методов:\n\n')
fprintf('Решение обратной матрицей:')
max(abs((X - reversed_matrix(A, B))))
fprintf('Решение методом Крамера:')
max(abs(X - metod_kramera(A, B)))
fprintf('Решение методом Гаусса с выбором главного элемента:')
max(abs(X - metod_gaussa_mod(A, B)))
fprintf('Решение через приведение к диагональному виду:')
Q = rref([A, B]);
max(abs(X - Q(:, n+1)))
fprintf('Решение через левое матричное деление:')
max(abs(X - A\B))