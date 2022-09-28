format short;
%Quando nos fornecessem um conjunto de pontos e nos pedem a integral.
%valores de x
x = [0 10 15 25 30 48 60 70 90];

%valores de y
y = [0 10 30 25 10 28 40 42 30];

%Resolucao do integral (metodo do trapezio)
integral = trapz(x, y)

%Resolucao do integral com tolerancia
%tolerancia = 1e10
%integral = trapz(x,y,tolerancia)