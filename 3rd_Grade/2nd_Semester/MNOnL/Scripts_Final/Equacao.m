format short;
%Mudar as options (descomentar a necessaria)
options = [optimset('Tolfun', 10^(-2))];
% options = [optimset('TolX', 10^(-2),'TolFun', 10^(-2))];

%valor inicial das iteracoes
init = 2;

%Resolver o sistema
[x,y,exitflag, output] = fsolve(@func, init, options)

%Funcao em questao
%Por em f(x) = 0 (IMPORTANTE)
function f = func(x)
f = x - 2*exp(-x) - 1.5;
    %f = (10 * x * sin(x/2))/ 2 - 10;
end