format short;
%valores de x
x = [1 2 4 7 8 10 12 14 16 18 19 21 23 24]; 

%valores de y
y = [30 29 33 40 39 33 39 38 30 31 45 50 44 30];
%tamanho da amostra
[lixo,tam] = size(x);

%Derivadas para pontos fronteira sao calculadas
d0 = (y(2) - y(1))/(x(2) - x(1));
dn = (y(tam) - y(tam-1))/(x(tam) - x(tam-1));

%Novos pontos; Nova tabela sem o 2 e penultimo pontos
xnov = [1 4 7 8 10 12 14 16 18 19 21 24]; 
ynov = [30 33 40 39 33 39 38 30 31 45 50 30];

%Calculo da spline com as derivadas e pontos a excessao dos removidos
sp = spline (xnov, [d0 ynov dn]);

%Mostrar coeficientes dos segmentos das splines (descomentar em baixo)
sp.coefs
% k = i - 1. i começa em 1. k começa em 0!!! Pedir k é o mesmo que pedir
% i-1!!

%       f( x )
% valor de x (onde) numa spline 
onde = 6;
valor_spline = spline (xnov, [d0 ynov dn],onde)