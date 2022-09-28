format short;
%valores de x
x = [0.0 0.3 0.5 0.6 0.8]; 

%valores de y
y = [0.302 0.106 0.240 0.579 0.468]; 

%Spline Natural nao é preciso calcular derivadas

%Calculo da spline com as derivadas e todos os pontos
sp = spline (x, y);

%Mostrar coeficientes dos segmentos das splines (descomentar em baixo)
%sp1 = coef1 (x - seg1)^3 + coef2(x-seg1)^2...
%sp2 = coef1 (x - seg2)^3 + coef2(x-seg2)^2...
sp.coefs;

% valor de x (onde) numa spline 
onde = 0.4;
valor_spline = spline(x, y, onde)