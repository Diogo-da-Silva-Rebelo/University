% Resolução do Teste 2014 - IA
% GRUPO 1

% Q1
/*
Disjunção de literais com no máximo 1 literal positivo.
¬x1 ou ¬x2 ou ... ou ¬xn ou y

x1 e x2 e ... e xn -> y
¬(x1 e x2 e ... e xn) ou y
¬x1 ou ¬x2 ou ... ou ¬xn ou y

Considerem-se as seguintes proposições:
p: O Pedro reaizou o exame de lógica.
q: O Pedro obteve classificação superior a 19 valores.
¬p: O Pedro não reaizou o exame de lógica.
¬q: O Pedro obteve classificação inferior a 19 valores.

p e q: representa a expressão em questão, mas temos 2 literais positivos e só podemos literais
no máximo 1, logo temos de alterar a fórmula para uma cláusula de Horn:

    p e q <=>
<=> ¬ (¬ (p e q))
<=> ¬ (¬p ou ¬q)
*/

% Q2
/*
a)
Para representação do conhecimento da Tabela 1, considere-se:
Extensão do predicado viatura: matricula,cor,marca,valor,proprietario,localidade -> {V,F,D}.
Tal resulta em:
viarura(matricula,cor,marca,valor,proprietario,localidade).

Para representação do conhecimento imperfeito, considere-se:
Extensão do predicado nao: questao -> {V,F}
Extensão do predicado nulo: termo -> {V,F}
Extensão do predicado exceção: predicado -> {V,F,D}

b)
viarura(o1ZZo1,dourado,ashton,100,antunes,anadia).
viatura(o2ZZo2,prateado,bercedes,200,P,L).
...
viatura(o4zzo4,"#004",drof,400,P,L).
exceção(viatura(o4zzo4,Cor,_,_,_,_)) :- viatura(o4zzo4,"#004",_,_,_,_).
nulo("#004").
+ viatura(o4zzo4,Cor,_,_,_,_) :: (findall(Cor,(viatura(o4zzo4,Cor,_,_,_,_),nao(nulo("#004"))),S),length(S,L),L==0).
...

*/