function [integral] = runge(f, x_start, x_end, eps)

    n = 1;
    I1 = metod_simpsona(f, x_start, x_end, n);
    n = 2;
    I2 = metod_simpsona(f, x_start, x_end, n);
    
    while(abs(I1-I2)/((2^2 - 1))>eps)
    n = n*2;
    I1 = I2;
    I2 = metod_simpsona(f, x_start, x_end, n);
    end
    integral = I2;
end
