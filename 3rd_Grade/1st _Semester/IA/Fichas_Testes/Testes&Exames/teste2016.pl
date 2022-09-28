% Resolução do Teste 2016 - IA
% GRUPO 1

% Q1

/*
a)
Para a representação do conhecimento presente na figura 1 podem
utilizar-se os seguintes predicados:
consulta(paciente,médico,data).
especialidade(nome,médicos).

Para a representação do conhecimento imperfeito:
consulta(P,M,D):- não(consulta(P,M,D)),
                  não(exceção(consulta(P,M,D))).

especialidade(E,M):- não(especialidade(E,M)),
                     não(exceção(especialidade(E,M))).

nao(Q):- Q,!,fail.
nao(Q).

nulo(T):- T.

b)
consulta(rosa,ana,segunda).
consulta(saulo,carlos,terca).
% com conjuntos
excecao(consulta(sara,ana,quarta)).
excecao(consulta(sara,bruna,quarta)).
% com incertezas
consulta(tavares,duarte,#04).
excecao(consulta(P,M,D)):- consulta(P,M,#04).
% com datas - intervalos
consulta(urbano,eduardo,quinta).
excecao(consulta(rosa,ana,D)):- D >= segunda, D =< sexta.
% conjuntos
excecao(consulta(vasco,filipe,sabado)).
excecao(consulta(vasco,fiipe,domingo)).

especialidade(OeG,ana).
especialidade(G,bruna).
especialidade(CGePC,carlos).
especialidade(PC,duarte).
excecao(especialidade(CG,eduardo)).
excecao(especialidade(PC,eduardo)).
especialidade(O,filipe).

% campo nulo
nulo(@FG).
+ especialidade(@FG,guilherme) :: (especialidade(X,guilherme), nao(nulo(X))).

c)
Assumindo que existe um predicado "feriado" que data uma data verifica se é feriado.
+ consulta(P,M,D) :: (findall(P,(consulta(_,_,D),feriado(D)),L),length(L,N),N==0).

d)
- especialidade(E,M) :: (findall(M,consulta(_,M,_),L),length(L,N),N==0).
/*

% Q2

/*
a)
conjunção(verdadeiro,verdadeiro,verdadeiro).
conjunção(...)
mesmo para a disjunção.

% sistema
demoComp(Q,R) :- demo(Q,R).
demoComp(Q1ouQ2,R):-
        demo(Q1,R1).
        demoComp(Q2,R2).
        conjunção(R1,R2,R).
demoComp(Q1eQ2,R):-
        demo(Q1,R1).
        demoComp(Q2,R2).
        disjunção(R1,R2,R).

% ou
demo(Q1,Q2,verdadeiro) :-Q1,Q2.
demo(Q1,Q2,falso):-Q1.
demo(Q1,Q2,falso):-Q2.
demo(Q1,Q2,desconhecido):- nao(Q1),não(¬Q1).
demo(Q1,Q2,desconhecido):- nao(Q2),nao(¬Q2).

b)
i)
demo((consulta(rosa,M,segunda)eespecialidade(O,M)),verdadeiro).
ii)
demo(consulta(ines,xavier,D),especialidade(G,xavier),verdadeiro).
*/

% GRUPO 2

% Q1 - V
% Q2 - F: setof falha com lista vazia
% Q3 - F: questiona se X é igual a X+1
% Q4 - F: serve para manter a consistência da BC
% Q5 - F: continuam a existir predicados desconhecidos
% Q6 - V

% GRUPO 4
% 1. ver depois.
% 2. V, F, F (Redes computacionais), F (Atualização peso sinapses), F (só com ApreSuper ou de Ref).

% GRUPO 5
/*
a) Neurónio,axónios,Sinápses.
b) Regras de aprendizagem, peso das sinapses, aprendizagem
c) Axónios, transferência, valor de ativação
*/