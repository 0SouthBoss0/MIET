clc, clear
format long
fprintf('Laboratornaya rabota 6. Reshenie sistem linejnyh uravnenij.\n')
fprintf('----------Zadanie 1.----------\n')

n = 3;
A = round(rand(n)*100)
B = round(rand(n,1)*100)

fprintf('������� �������� ��������:')
reversed_matrix(A, B)

fprintf('������� ������� �������:')
metod_kramera(A, B)

fprintf('----------Zadanie 2.----------\n')
fprintf('������� ������� ������ � ������� �������� ��������:')
metod_gaussa_mod(A, B)

fprintf('----------Zadanie 3.----------\n')
fprintf('������� ����� ���������� � ������������� ����:')
Q = rref([A, B]);
Q(:, n+1)

fprintf('������� ����� ����� ��������� �������:')
A\B

fprintf('�������� ������������:')
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

fprintf('������������ ����������� ��� ������������� �������:\n\n')
fprintf('������� �������� ��������:')
max(abs((X - reversed_matrix(A, B))))
fprintf('������� ������� �������:')
max(abs(X - metod_kramera(A, B)))
fprintf('������� ������� ������ � ������� �������� ��������:')
max(abs(X - metod_gaussa_mod(A, B)))
fprintf('������� ����� ���������� � ������������� ����:')
Q = rref([A, B]);
max(abs(X - Q(:, n+1)))
fprintf('������� ����� ����� ��������� �������:')
max(abs(X - A\B))