format short;
%valores de x
%x = [1 2 4 7 8 10 12 14 16 18 19 21	23 24]; 
x = [0.5 1.5 2]
%valores de y
%y = [30	29 33 40 39 33 39 38 30	31 45 50 44 30];
y = [-0.69 0.41 0.69]

%Derivadas para pontos fronteira sao dadas
%d0: derivada no primeiro número
%dn: derivada no último número
d0 = 2;
dn = 0.5;

%Calculo da spline com as derivadas e todos os pontos
sp = spline (x, [d0 y dn]);

% Mostrar coeficientes dos segmentos das splines (descomentar em baixo)
sp.coefs

% valor de x (onde) numa spline 
onde = 1;
valor_spline = spline(x, [d0 y dn], onde)

