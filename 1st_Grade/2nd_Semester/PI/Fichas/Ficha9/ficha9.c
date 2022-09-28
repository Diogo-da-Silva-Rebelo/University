#include "abin.h"
#include <time.h>

ABin newABin (int r, ABin e, ABin d) {
    ABin a = malloc (sizeof(struct nodo));
    if (a!=NULL) {
        a->valor = r; a->esq = e; a->dir = d;
    }
    return a;
}

ABin RandArvFromArray (int v[], int N) {
    ABin a = NULL;
    int m;
    if (N > 0){
        m = rand() % N;
        a = newABin (v[m], RandArvFromArray (v,m), RandArvFromArray (v+m+1,N-m-1));
    }
    return a;
}

int altura (ABin a){
    int r = 0;
    if (a){
        r += max(altura(a->esq), altura(a->dir));
    }
    return (r);
}

int nFolhas (ABin a){
    int r = 0;
    if (a){
        if (!a->esq && !a->dir) r = 1;
        else {
            r = nFolhas(a->esq) + nFolhas(a->dir);
        }
    }
    return (r);
}

ABin maisEsquerda (ABin a){
    while(a && a->esq){
        a = a->esq;
    }
    return a;
}

void imprimeNivel (ABin a, int l){
    if (a && l == 0){
        printf("%d ", a->valor);
    } else if (a){
        imprimeNivel(a->esq,l-1);
        imprimeNivel(a->dir,l-1);
    }
}

void inorder(Abin a){
    if (a){
        inorder(a->esq);
    }
}
int procuraE (ABin a, int x){
    return (-1);
}

struct nodo *procura (ABin a, int x){
    return NULL;
}

int nivel (ABin a, int x){
    return (-1);
}

void imprimeAte (ABin a, int x){

}

int main (){
    int v1[15] = { 1, 3, 5, 7, 9,11,13,15,17,19,21,23,25,27,29},
            v2[15] = {21, 3,15,27, 9,11,23, 5,17,29, 1,13,25, 7,19},
            N=15;
    ABin a1, a2,r;

    srand(time(NULL));

    printf ("_______________ Testes _______________\n\n");
    // N = rand() % 16;
    a1 = RandArvFromArray (v2, N);
    printf ("Primeira árvore de teste (%d elementos)\n", N);
    dumpABin (a1, N);

    printf ("altura = %d\n", altura (a1));
    printf ("numero de folhas: %d\n", nFolhas (a1));
    printf ("Nodo mais à esquerda: ");
    r = maisEsquerda (a1);
    if (r==NULL) printf ("(NULL)\n"); else printf ("%d\n", r->valor);
    printf ("Elementos no nivel 3_______\n");
    imprimeNivel (a1, 3);
    printf ("\n___________________________\n");

    printf ("procura de 2: %d\n", procuraE (a1, 2));
    printf ("procura de 9: %d\n", procuraE (a1, 9));

    freeABin (a1);

    // N = rand() % 16;
    a2 = RandArvFromArray (v1, N);
    printf ("\nSegunda árvore de teste (%d elementos)\n", N);
    dumpABin (a2, N);

    printf ("procura de 9: ");
    r = procura (a2, 9);
    if (r==NULL) printf ("(NULL)\n"); else printf ("%d\n", r->valor);
    printf ("procura de 2: ");
    r = procura (a2, 2);
    if (r==NULL) printf ("(NULL)\n"); else printf ("%d\n", r->valor);
    printf ("nível do elemento 2: %d\n", nivel (a2, 2));
    printf ("nível do elemento 9: %d\n", nivel (a2, 9));
    imprimeAte (a2, 20);

    freeABin (a1);

    printf ("\n\n___________ Fim dos testes ___________\n\n");
    return 0;
}
