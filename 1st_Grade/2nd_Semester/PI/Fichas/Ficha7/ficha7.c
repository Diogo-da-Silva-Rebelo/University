#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct celula {
    char *palavra;
    int ocorr;
    struct celula * prox;
} * Palavras, Celula;


void libertaLista (Palavras l){
    Palavras aux;
    while (l != NULL) {
        aux = l;
        l = l->prox;
        free(aux);
    }
}

//destruição da lista de trás para a frente
void libertaLista2 (Palavras l){
    if (l) {
        libertaLista2(l->prox);
        free(l);
    }
}

int quantasP (Palavras l){
    int sum = 0;
    while (l){
        sum++;
        l = l->prox;
    }
    return sum;
}

void listaPal (Palavras l){
    while(l){
        printf("%s :: %d\n",l->palavra,l->ocorr);
        l = l->prox;
    }
}
//posição da última cécula -> prox == NULL
char * ultima (Palavras l){
    while (l){
        l = l->prox;
        if (l->prox == NULL){
            return l->palavra;
        }
    }
    return NULL;
}
//Nestes casos em que temos várias condições no while, temos de identificar sempre depois a condição que nos fez sair do ciclo!!
char * ultima2 (Palavras l){
    while (l && l->prox) l = l->prox;
    if (l) return l->palavra;
    else return NULL;
    //return l ? l->palavra : NULL
}

Palavras acrescentaInicio (Palavras l, char *palavra){
    //1. Alocar memória para a struct que vamos adicionar
    //Palavras new = malloc(sizeof (struct celula));
    Palavras aux = malloc(sizeof (Celula));
    //2. Copiar informação para a nova célula;
    aux->palavra = strdup(palavra);
    //3. Unir a célula à lista
    aux->ocorr = 1;
    aux->prox = l;
    return aux;
}

Palavras acrescentaFim (Palavras l, char *p){
    Palavras aux2 = l , aux = malloc(sizeof (Celula));
    aux->palavra = strdup(p);
    aux->prox = NULL;
    aux->ocorr = 1;

    while (l && l->prox) l = l->prox;
    if (l) {
        l->prox = aux;
        return aux2;
    }
    else return aux;
}
//inserção ordenada (assumimos que a lista está ordenada)
//Acesso ordenado
Palavras acrescenta (Palavras l, char *p){
    if (!l || (strcmp(p,l->palavra) < 0)) {
        return acrescentaInicio(l,p);
    } else if ((strcmp(p,l->palavra) == 0)) {
    l->ocorr++;
    return l;
    } else {
       l->prox = acrescenta(l->prox,p);
        return l;
    }
}

Palavras maisFreq (Palavras l){
    Palavras res = NULL;
    int max = 0;

    while(l){
        if (l->ocorr > max){
            res = l;
            max = l->ocorr;
        }
        l = l->prox;
    }
    return res;
}

//função de remoção: localizar celula; trocar apontador; dar free da célula removida;
int main () {
    Palavras dic = NULL;

    char * canto1 [44] = {"as", "armas", "e", "os", "baroes", "assinalados",
                          "que", "da", "ocidental", "praia", "lusitana",
                          "por", "mares", "nunca", "de", "antes", "navegados",
                          "passaram", "ainda", "alem", "da", "taprobana",
                          "em", "perigos", "e", "guerras", "esforcados",
                          "mais", "do", "que", "prometia", "a", "forca", "humana",
                          "e", "entre", "gente", "remota", "edificaram",
                          "novo", "reino", "que", "tanto", "sublimaram"};

    printf ("\n_____________ Testes _____________\n\n");

    int i; struct celula *p;
    for (i=0;i<44;i++)
        dic = acrescentaInicio (dic, canto1[i]);

    printf ("Foram inseridas %d palavras\n", quantasP (dic));
    printf ("palavras existentes:\n");
    listaPal (dic);
    printf ("última palavra inserida: %s\n", ultima (dic));

    libertaLista (dic);

    dic = NULL;

    srand(42);

    for (i=0; i<1000; i++)
        dic = acrescenta (dic, canto1 [rand() % 44]);

    printf ("Foram inseridas %d palavras\n", quantasP (dic));
    printf ("palavras existentes:\n");
    listaPal (dic);
    printf ("última palavra inserida: %s\n", ultima (dic));

    p = maisFreq (dic);
    //printf ("Palavra mais frequente: %s (%d)\n", p->palavra, p->ocorr);

    printf ("\n_________ Fim dos testes _________\n\n");

    return 0;
}

/* programa em C que escreve os números de 1 a 100 com as seguintes operações:
 * 1. Se o número é divisivel por 3, escreve ping;
 * 2. Se o número é divisível por 5, escreve pong;
 * 3. Se o número é divisível por 3 e 5 escreve ping-pong; */
//partir da condição mais específica para as outras;
void ping_pong(){
    int i = 0;
    while (i < 100){
        if (!(i % 3) && !(i % 5)) {
            printf("ping-pong");
        }
        else if (!(i % 5)){
            printf("pong");
        }
        else if (!(i % 3)){
            printf("ping");
        }
        i++;
    }
}




