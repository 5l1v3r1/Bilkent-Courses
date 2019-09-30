function [] = reserve( x )
n = 0;
fprintf('x%d = %4.2f \n',n,x)

n = n + 1;

x = (97/100)*x+245;
fprintf('x%d = %4.2f \n',n,x)

for x < 8166.66
    n = n + 1;
    y = x*(97/100)+(65+180);
    x = y;
    fprintf('x%d = %4.2f \n',n,y)
end

end
