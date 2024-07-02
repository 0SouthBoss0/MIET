function [X] = metod_kramera(A, B)
   dA=det(A);
   if (dA==0)
        error 'A - вырожденная матрица'
    end
    dx=zeros(length(B), 1);
    for i=1:length(B)
        dx(i)=det([A(:, 1:(i-1)), B, A(:, (i+1):length(B))]);
    end
    X = dx./dA;
end
