% Resolução do Teste 2015 - IA
% GRUPO 1

% Q1

/*
_ nulo incerto -> predicado e exceção
{} conjuntos - nulo impreciso -> exceção
[] intervalos - nulo impreciso -> excecao
'#' nulo interdito -> predicado, excecao, nulo, invariante

a)
Para a representação do conhecimento da tabela 1, é necessário existir:
Extensão do predicado aluno: id,nome,curso,ano,creditos,propina -> {V,F,D}
Tal resulta em:
aluno(id,nome,curso,ano,creditos,propina).

Para representação do conhecimento imperfeito, usa-se:
Extensão do predicado nao: questao -> {V,F}
Extensão do predicado nulo: termo -> {V,F}
Extensão do predicado excecao: predicado -> {V,F,D}

aluno(I,N,Cur,A,Cred,P) :- nao(aluno(I,N,Cur,A,Cred,P)).
                           nao(excecao(aluno(aluno(I,N,Cur,A,Cred,P)))).

b)
aluno(12345,ana,lei,1,60,sim).
aluno(23456,beatriz,lcc,2,60,nao).
% tipo nulo impreciso
exceção(aluno(3456,carlos,mdi,1,Cred,sim)) :- Cred >= 0, Cred < 45.
...
% tipo nulo incerto
aluno(56789,eva,miec,4,240,talvez).
excecao(aluno(56789,_,_,_,_,P)) :- aluno(56789,_,_,_,_,talvez).

excecao(aluno(67890,filipe,lfis,1,45,nao)).
excecao(aluno(67890,filipe,lfis,1,54,nao)).
excecao(aluno(67890,filipe,lefis,1,45,nao)).
excecao(aluno(67890,filipe,lefis,1,54,nao)).
...

% tipo nulo interdito
aluno(89012,heitor,'#73',1,10,nao).
excecao(aluno(89012,_,Cur,_,_,_)) :- aluno(89012,_,'#73',_,_,_).
nulo('#73').
+ aluno(89012,_,_,_,_,_)) :: ((findall(Cred, (aluno(89012,_,Cred,_,_,_),nao(nulo(Cred)),S), length(S,N), N==0).
...

c) Invariantes de impossivel curso ter mais do que 5 anos e nº cred nunca exceder 300 ECTS.
+ aluno(_,_,_,Ano,_,_) :: Ano=<5.
+ aluno(_,_,_,_,Cred,_) :: Cred=<300.

d) Invariantes de inserção de conhecimento na BC
evolucao(X):-
  findall(Inv, +Termo :: Inv, L),
  insere(Termo),
  testa(L).

inserir(T):- assert(T).
inserir(T):- retract(T),!,fail.

testa([]).
testa([R|L]):- R,testa(L).
/*

% Q2
*/
demo(Q,verdadeiro):- Q.
demo(Q,falso):- ¬Q.
demo(Q,desconhecido):- nao(Q),nao(¬Q).
/*

% GRUPO 2
/*
Q1: F - O operador '=' é um functor utilizado para a obtenção de termos
e não para a comparação de valores.
Q2: V
Q3: F - As duas designações reference a casos em que existem provas de falsidade
de predicados na BC.
Q4: F - os valores nulos assumem a representação de conhecimento desconhecido.
Q5: F - os invariantes definem regras de teste à consistência do conhecimento, sendo
que NÃO são utilizados para representação de conhecimento.
Factos e regras representam conhecimento.
*/

% GRUPO 3
/*
Q1:
1. V
2. V
3. V
4. F - implementação correta.
5. V
Q2:
1. F - é com base em casos passados.
2. V
3. F - é apenas com um único axónio.
4. F - depende do peso das sinapses.
5. F - por 1 ou mais.
*/
% GRUPO 4
% neurónios, aprender.
% posição, estado.
% os axónios, sinapse, aprendizagem.
% Feedforward (grafo sem ciclos e com camadas), FeedBack (pelo menos 1 ciclo).
% processos de aprendizado/paradigmas de aprendizagem.
% Supervisionado - há um agente externo que fornece-se resposta
% Não Supervisionado - não há fornecimento de resposta
% Reforço - crítico externo que avalia a resposta fornecida pela rede.