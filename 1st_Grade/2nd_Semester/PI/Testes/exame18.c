#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct posicao {
    int x, y;
} Posicao;

typedef struct slist {
    int valor;
    struct slist *prox;
} *LInt;

typedef struct node {
    int data;
    struct node *left, *right;
} *ABin;

//Parte A
//1
char *my_strstr (char s1[], char s2[]) {
    int i, j;
    if (!*s2) return s1;
    if (!*s1) return (!*s2) ? s1 : NULL;
    for (i = 0; s1[i]; i++) {
        for (j = 0; s1[i + j] && s2[j] && s1[i + j] == s2[j]; j++) {
            if (!s2[j + 1]) return s1 + i;
        }
    }
    return NULL;
}

//2
void truncW (char t[], int n) {
 int len = 0, i = 0, j;
    while(t[i]){
    if (t[i] == ' ' || t[i] == '\n' || t[i] == '\t'){
        len = 0;
        i++;
    } else if (len < n){
        len++;
        i++;
    } else {
        for (j = i; t[j]; j++) t[j] = t[j+1];
    }
    }
}

//3
int calculaDistanciaOrigem (Posicao p){
    return (int) sqrt(pow(p.x,2) + pow(p.y,2));
}

int maisCentral (Posicao pos[], int N){
    int min = 0;
    int min_dist = calculaDistanciaOrigem(pos[0]);
    int i;

    if (N == 0) return -1;
    //d(x,y) = sqrt(x*x + y*y)
    for (i = 0; i < N ; i++){
        int dist = calculaDistanciaOrigem(pos[i]);
        if (dist < min_dist) {
            min = i;
            min_dist = dist;
        }
    }
    return min;
}

//3
int sizeList(LInt list){
    int len = 0;
    if (list == NULL) return 0;
    else {
        while(list){
            len++;
            list=list->prox;
        }
    }
    return len;
}

LInt somasAcL (LInt l) {
    LInt ans = NULL;
    int soma = 0;
    for(;l;l = l->prox) {
        soma += l->valor;
        LInt new = malloc(sizeof(struct slist));
        new->valor = soma;
        new->prox = NULL;
        if(!ans) ans = new;
        else {
            LInt temp = ans;
            while(temp->prox) temp = temp->prox;
            temp->prox = new;
        }
    }
    return ans;
}

//5
ABin newNode(int data){
    // Allocate memory for new node
    ABin a = malloc(sizeof(struct node));
    // Assign data to this node
    a->data = data;
    a->left = NULL;
    a->right = NULL;
    return (a);
}

//travessias
// [ left, visit, right ]
void inOrder(ABin n){
    if (n) {
        if (n->left) inOrder(n->left);
        printf("%d ", n->data);
        if (n->right) inOrder(n->right);
    }
}

// [ visit, left, right ]
void preOrder(ABin n){
   if (n) {
       printf("%d ", n->data);
       if (n->left) preOrder(n->left);
       if (n->right) preOrder(n->right);
   }
}

// [ left, right, visit ]
void posOrder(ABin n){
    if(n) {
        if (n->left) posOrder(n->left);
        if (n->right) posOrder(n->right);
        printf("%d ", n->data);
    }
}
void printABin(ABin a){
    if(a != NULL) {
        printABin(a->left);
        printf("%d\n", a->data);
        printABin(a->right);
    }
}

//versão iterativa
ABin addOrd (ABin a, int x) {
    if ((a) == NULL) {
        (a) = newNode(x);
        return (a);
    }

    while ((a) != NULL) {
        if ((a)->data == x) {
            printf("Value Already in tree!\n");
            return (a);
        }
        else if (x < (a)->data) {
            if ((a)->left == NULL) {
                (a)->left = newNode(x);
                (a) = NULL;
            }
            else (a) = (a)->left;
        } else {
            if ((a)->right == NULL) {
                (a)->right = newNode(x);
                (a) = NULL;
            } else (a) = (a)->right;
        }
    }
    return (a);
}

//versão recursiva
ABin addOrdRec(ABin a, int x) {
    if ((a) == NULL) {
        a = newNode(x);
        return a;
    }

    if ((a)->data == x) {
        printf("Value Already in tree!\n");
        return (a);
    } else if (x < (a)->data) {
        a->left =  addOrdRec(a->left, x);
    } else {
        a->right = addOrdRec(a->right, x);
    }
    return a;
}

//Parte B
typedef struct celula {
    char *palavra;
    int comp;
    struct celula *prox;
} *Palavras;

int daPalavra (char *s, int *e) {
    for((*e) = 0; isspace(s[(*e)]);(*e)++);
    int len;
    for(len = 0; !isspace(s[len + (*e)]) && s[len + (*e)] != '\0';len++);
    return len;
}

// 2
Palavras words (char *texto) {
    if(!texto) return NULL;

    int e, n;
    n = daPalavra(texto,&e);

    if(!n) return NULL;

    Palavras new = malloc(sizeof(struct celula));

    new->palavra = texto + e;
    new->comp = n;
    new->prox = words(texto + e + n);
    return new;
}

// 3

Palavras daLinha (Palavras t, int n) {
    int len = 0;
    Palavras prev;
    for(;len < n && t;t = t->prox) {
        len += t->comp + 1;
        if(len > n) break;
        prev = t;
    }
    t = prev->prox;
    prev->prox = NULL;
    return t;
}

// 4
int tamLinha(Palavras p, int* numP) {
    int len = 0;
    (*numP) = 0;
    while(p) {
        len += p->comp;
        if(p->prox) len++;
        (*numP)++;
        p = p->prox;
    }
    return len;
}

void escreveLinha (Palavras p, int n) {
    int numP;
    int len = tamLinha(p,&numP);
    if(numP == 1) printf("%s\n",p->palavra);
    else {
        int espacos = n - len;
        while(p) {
            for(int i = 0; i < p->comp; i++) putchar(p->palavra[i]);
            numP--;
            if(p->prox) {
                putchar(' ');
                for(;(espacos/numP) > 0; espacos--) putchar(' ');
            }
            p = p->prox;
        }
    }
    printf("\n");
}

// 5
void formata (char texto[], int largura) {
    Palavras pals = words(texto);
    Palavras resto;
    while((resto = daLinha(pals,largura))){
        escreveLinha(pals, largura);
        pals = resto;
    }
    escreveLinha(pals,largura);
}

int main(){
    /*
    Posicao p1;
    p1.x = 0;
    p1.y = 5;

    Posicao p2;
    p2.x = 0;
    p2.y = 6;

    Posicao pos[] = {p1,p2};
    int minimo = maisCentral (pos, 2);
    printf("%d\n", minimo);
    */
    int v[20];
    ABin a = addOrd(a,3);
    addOrd(a,6);
    addOrd(a,2);
    addOrd(a,8);
    addOrd(a,5);
    printABin(a);

    for (int i = 0; i < 6;i++){
        printf("\n%d-", v[i] );
    }
    /*
    char *s = strdup("Aqui ao leme sou mais  do  que\n"
                     "eu: Sou um  povo  que  quer o\n"
                     "mar que e teu; E mais  que  o\n"
                     "mostrengo, que me a alma  teme\n"
                     "E roda nas trevas  do  fim do\n"
                     "mundo, Manda  a  vontade,  que\n"
                     "me ata ao leme, De  El-Rei  D.\n"
                     "Joao                  Segundo!");
    int *e = malloc(sizeof (int)*20);
    int x = daPalavra(" Joao Segundo!", e);
    printf("%d\n%d\n", x, (*e));
     */

    return 0;
}