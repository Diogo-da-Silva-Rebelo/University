%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Inteligência Artificial - MiEI/3 LEI/3

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Operacoes aritmeticas.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado soma: X,Y,Soma -> {V,F}
soma(X,Y,Soma) :- Soma is X+Y.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado soma: X,Y,Z,Soma -> {V,F}
soma(X,Y,Z,Soma) :- Soma is X+Y+Z.
operacao(adicao,X,Y,R) :- R is X+Y.
operacao(subtracao,X,Y,R) :- R is X-Y.
operacao(multiplicacao,X,Y,R) :- R is X*Y.
operacao(divisao,X,Y,R) :- R is X/Y, Y/=0.
operacao(_,X,Y,R) :- R = 'Error: operation not specified'.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado maior: X,Y,Maior ->{V,F}
% podiamos definir como implicação: 
% maior1(X,Y,R) :- X>Y -> R is X; R is Y
% mas é muito mais fácil assim:
maior1(X,Y,X) :- X>=Y,!.
maior1(X,Y,Y).
% podiamos definir assim:
% maior2(X,Y,Z,R) :- X>=Y , X>=Z -> R is X ; Y>=X , Y>=Z -> R is Y; R is Z.
% mas seria mais fácil/eficaz assim:
maior2(X,Y,Z,X) :- X>=Y , X>=Z,!.
maior2(X,Y,Z,Y) :- Y>=X , Y>=Z,!.
maior2(X,Y,Z,Z).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado menor: X,Y,Menor ->{V,F}
% podiamos definir como implicação:
% menor1(X,Y,R) :- X<=Y -> R is X ; R is Y.
% mas é muito mais fácil assim:
menor1(X,Y,X) :- X<=Y,!.
menor1(X,Y,Y).
% podiamos definir assim:
% menor1(X,Y,Z,R) :- X<Y , X<Z -> R is X ; Y<X , Y<Z -> R is Y; R is Z.
% mas seria mais fácil/eficaz assim:
menor2(X,Y,Z,X) :- X<=Y , X<=Z,!.
menor2(X,Y,Z,Y) :- Y<=X , Y<=Z,!.
menor2(X,Y,Z,Z).
nao(Q) :- Q,!,Fail.
nao(Q).
par(X) :- mod(X,2) =:= 0.
impar(X) :- nao(par(X)).
mdc(X,X,X). 
mdc(X,Y,R) :- X<Y, Y1 is Y-X, mdc(X,Y1,R).
mdc(X,Y,R) :- X>Y, mdc(Y,X,R).
mmc(X,Y,R) :- X<Y, mmc(Y,Y,R)
mmc(X,Y,R) :- R is abs(X*Y)/mdc(X,Y).