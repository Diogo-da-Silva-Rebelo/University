format short;

%valores de x
x = [1.5 2.0 2.2 3.0 3.8 4.0]; 

%valores de y
y = [4.9 3.3 3.0 2.0 1.75 1.5]; 

% Modelo de grau n
% P = polinomio 
% residuo = somatorio do quadrado do erro = S
grau = 2;
[P,a] = polyfit(x,y,grau)
residuo = a.normr^2

% Valor em x (onde) no Polinomio anterior (P)
onde = 3.5;
valor = polyval(P, onde);

% Representar o polinomio (descomentar em baixo)
%P