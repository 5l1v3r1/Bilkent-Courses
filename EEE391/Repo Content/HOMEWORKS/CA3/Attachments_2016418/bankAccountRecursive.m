function [ y ] = bankSystem( x )
n = 0;
fprintf('x%d = %4.2f \n',n,x)
for n = 0:5 
    n = n + 1;

    if mod(n,2) == 0
        y = x*(109/100)-2500;
        x = y;
        fprintf('x%d = %4.2f \n',n,x)
    end
    
    if mod(n,2) == 1
        y = x*(109/100)+1000;
        x = y;
        fprintf('x%d = %4.2f \n',n,x)
    end

end

end

