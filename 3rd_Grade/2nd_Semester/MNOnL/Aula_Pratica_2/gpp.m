
format short
% Exercício resolução de sistema GGP
A = [0.8 1.4 3.0; 0.6 0.9 2.8; 2.0 1.0 1.1];
B = [12.6; 10.8; 4.0];
C = A\B;
D = det(A);
I = inv(A);

% Utilizar ponto para maior precisão (com floats, normalmente)
fplot(@volume,[0,4]);
grid
fx1=volume(0.25);
fx2=volume(0.5);

% funções colocadas no fim
function f = volume(x)
f =((pi.*x.^2.*(3-x))./3) - 0.5;
end