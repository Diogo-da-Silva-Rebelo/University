#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;

typedef struct listaP{
    char *pal;
    int cont;
    struct listaP *prox;
} Nodo, *Hist;

//Parte A
//1
char *my_strcpy (char*dest, char source[]){
    int i;
    if (!strlen(source)) return NULL;
    for (i = 0; source[i];i++){
        dest[i] = source[i];
    }
    dest[i] = '\0';
    return dest;
}

//2
void my_strnoV (char s[]) {
    int i,j;

    for (i = 0; s[i]; i++) {
        if (s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U'
            || s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
            for (j = i; s[j]; j++) s[j] = s[j+1];
            i--;
        }
    }
}

//3 inorder (left, visit, right)
int dumpAbinAux (ABin a, int v[], int N, int i) {
    if (a == NULL) return i;
    else {
        i = dumpAbinAux(a->esq, v, N, i);
        if (i != N) v[i++] = a ->valor;
        i = dumpAbinAux(a->dir, v, N, i);
    }
    return i;
}

int dumpAbin (ABin a, int *v, int N) {
    return dumpAbinAux(a, v, N, 0);
}

//PosOrder (visit, left, right)
int dumpAbinIdx2 (ABin a, int v[], int N, int i) {
    int esq, dir;
    if (a == NULL || i == N) return 0;
    v[i] = a->valor;
    esq = dumpAbinIdx2(a->esq, v, N, i + 1);
    dir = dumpAbinIdx2(a->dir, v, N, i + 1 + esq);
    return esq + dir + 1;
}

int dumpAbin2 (ABin a, int v[], int N) {
    return dumpAbinIdx2(a, v, N, 0);
}

//4
int lookupAB(ABin a, int x){
    if (!a) return 0;
    else {
        while(a){
            if (a->valor == x){
                return 1;
            } else if (x < a->valor) {
                a = a->esq;
            } else {
                a = a->dir;
            }
        }
    }
    return 0;
}

//versão recursiva
int lookupABRec(ABin a, int x) {
    if (!a) return 0;
    else {
        if (a->valor == x) return 1;
        if (x < a->valor) lookupABRec(a->esq, x);
        if (x > a->valor) lookupABRec(a->dir, x);
    }
}
//Parte B
//creating new node
Hist creatNode(char* p, int cont){
        Hist new = malloc(sizeof(Nodo));
        if (new){
        new->pal = p;
        new->cont = cont;
        new->prox = NULL;
    }
    return new;
}

Hist acrescentaInicio (Hist h, char *palavra){
    Hist aux = malloc(sizeof (Nodo));
    //2. Copiar informação para a nova célula;
    aux->pal = strdup(palavra);
    aux->cont = 1;
    //3. Unir a célula à lista
    aux->prox = h;
    return aux;
}

//inserção ordenada (assumimos que a lista está ordenada)
//Acesso ordenado
Hist acrescentaLexico(Hist *h, char *pal){
    if (!h || (strcmp(pal,(*h)->pal) < 0)) {
        return acrescentaInicio((*h),pal);
    } else if ((strcmp(pal,(*h)->pal) == 0)) {
        (*h)->cont++;
        return (*h);
    } else {
        (*h)->prox = acrescentaLexico(&(*h)->prox,pal);
        return (*h);
    }
}

int inc(Hist *h, char* pal) {
    if (!pal) {
        printf("Palavra inexistente!\n");
        return 0;
    }

    if (!h || (strcmp(pal,(*h)->pal) < 0)) {
        (*h) = acrescentaInicio((*h),pal);
        return 1;
    } else if ((strcmp(pal,(*h)->pal) == 0)) {
        (*h)->cont++;
        return 1;
    } else {
        (*h)->prox = acrescentaLexico(&(*h)->prox,pal);
        return 1;
    }
}

//2
char* remMaisFreq(Hist *h, int* count){
    if (!(*h)) return NULL;

    char * maisFreq = NULL;
    int max_occ = 0;

    while((*h)){
        if ((*h)->cont > max_occ) {
            max_occ = (*h)->cont;
            *count = max_occ;
            maisFreq = (*h)->pal;
        }
        (*h) = (*h)->prox;
    }
    return maisFreq;
}

//3
char* convert(char* word){
    int i,j;
    for(i=0; word[i];i++){
        if (isalpha(word[i]) == 0){
            for(j = i; word[j];j++) word[j] = (word[j+1]);
            i--;
        }
    }

    for(i=0; word[i];i++){
        word[i] = toupper(word[i]);
    }
    return word;
}

//main de teste
int FakeMain(){
    char dest[20];
    printf("%s\n", my_strcpy(dest,"Diogo Rebelo"));
    my_strnoV(dest);
    printf("%s\n", dest);
    return 0;
}

//última pergunta
int compare_string(char *s, char *p) {
    int i, j;
    i = j = 0;
    while (s[i] && p[j]) {
        if (!isalpha(s[i])) {
            i++;
            continue;
        }
        if (!isalpha(p[j])) {
            j++;
            continue;
        }
        if(toupper(s[i++]) != toupper(p[j++])) return 0;
    }
    return !s[i] && !p[j];
}

//Inserir uma palavra na lista
void insert(Hist * h, char * word) {
    //se o seu comprimento for <= 3 a palavra não é adicionada
    if(strlen(word) <= 3) return;
    //enquanto a lista não for nula e a palavra do nodo em questão for diferente da dada
    //avançamos na lista
    while(*h && !compare_string(word,(*h)->pal)) h = &((*h)->prox);

    //se a palavra dada for igual, incrementamos o seu count
    if(*h) (*h)->count++;
    //se a palavra não está na lista, vamos adiciona-la
    else {
        Hist new = malloc(sizeof(Nodo));
        if (new != NULL) {
            new->count = 0;
            new->pal = strdup(word);
            new->prox = NULL;
            *h = new;
        }
    }
}


Hist *readlines() {
    Hist* h;
    char *line;
    size_t size = 256;
    while (getline(&line, &size, stdin)) {
        while (line) {
            word = strsep(&line, " ");
            insert(h,word);
        }
    }
    return h;
}

void print10() {
    Hist *h = readlines();
    for(int i = 0; i < 10; i++) puts(remMaisFreq(h,NULL));
}
