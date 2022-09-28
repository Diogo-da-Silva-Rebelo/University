#include "string.h"
#include "stdlib.h"
#include "stdio.h"

//1
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

int paresImpares1(int v[], int N){
   int count = 0;
   int i, j;

    for (i = 0; i < N; i++){
        if (v[i]% 2 == 0){
            count++;
            int temp = v[i];
            for (j = i; j > 0; j--){
                v[j] = v[j-1];
            }
            v[0] = temp;
        }
    }

    return count;
}

//2
typedef struct LInt{
    int valor;
    struct LInt *prox;
} *LInt;

void merge(LInt *r, LInt a, LInt b) {
    while (a || b) {
        if (!b || (a && a->valor < b->valor)) {
            *r = a;
            a = a->prox;
        } else {
            *r = b;
            b = b->prox;
        }
        r = &((*r)->prox);
    }
}

//3
int void latino(int N,int m[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            m[i][j] = (i + j) % N + 1;
        }
    }
}

//4
typedef struct nodo {
    int valor;
    struct nodo *pai, *esq, *dir;
} *ABIn;

ABin esq (ABin a){
    if(a){
        if(a->esq)
            return esq(a->esq);
        else
            return a;
    } else return NULL;
}

ABin next(ABin a){
    if(a){
        if(a->dir){
            return esq(a->dir);
        }else{
            if(a->pai){
                if(a->pai->dir==a) return NULL;
            } else return a->pai;
            else return NULL;
        }
    }
    return NULL;
}


int main(){
    int v[] = {0,2,3,7,3,0,0};
    printf("n elementos par: %d\n", paresImpares1(v,7));

    for (int i = 0; i < 7; i++){
        printf("%d", v[i]);
        putchar('\n');
    }

    return 0;
}
