#define MAXMS 1001
#define MAXH 100
#define SIZE 1009
#define STATUS_FREE 0
#define STATUS_USED 1
#define STATUS_DELETED 2
#define RIGHT 1
#define LEFT -1
#define BAL 0
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//ESTRUTURAS DE DADOS

//lista ligada de inteiros
typedef struct listaI {
    int valor;
    struct listaI * prox;
} *LInt;


//mais uma forma de hash com chaining e open address
typedef struct lista {
    int valor;
    struct lista * prox;
} *HashChain[SIZE];

typedef struct cel{
    int estado;
    int valor;
} HashOpen[SIZE];


//hash dinâmica com open addressing e linear probing
typedef struct celula {
    int key;
    //informação genérica, não com lista ligada! (open addressing é sem chaining)
    void* info;
    int estado; //Livre/Ocupado/Apagado
} Celula;

typedef struct shash {
    int tamanho, ocupados, apagados;
    Celula *Tabela;
} *THash;


//hash dinâmica com colisão por open addressing
//cada entrada e a tabela depois
typedef struct entryO {
    int status;
    char* key;
    void* info;
} EntryOAdd;

typedef struct hashA{
    int size;
    int used;
    EntryOAdd *table;
} *HashTableOAddr;


//hash dinâmica com colisão por chaining (closed addressing)
typedef struct entryC {
    char key[10];
    void *info;
    struct entryC *next;
} EntryChain;

typedef struct hashT{
    int hashsize;
    EntryChain *table;
} *HashTableChain;


//AVL com fator de balanço
typedef struct avlnode{
    int value, balance;
    struct avlnode *esq, *dir;
} *AVL;


//AVL de inteiros (Árvores Binárias de Procura)
typedef struct nodo *ABPInt;
struct nodo{
    int valor;
    ABPInt esq, dir;
};


// AVL com a altura de cada nodo
typedef struct nodoA {
    int valor;
    int altura;
    struct nodoA *esq, *dir;
}*AVLa;


// Conjuntos de Inteiros
// [conjunto1 -> conjunto2 -> etc]
// [[1,2,5,...; 4,5,3,...; ...]
typedef struct set {
    int values[1001];
    struct set *next;
}*Set;

//Multiconjunto de inteiros
/* Index: 0  1  2  3  ...  1000
 * Valor: 4  5  2  1  ...  3
 * Conjunto:
 * { 0,0,0,0,1,1,1,1,1,2,2,3,...,1000,1000,1000}
 */
typedef int MSetInt[MAXMS];


//hash com listas ligadas (chaining)
typedef struct no{
    char matricula[6];
    struct no *next;
} No;

typedef No* Tabela[SIZE];


//com arrays dinâmicos
typedef struct mHeapD {
    int size;
    int used;
    int *values;
} *MinHeapD;


//com arrays estáticos
typedef struct mHeap {
    int size;
    int heap [MAXH];
    } *MinHeap;

//com arrays estáticos e o campo used
typedef struct mHeapU {
    int size;
    int used;
    int values [MAXH];
} *MinHeapU;

