function lagrange_polynomial = lagrange_poly(x, y)
 n = length(x);  
 coefficients = zeros(1, n);
    for i = 1:n
        num = 1;
        den = 1;
        for j = 1:n
            if j ~= i
                num = conv(num, [1, -x(j)]);
                den = den * (x(i) - x(j));
            end
        end
        coefficients = coefficients + y(i) * num / den;
    end
   lagrange_polynomial = coefficients;
end