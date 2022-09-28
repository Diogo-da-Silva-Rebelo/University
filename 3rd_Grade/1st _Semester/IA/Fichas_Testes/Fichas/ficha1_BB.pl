%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Inteligência Artificial MIEI /3  LEI/3

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Base de Conhecimento com informacao genealogica.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% SICStus PROLOG: Declaracoes iniciais

:- set_prolog_flag( discontiguous_warnings,off ).
:- set_prolog_flag( single_var_warnings,off ).
:- set_prolog_flag( unknown,fail ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado masculino: Homem -> {V,F}

masculino(joao).
masculino(jose).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado feminino: Mulher -> {V,F}

feminino(maria).
feminino(joana).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado filho: Filho,Pai -> {V,F}

filho( joao,jose ).
filho( jose,manuel ).
filho( carlos,jose ).
filho( filipe,paulo ).
filho( maria,paulo ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado pai: Pai,Filho -> {V,F}

pai( P,F ) :- filho( F,P ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado avo: Avo,Neto -> {V,F}

avo( A,N ) :- filho( N,X ),pai( A,X ).

avo( antonio,nadia ).
neto( nuno,ana ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado neto: Neto,Avo -> {V,F}

neto( N,A ) :- avo( A,N ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado bisavo: Bisavo,Bisneto -> {V,F}

bisavo( X,Y ) :- avo( X,P ),pai( P,Y )

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado trisavo: Trisavo,Trisneto -> {V,F}

trisavo( X,Y ) :- bisavo( X,P ),avo( P,Y )

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado descendente: Descendente,Ascendente -> {V,F}

descendente( X,Y ) :- bisavo( Y,X ); avo( Y,X ); pai( Y,X ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado descendente: Descendente,Ascendente,Grau -> {V,F}

grau( X,Y,1 ) :- filho( X,Y ).
grau( X,Y,1 ) :- pai( Y,X ).
grau( X,Y,2 ) :- avo( Y,X ).
grau( X,Y,3 ) :- bisavo( Y,X ).
grau( X,Y,4 ) :- trisavo( Y,X ).

grauFilho( F,N ) :- grau( F,N,1 ).
grauAvo( N,A ):- grau( N,A,2 ).
grauBisavo( BN,BA ):- grau( BN,BA,3 ).
grauTrisavo( TN,TA ) :- grau( TN,TA,4 ).

% por verificar: grau( D,A,G ):- filho(D,X), grau(X,A,N), G is N+1.

% Faz parte das extensões do predicado Avo, mas só é pedido aqui
avo( A,N ) :- grauAvo( N,A ).
bisavo( BA,BN ) :- grauBisavo( BN,BA )

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Árvores de prova ainda não foram lecionadas nas aulas


