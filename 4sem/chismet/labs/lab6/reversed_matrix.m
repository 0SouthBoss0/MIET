function [X] = reversed_matrix(A, B)
    if (det(A)==0)
        error 'A - ����������� �������'
    end
    X= inv(A)*B;
end
