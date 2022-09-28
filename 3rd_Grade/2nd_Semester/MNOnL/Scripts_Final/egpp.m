%EGPP
format short;
% matriz A de coeficientes
% colocar cada elemento da matriz separado por um espaço.
% cada linha da matriz separa-se com um ";".
A=[5 1 5;2 1 5;7 9 10];
% vetor b de Termos Independentes
% cada elemento do vetor separa-se com um ";".
b=[0.5;0.5;0.5];
% matriz do sistema [A | b]
F=A\b

% os elementos x1, x2, x3 são fornecidos no output por ordem.

% calcular determinante da matriz A
D = det(A);
% calcular inversa da matriz A
I = inv(A);