format short;
%Mudar as options (descomentar a necessaria)
%options = [optimset('TolX', 10^(-1))];
%options = [optimset('TolX', 10^(-2),'TolFun', 10^(-2))];
options = [optimset('TolFun', 10^(-3))];
% ysol dá: F(x1,x2)
%valor inicial das iteracoes
init = [2 1];

%Resolver o sistema (rotina)
[xsol,ysol,exitflag, output] = fsolve(@func, init, options)

%Funcoes em questao
%Por em f(x) = 0 (IMPORTANTE)
%Trocar o 5 pelo valor específico
function f = func(x)
    f(1)=log(x(1))-x(1)*x(2)-2
    f(2)=3*x(1)^2-x(2)^2-2*x(2)-1
    %f(1) = (x(1)^2 - x(2) - 5) * exp(-x(1)^2 - x(2)^2) + 0.1
    %f(2) = 20 * (x(1)^2 - x(2)^2) - 10
    %f(1) = (x(1)^6 - x(2)^3 - 0.5) * exp(-x(1)^2 - x(2)^2);
    %f(2) = 20 * (x(1)^2 - x(2)^2) - 5;
end