void swap(int a, int b, int v[]){
    int temp;
    temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

void bubbleUp (int v[], int i){
    int a = (i - 1)/2;
    while (v[i] < v[a] && i > 0) {
        swap(i,a,v);
        i = a;
        a = (i - 1)/2;
    }
}

void bubbleDown (int v[], int i, int N){
    int f = (2*i) + 1;
    while (f < N) {
        if (f + 1 < N && v[f + 1] < v[f])
            f = f + 1;
        if (v[f] > v[i]) break;
        swap(i, f,v);
        i = f;
        f = 2 * i + 1;
    }
}

//muda o valor da posição "pos" da Heap para "valor".
//decidi alterar o tipo que a função retorna, já que pode não ser possível mudar o valor.
int muda (MinHeap h, int pos, int valor){
    int r = 0, k = 1;
    int a = (pos - 1)/2; //antecessor
    int elemSucessor = h->heap[pos + 1];

    if (pos > h->size) r = 1;
    else {
        h->heap[pos] = valor;
        // basta verificar se é maior que o antecessor
        while (k == 1)
            if (pos > 0) {
                if (valor < h->heap[a]) {
                    swap(a, pos, h->heap);
                    k = 0;
                }
                goto suc;
            }
            else {
                suc:
                if (valor > elemSucessor || valor > elemSucessor + 1) {
                    bubbleDown(h->heap, pos, h->size);
                    k = 0;
                }
            }
    }
    return r;
}

// calcula o maior elemento da heap, sem a percorrer toda
int maiorElemHeap (MinHeap h) {
    int i = 0;
    int meio = (h->size)/ 2;
    int ultimo = h->heap[h->size-1];
    int maior = ultimo;
    int indexUltimo = h->size - 1;

    //percorre no máximo até a meio da Heap
    while (i <= meio) {
        if (maior < ultimo) {
            maior = ultimo;
        }
        ultimo = h->heap[indexUltimo-1];
        i++;
    }
    return maior;
}

// ordena a minHeap, dando o array ordenado. Aloca espaço para o array resultado e destrói o anterior.
int *ordenados(MinHeapD h){
    int* new = malloc(sizeof(int)*h->used);
    int i = 0;

    //começa pelo fim.
    while (h->used > 0) {
        //aponta para o início de values, guarda o menor elemento
        new[i] = *(h->values);
        (h->values)++;
        h->used--;
        bubbleDown(h->values,i,h->used);
        i++;
    }
    //destrói a heap toda
    free(h);
    return new;
}

//testa se a heap está bem construída, com custo linear (N).
//a estratratégia é começar no fim da heap (das folhas à raíz)
int minHeapOK (MinHeapU h){
    int i = h->used - 1;
    int r = 1;
    int poi;

    while (i > 0 && r == 1){
        poi = (i-1) / 2;
        if (h->values[poi] > h->values[i])
            r = 0;
        else i--;
    }
    return r;
}

//insere um elemento na Heap, continuando correta. Aloca o dobro do espaço se estiver cheia.
void insertHeap(MinHeapD *h, int x){
    int i;
    if ((*h)->used == (*h)->size){
        //heap cheia, aloca o dobro do espaço dela
        (*h)->values = realloc((*h)->values,(*h)->size*2);
        (*h)->size *= 2;
    }
    //verificar que o elemento não existe
    for (i = (*h)->used; i >= 0 && (*h)->values[i] != x; i--);
    //saímos do ciclo porque não existe esse elemento na heap
    //podemos adicionar
    if (i < 0) {
        int index = (*h)->used;
        (*h)->values[index] = x;
        bubbleUp((*h)->values,index);
        (*h)->used++;
    }
}

// função de hash, converte uma matrícula num determinado índice da tabela de hash.
// chaining -> listas ligadas para matrículas que obtêm o mesmo índice (colisões)
int hash(const char matricula[6]) {
    int key = 1;

    for (int i = 0; i < 6; i++)
        key *= matricula[i];

    return (key % SIZE);
}

// insere a matricula na tabela, sem ter matriculas repetidas
int insert(Tabela t, char matricula[6]) {
    int r = 0;
    int p = hash(matricula);
    No *mat;

    //verificar se a matrícula existe na tabela
    //percorrer linked.list desse índice da tabela até ao fim
    for (mat = t[p]; mat != NULL && (strcmp(mat->matricula,matricula) != 0); mat = mat->next);
    // aqui temos de ver por qual das condições saiu.
    if (mat != NULL) {
        //já existe na tabela
        r = 0;
    }
    // não consta na tabela, temos de adiconar
    // mat está na últmo elemento da lista ligada
    else {
        //alocar
        mat = (No*) malloc(sizeof(struct no));
        //copiar as matriculas
        strcpy(mat->matricula,matricula);
        //ligar à lista da posição p na tebela
        mat->next = t[p];
        t[p] = mat;
        //mais 1 elemento adicionado
        r = 1;
    }
    return r;
}

// se um elemento está presente no conjunto
int presente(MSetInt s, int x){
    return (s[x] != 0);
}
// inserir elemento no conjunto de inteiros de 0 a 1000
int addMSet (MSetInt s, int x){
    int r = 0;
    if (!(presente(s,x))) {
        s[x] += 1;
        r = 1;
    }
    return r;
}

// printa a listagem ordenada no ecrã
void listagemOrdenada(MSetInt s) {
    int i;

    //aqui, no pior caso, percorremos o array completo -> T(N) = N
    for (i = 0; i < MAXMS && s[i] == 0 ; i++);
    if (i == MAXMS){
        printf("O conjunto está vazio.\n");
    }
    else {
        i = 0;
        while (i < MAXMS){
            printf("Elemento: %d (repetições: %d).\n", i, s[i]);
            i++;
        }
        printf("fim\n");
    }
}

// insere um conjunto de inteiros no array de conjuntos, no final
Set insereFinalSet (Set s, Set new){
    Set * el = &s;

    while ((*el) != NULL) {
        el = &((*el)->next);
    }
    //estamos no fim
    //*el aponta para o último elemento
    *el = malloc(sizeof (struct set));

    //temos de copiar o array
    for (int i = 0; i < 1000; i++){
        (*el)->values[i] = new->values[i];
    }
    (*el)->next = NULL;
    return s;
}

// dada uma APB determina se existem elementos da árvore entre um intervalo ([l...u])
// se não existir, retorna 0, se existir, retorna o número de inteiros entre esse intervalo
int procura (ABPInt a, int l, int u){
    int r = 0;
    if (a == NULL) r = 0;
    else {
        if (a->valor > l && a->valor < u) r++;
        // temos de procurar nas duas subárvores e não só numa delas!
        procura(a->esq,l,u);
        procura(a->dir,l,u);
    }
    return r;
}

// efetua uma rotação simples para a direita
int rdir(AVL *tptr){
    int r = 0;
    if (*tptr == NULL && (*tptr)->esq != NULL) r = -1;
    else {
        AVL *b = &((*tptr)->esq);
        (*tptr)->esq = (*b)->dir;
        (*b)->dir = *tptr;
    }
    return r;
}

// efetua uma rotação simples para a esquerda
//trocar a por b e esq por dir.
int resq(AVL *tptr){
    int r = 0;
    if (*tptr == NULL && (*tptr)->dir != NULL) r = -1;
    else {
        AVL *a = &((*tptr)->dir);
        (*tptr)->dir = (*a)->esq;
        (*a)->esq = *tptr;
    }
    return r;
}

//função de hash da tabela de listas
int hashC(int size, char key[]){
    int index = 1;
    for (int i = 0; i < 10; i++){
        index *= key[i];
    }
    return (index % size);
}

// calcula fator de carga da tabela hash
// O fator de carga é definido como: nº de pares armazenados (nºchaves) / tamanho do array a ser usado.
// Sendo assim, o fator acaba por medir o tamanho médio de cada EntryC, ou seja, o número médio de colisões.
float loadFactorC (HashTableChain t){
    int nKeys = 0;
    int nTableSize = t->hashsize;
    float fatorCarga = 0;

    if (nTableSize != 0) {
        for (int i = nTableSize; i > 0; i--){
            EntryChain * e = t->table;
            while (e != NULL){
                nKeys++;
                e = e->next;
            }
            fatorCarga = ((float) nKeys/(float) nTableSize);
        }
    }
      return fatorCarga;
}

// funcão de hash que tem em conta o rank de cada letra.
// quanto mais vez a letra aparece na palavra, menor é o rank
// a significância de cada letra está em rank[26]
int hashRank (int size, char key[]){
    int index = 1;
    int rank[26];

    for (int i = 0; key[i] != '\0'; i++){
        //admita-se: Key[0] == 'b' ; key[i] - 'a' == 'b' ; rank [1] (rank do b) rank[b(ASCII)]
        // ou seja, assim a letra em questão coincide exatamente com a posição dessa letra na tabela ASCII
        index += rank[key[i] - 'a'];
    }
    return (index % size);
}

// trata de encontrar o novo índice após colisão, através da chave
// vamos utilizar a função hash mas com apontadores
int hashPtr (int size, char* key){
    int index = 1;

    while (key!= NULL){
        index *= *key;
        key++;
    }
    return (index % size);
}

//implementar o linear probing para a posição seguinte
int find_probe(HashTableOAddr h, char *key) {
    int index = hashPtr(h->size, key);
    int count;
    int statusOfIndex = h->table[index].status;
    int comparaChaves = strcmp(h->table[index].key, key);

    //vamos avançando (count > 0) as posições que estão ocupadas e onde as chaves são diferentes
    for (count = h->size; count > 0 && statusOfIndex == STATUS_USED && !comparaChaves; count--)
        index = ((index + 1) % h->size);

    //compara chaves, ver se são diferentes
    if (!comparaChaves) {
        if (count == 0) {
            //table está cheia
            index = -1;
        } else {
            // a tabela não está cheia e encontramos uma célula deletada
            //procurar nas posições livres seguintes, com chave diferente
            int tmp = index;
            while (count > 0 && statusOfIndex == STATUS_FREE && !comparaChaves) {
                count--;
                index = (index + 1) % h->size;
            }
            if (!comparaChaves) index = tmp;
        }
    }
    return index;
}

// insere na tabela com open addressong e linear probing
int update(HashTableOAddr h, char* key, void *newInfo){
    int p = find_probe(h,key);
    int r;

    //verificar se a tabela está cheia
    if (p < 0) r = 0;
    else if (strcmp(h->table[p].key,key) == 0){
        //chave já existe
        //vamos reinserir
        h->table[p].info = newInfo;
        h->table[p].status = STATUS_USED;
        r = 1;
    }
    else {
        //nova chave a inserir
        h->table[p].status = STATUS_USED;
        h->table[p].key = key;
        h->table[p].info = newInfo;
        r = 2;
    }
    return r;
}

// duplica o tamanho da tabela
// podemos utilizar a função realloc em vez da malloc, já que esta copia o conteúdo
// temos de fazer verificação se a memória foi alocada (ptr != NULL)
// esta função precisa que se faça a função de probe (linear probing) e da função de inserção na tabela (ver acima)
void doubleTable1 (HashTableOAddr h) {
    /* Não tenho a certeza se o realloc aqui também consegue reescrever as entradas
    h->size *= 2;
    h->table = realloc(h->table,h->size);
    */

    //Usando malloc -> é preciso reecrever a tabela toda
    HashTableOAddr new;
    new->size = h->size * 2;
    new->used = h->used;
    new->table = malloc(sizeof(EntryOAdd) * new->size);

    //reescrever a tabela
    int i;
    //colocamos o status das células a FREE
    for (i = 0; i < new->size; i++)
        new->table[i].status = STATUS_FREE;

    //percorrermos a tabela original e reescrevemos
    for (i = 0; i < h->size; i++)
        if (h->table[i].status == STATUS_USED)
            update(new, h->table[i].key, h->table[i].info);
    free(h->table);

    //mudar os apontadores, porque não estamos a retornar uma tabela nova
    // mas sim a reescrever
    h->size = new->size;
    h->table = new->table;
}

//inicializa a hashtable, com listas vazias em cada entrada
HashTableChain newTABLE (int hashsize) {
    HashTableChain new = malloc(sizeof(HashTableChain));
    new->hashsize = hashsize;
    new->table = malloc(sizeof(EntryChain) * hashsize);

    EntryChain * it;
    for (it = new->table; it != NULL; it = it->next)
       it = NULL;
    return new;
}

// calcula a altura de uma árvore em T(N)=log(N)
int alturaR (AVL a) {
    int size;
    if (a == NULL) size = 0;
    else {
        int aL = alturaR(a->esq);
        int aR = alturaR(a->dir);
        aL > aR ? (size = aL) : (size = aR);
        size = size + 1;
    }
    return size;
}

// para o caso de estar balanceada, ainda é mais fácil
int alturaB (AVL a) {
    int size = 0;
    if (a != NULL) {
        size++;
        switch (a->balance) {
            case RIGHT:
                alturaB(a->dir);
                break;
            case LEFT:
                alturaB(a->esq);
                break;
            default:
                alturaB(a->dir);
        }
    }
    return size;
}

// efetua rotação para a esquerda de uma AVL com a altura de cada árvore
// atualizar o campo altura!
void rotateLeftWithHeight (AVLa b){
    if (b != NULL && b->dir != NULL){
        //rodar
        AVLa a = b->dir;
        b->dir = a->esq;
        a->esq = b;
        //alterar alturas
        //podemos utilizar a função que calcula a altura de uma árvore
        //que fizemos atrás
        //fiz cast porque a função foi feita para AVL, mas numa situação normal, não era necessário
        a->altura = alturaR((AVL) a);
        b->altura = alturaR((AVL) b);
    }
}

//remove as células apagadas da tabela hash
//garbage collection
//a ideia é criar uma nova tabela, com os elementos apagados
int hashI (int key, int hashSize){
    return (key % hashSize);
}

//podiamos utilizar a função find_probe
void remApagaddos(THash h) {
    Celula *new = malloc(sizeof(Celula) * h->tamanho);
    int i, p, t, count, ocupados = 0;
    //colocar todos os índices livres
    for (i = 0; i < h->tamanho; i++)
        new[i].estado = STATUS_FREE;

    for (i = 0; i < h->tamanho; i++) {
        if (h->Tabela[i].estado == STATUS_USED) {
            p = hashI(h->Tabela[i].key, h->tamanho);
            t = h->tamanho;
        }
        while (t > 0 && new[i].estado == STATUS_USED) {
            p = (p + 1) % h->tamanho;
            t--;
        }
        if (new[i].estado == STATUS_USED) {
            new[i].key = h->Tabela[i].key;
            new[i].info = h->Tabela[i].info;
            new[i].estado = STATUS_USED;
            ocupados++;
        }
    }
    free(h->Tabela);
    h->Tabela = new;
    h->apagados = 0;
    h->ocupados = ocupados;
}

//preenche a tabela nova com as chaves da primeira
//se a tabelas tivessem tamanho diferente, seria necessário realocar memória
//garantindo que as chaves a mais da tabela seriam repostas na outra.
//para além disso, como o tamanho da tabela se alterava, seria necessário
//voltar a inserir os elementos um a um, já que, alterando o tamanho da hash, altera-se
//o índice atribuído a cada elemento.
int fromChain (HashChain h1, HashOpen h2){
    int i = 0;
    int p = hashI(h1[i]->valor,SIZE);

    h2 = malloc(sizeof(struct cel)*SIZE);
    if (h2 == NULL) return -1;

    for (i = 0; i < SIZE; i++) {
        while(h1[i] != NULL){
            for (int t = p; h2[p].estado != STATUS_FREE; t++) {
                if (t >= SIZE) t = 0;
                h2[t].valor = h1[t]->valor;
                h2[t].estado = STATUS_USED;
            }
            h1[i] = h1[i]->prox;
        }
    }
    return 0;
}

//calcula o nodo da árvore mais profundo em T(N)=log(N)
AVL maisProfundo(AVL a) {
    AVL nodo = NULL;

    if (a != NULL) {
        while (a->dir != NULL && a->esq != NULL) {
            nodo = a;
            switch (a->balance) {
                case LEFT:
                    a = a->esq;
                    break;
                case RIGHT:
                    a = a->dir;
                    break;
                default:
                    a = a->dir;
            }
        }
    }
    return nodo;
}

//dada uma lista de inteiros, forma uma AVL
// em tempo linear do número de elementos da lista
//Para a condição acima ser possível a inserção na árvore deve ser na ordem pela a qual os elementos surgem na lista
//podemos criar uma função de inserção e chamar para cada elemento da lista
AVL fromList (LInt l, int n){

    if (n <= 0) return NULL;

    //constroi a subárvore da esquerda recursivamente
    AVL left = fromList(l,n/2);

    //aloca memória para a nova raíz, liga essa árvore à raíz
    AVL root = malloc(sizeof(struct avlnode));
    root->esq = left;

    //atualiza o ponteiro da lista ligada
    l = l->prox;

    //constroi a subárvore da direita recursivamente, liga-a à raíz
    //#Nodos(RightSubTree) = #TotalNodes - #Nodos(LeftSubTree) - 1
    //Para Raíz : n - n/2 - 1
    root->dir = fromList(l,n-n/2-1);
    return root;
}


//Função Principal (usei apenas para testar)
int main() {
/*
    MinHeap h = malloc(sizeof(struct mHeap));
    h->size = 5;
    h->heap[0] = 5;
    h->heap[1] = 8;
    h->heap[2] = 6;
    h->heap[3] = 10;
    h->heap[4] = 12;

    //muda(h,0,9);
    //muda(h,1,9);

    //printf("%d\n", maiorElemHeap(h));

    for (int i = 0; i < h->size; i++)
        printf("%d\n", h->heap[i]);
    printf("\n");
*/

    /*
    MinHeapD hd = malloc(sizeof(struct mHeapD));
    hd->values = malloc(sizeof(int) * 5);
    hd->size = 5;
    hd->used = 5;
    hd->values[0] = 5;
    hd->values[1] = 8;
    hd->values[2] = 6;
    hd->values[3] = 10;
    hd->values[4] = 12;

    printf("Array da Heap Original:\n");
    for (int i = 0; i < hd->used; i++)
        printf("array[%d] = %d\n", i, hd->values[i]);
    printf("\n");

    int *ordenado = ordenados(hd);
    printf("Array Ordenado:\n");
    for (int l = 0; l < 5; l++)
        printf("array[%d] = %d\n", l, ordenado[l]);
    printf("\n");

    insertHeap(&hd,1);
    insertHeap(&hd,7);
    insertHeap(&hd,4);
    insertHeap(&hd, 1); //ele não deve adicionar, porque já está na Heap
    for (int l = 0; l < hd->used; l++)
        printf("array[%d] = %d\n", l, hd->values[l]);
    printf("\n");
     */
    return 0;
}