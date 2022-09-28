format short;

%Quando nos dão uma expressão de um integral e nos pedem uma aproximação.
%Colocar intervalos do integral (extremos)
inicio = 0;
fim = 2;

%Resolucao do integral (metodo do trapezio)
[integral,npontos] = quad(@func, inicio, fim)

%Resolucao do integral com tolerancia
%tolerancia = 1e(-10)
%[integral,npontos] = quad(@func, inicio, fim, tolerancia)
 
%Como estamos a fazer operações com todos os elementos
%da matriz, é preciso usar '.' antes de cada operação!
function f = func(x)
    f = (x.^2).*exp(x)
    %f = (exp(x))./(cos(x))
end