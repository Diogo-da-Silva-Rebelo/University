%Resolução Ficha 1
u = [1 2 3];
v = [1;2;3];
s = [1:10];
t = [2:2:12];
A = [1,2,3;4,5,6;7,8,9];


B = A(2:3,1:2);
% Ir á matriz e considerar apenas a matriz nas linhas 2 a 3 e colunas 1 a 2.
C = A(:,1:2);
% Ir à matriz e considerar todas as linhas e apenas as colunas 1 a 2.
D = [A;4 4 4];
% Ir à matriz A e adicionar a linha 4 4 4.
E = D([2,4],:);
% A matriz E será a matriz que resulta de ir á matriz D, ler as suas linhas
% 2 e 4, e todas as suas colunas.
F = [0:3:9;2:2:8;5:5:20];
% F será a matriz resultante com linha 1 = 0 3 6 9, linha 2 = 2 4 6 8,
% linha 3 = 5 10 15 20.


id = eye(5);
al = rand(3);
al2 = 2*rand(4,3) - 1;
n = zeros(2,3);
o = ones(2);
d = ones(10)*10;
diagA = diag(diag(A));

A = [1,3,5;0,4,1;2,2,1];
B = ones(3);
vectorA = [1 2 1];
vectorB = [0 3 5];
vectorC = vectorA .* vectorB;
S = A + B;
P = A * B;

% Podemos correr no prórpio script
% exercício 1.6
%[soma,produto] = ex16PL6([1 3 3])
% Outra forma de resolução neste mesmo script:
%.* multiplica elemento a elemento
clear var A B
x = input('escreva o 1o no.');
y = input('escreva o 2o no.');
PR = [x y];
m = max(PR);
disp(m);

% programa com ciclos
n = input('quantos numeros?');
sum = 0;
prod = 1;
for i = 1:n
    num = input('');
    sum = sum + num;
    prod = prod*num;
end
fprintf('Soma dos nos. %i\n', sum);
fprintf('Produto dos nos. %i\n', prod);