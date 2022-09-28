%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% inteligência Artificial - MiEI/3 LEI/3

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Operacoes sobre listas.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado pertence: Elemento,Lista -> {V,F}

% Solução recursiva
pertence(X,[X|L]).
pertence(X,[Y|L]) :- X \= Y, pertence(X,L).

member(X,[X|_]).
member(X,[_|T]) :- member(X,T).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado comprimento: Lista,Comprimento -> {V,F}

comprimento([],0).
comprimento([X|L],N) :- comprimento(L,N1), N is N1+1.

len([],0).
len([_,L],N) :- len(L,X), N is X+1.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do meta-predicado nao: Questao -> {V,F}

nao(Q) :- Q,!,fail.
nao(Q).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado quantos: Lista,Comprimento -> {V,F}

% Quantos elementos diferentes existem na lista (versão feita na aula)
quantos([],0).
quantos([H|T],N) :- pertence(H,T), quantos(T,N).
quantos([H|T],N1) :- nao(pertence(H,T)), quantos(T,N), N1 is N + 1.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado diferentes: Lista, Valor -> {V,F}

diferentes([],0).
diferentes([H|T],V) :- pertence(H,T), !, diferentes(T,V).
diferentes([H|T],V) :- nao(pertence(H,T)), diferentes(T,V1), V is V1+1.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado apagar: Elemento,Lista,Resultado -> {V,F}

apaga1(X,[X|T],T).
apaga1(X,[H|T],[H|R]) :- X \= H, apaga1(X,T,R).


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado apagatudo: Elemento,Lista,Resultado -> {V,F}

apagaT(_,[],[]) :- !.
apagaT(X,[X|T],A) :- apagaT(X,T,A),!.
apagaT(X,[H|T],[H|R]) :- X \= H, apagaT(X,T,R), !.

% outra versão
delMember(X, [], []) :- !.
delMember(X, [X|Xs], Y) :- !, delMember(X, Xs, Y).
delMember(X, [T|Xs], Y) :- !, delMember(X, Xs, Y2), append([T], Y2, Y).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado adicionar: Elemento,Lista,Resultado -> {V,F}

adicionar(X,[],[X]) :- !.
adicionar(X,[X|T],[X|T]) :- !.
adicionar(X,[H|T],[H|R]) :- X\=H, adicionar(X,T,R), !.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado concatenar: Lista1,Lista2,Resultado -> {V,F}

% Easy lmao
concatenar(X,Y,R) :- append(X,Y,R).

% outra versão
concatenar2([],List,List).
concatenar2([X|Xs],List,[X|R]) :- concatenar2(Xs,List,R).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado inverter: Lista,Resultado -> {V,F}

% com 3 argumentos neste caso
reverse([],Z,Z).
reverse([H|T],Z,Acc) :- reverse(T,Z,[H|Acc]).

% com 2 argumentos como pedido
inverter2([],[]) :- !.
inverter2([X],[X]) :- !.
inverter2([X|Xs], R) :- inverter(Xs,R1), concatenar2(R1,[X],R).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado sublista: SubLista,Lista -> {V,F}
% estudar estas versões
% versão 1
sublista([], _).
sublista([H|T], [H|X]) :- sublista(T, X).
sublista([A|L], [H|T]) :- pertence(T, A), sublista(L, T).

% versão 2
prefix(L,R) :- conc(L,_,R).
sufix(L,R) :- conc(_,L,R).
subl(S,L) :- sufix(Suf,L), prefix(S,Suf).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -