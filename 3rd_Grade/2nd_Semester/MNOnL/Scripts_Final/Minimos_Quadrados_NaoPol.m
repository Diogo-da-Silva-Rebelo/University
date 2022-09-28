format short;
%Quandos nos pedem um modelo segundo uma função que eles dão! M(c1,c2).
%valores de x
x = [1 3 4.3 7 9 13.5 15]; 

%valores de y
y = [8.2 10 10 13.1 8 20 26]; 

%valor inicial (para os c's) -> subentendido: eles não precisam de dizer.
init = [1 1 1];

%Resolver rotina
%erro = resnorm = S
[c,resnorm, residual, exitflag,output] = lsqcurvefit(@func,init, x, y)

%não esquecer do ponto:"."!
function f = func(c,x)
    %f=(c(1).*log(x(1))).+(c(2).*cos(1./x(1)))+(c(3).*x(2).^2);
    f = (c(1).*(x.^2)) + (c(2).*(exp(1./(x+1))))
    %f = c(1) .* (x.^3)  + c(2).* (exp(1./(x+1))) + c(3) .*(1./x);
end