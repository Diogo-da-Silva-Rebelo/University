#include <stdio.h>
#include <stdlib.h>
#include "pessoas.h"
//projeto em https://codeboard.io/projects/20354
void troca (Pessoa *p[], int i, int j){
    // esta função troca os valores dos indices i e j
    Pessoa *tmp;
    tmp=p[i]; p[i]=p[j]; p[j]=tmp;
}
int idade (Pessoa p, Data hoje){
    Data nasc = p.nascimento;
    int anoNasc = nasc.ano;
    int anoAtual = hoje.ano;
    if (nasc.mes <= hoje.mes){
        return anoAtual - anoNasc + 1;
    } else {
        return anoAtual - anoNasc;
    }
    // retorna a idade (número de anos) de uma pessoa relativamente a hoje
    return (anoAtual - anoNasc);
}

int comparaIdade (Data t1, Data t2){
//recebe duas datas e compara-as
//se t1 for menor que t2, retorna -1, senão retorna 1
    if (t1.ano < t2.ano){
        return -1;
    } else if (t1.ano == t2.ano){
        if (t1.mes < t2.mes) return -1;
        else if (t1.mes == t2.mes){
            if (t1.dia < t2.dia) return -1;
            else return 1;
        }
        else return 1;
    }
    return 1;
}

void ordena (Pessoa *p [], int N) {
// ordena um vector com N (endereços de) pessoas por ordem decrescente da sua idade
// isto é, por ordem crescente da data de nascimento.
// Use a função troca (definida acima) para trocar elementos do vector
    int i,j;
    Data dH;
    dH.ano = 2021;
    dH.mes = 6;
    dH.dia = 30;

    for (i = 0; i < N; i++){
        for (j = i; j < N; j++){
            if(comparaIdade(p[i]->nascimento,p[j]->nascimento) == 1) troca(p,i,j);
        }
    }
    return;
}