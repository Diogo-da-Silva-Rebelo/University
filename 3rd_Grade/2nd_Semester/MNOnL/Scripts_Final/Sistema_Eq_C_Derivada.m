format short;

%Mudar as options (descomentar a necessaria
%options = [optimset('TolX', 10^(-1))];
%options = [optimset('TolX', 10^(-1),'TolFun', 10^(-1))];
options = [optimset('TolX', 10^(-10), 'TolFun', 10^(-8), 'Jacobian', 'on')];

%valor inicial das iteracoes
init = [-1 -0.1];

%Resolver o sistema
% x = aproximação inicial
% y = imagem da aproximação incial
[x,y,exitflag, output] = fsolve(@func, init, options)

%Funcoes em questao
function [F,d] = func(x)
    F(1) = (70*exp(x(1))) + (20*exp(x(2))) - 27.5702;
    F(2) = (70*exp(2*x(1))) + (20*exp(2*x(2))) - 17.6567;
    
if nargout>1 %derivadas em baixo no formato [d1; d2] 
    d = [70*exp(x(1)) 20*exp(x(2));140*exp(x(1)) 40*exp(x(2))];
end
end