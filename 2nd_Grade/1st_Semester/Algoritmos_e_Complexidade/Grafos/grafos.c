#define NV 6 //número de vértices -> alterar conforme o pretendido
#define NE 0 // peso da aresta que não existe
#define NEd 20 //número de arestas
#define BRANCO   0 // não visitado
#define CINZENTO 1 // em visita
#define PRETO    2 // visitado
#define INFINITY 9999
#define VERDE    0
#define AZUL     1
#include "estruturas.c"
#include <stdlib.h>

//estrutura para a representação da Orla
struct fringe{
    int size;
    int edges[NV];
};
typedef struct fringe * Fringe;

//grafo de inteiros representado com matriz de adjacência
typedef int GraphMat[NV][NV]

//grafo de inteiros representado por lista de adjacência
typedef struct edge{
    int dest;
    int cost;
    struct edge * next;
} * EList;
typedef EList GraphList [NV];

//grafo de inteiros representado por vetores de adjacência
typedef struct edgeV {
    int dest;
    int cost;
} EdgeV;
typedef struct {
    int vertices [NV+1];
    EdgeV edges[NEd];
} GraphVet;

//implementação de uma stack
typedef struct stack {
    int values[NV];
    int sp;
} Stack;

//determinar o peso de uma aresta (matriz de adj)
//T(N) = 1, tempo constante
int edgeWMat(GraphMat gm, int o , int d, int *w){
    *w = gm[o][d];
    return (*w != NE);
}

//determinar o peso de uma aresta (lista de adj)
//Pior Caso: T(N) = O(V)
//Melhor Caso: T(N) = 1, tempo constante
int edgeWList(GraphList gl, int o, int d, int *w){
    EList it;
    int found = 0;
    for (it = gl[o]; (it != NULL) && !found; it = it->next){
        found = (it->dest == d);
    }
    if (found) *w = it->cost;

    return found;
}

int edgeWVet (GraphVet gv, int o, int d, int *w){
    int k;
    int found = 0;
    for (k = gv.vertices[o]; (k < gv.vertices[o+1]) && !found; k++){
        found = (gv.edges[k].dest == d);
    }
    if (found) *w = gv.edges[k].cost;

    return found;
}

//grau de entrada e saída de um grafo
//T(N) = 0(V)
int indegreeMat(GraphMat gm, int v){
    int grau = 0;

    for (int i = 0; i < NV; i ++){
        if (gm[i][v] != NE) grau++;
    }

    return grau;
}

//T(N) = 0(V)
int outdegreeMat(GraphMat gm, int v){
    int grau = 0;

    for (int i = 0; i < NV; i ++){
       if (gm[v][i] != NE) grau++;
    }

    return grau;
}

//T(N) <= 0(V+E), pior que matrizes
int indegreeList(GraphList gl, int v){
    int grau = 0;
    EList it;

    for (i = 0; i < NV; i++){
        for (it = gl[i]; it != NULL; it = it->next){
            if (it->dest == v) grau++;
        }
    }

    return grau;
}

//T(N) <= O(V), melhor que matrizes
int outdegreeMat(GraphList gl, int v){
    int grau = 0;
    EList it;

    for (it = g[v]; it != NULL; it = it->next)
        grau++

    return grau;
}

int indegreeVet(GraphVet gv, int v){
    int grau = 0;
    EList it;

    for (i=0; i < NEd; i++)
        if (gv->edges[i].dest == v) grau++;
    return grau;
}

int outdegreeVet (GraphVet *gv, int v){
    int grau = 0;
    return (gv->vertices[v+1] - g->vertices[v]);
}

//converter matriz de adjacências para lista de adjacências
void mat2list(GraphMat gm, GraphList gl){
    int i,j;
    EList tmp;
    for (i = 0; i <NV; i++){
        //iniciar lista
        gl[i] = NULL;
        for (j = NV-1; j >= 0; j--){
            if (gm[i][j] != NE){
                //aresta existe -> adicionar à cabeça
                //porque estamos a iterar de trás!
                tmp = malloc(sizeof(struct edge));
                tmp->dest = j;
                tmp->cost = gm[i][j];
                // tmp -> gl -> tmp
                tmp->next = gl[i];
                gl[i] = tmp;
            }
        }
    }
}

//converter lista de adjacências para matriz de adjacências
void list2mat (GraphList gl, GraphMat gm) {
    int i, j;
    EList pt;

    //inicializar tudo a 0
    for (i = 0; i < NV; i++)
        for (j = 0; j < NV; j++)
            gm[i][j] = 0; //NE

    //converter
    for (i = 0; i < NV; i++)
        for (pt = gl[i]; pt != NULL; pt = pt->next)
            gm[i][pt->dest] = pt->cost;
}

//contar o número de arestas de um grafo em LA
int nArestasL (GraphList gl){
    int r = 0, i;
    EList it;

    for (i = 0; i < NV; i++)
        for (it = g[i]; it != NULL; it = it->next)
            r++;

    return r;
}

//contar o número de arestas de um grafo em MA
int nArestasM (GraphMat gm){
    int r = 0, i, j;

    for (i = 0; i < NV; i++)
        for (j = 0; j < NV; j++)
            if (gm[i][j] != NE) r++;

    return r;
}

//converte lista de adjacências para vector de adjacências
void list2vet(GraphList gl, GraphVet gv){
    int i, k;
    EList it;

    for (i=k=0; i < NV; i++){
        gv->vertices[i] = k;
        for (it = gl[i]; it != NULL; it = it->next){
            gv.edges[k].dest = it->dest;
            gv.edges[k].cost = it->cost;
            k++
        }
    }
    gv.vertices[i] = k;
}

//converte vetor de adjacências para lista de adjacências
void vet2list (GraphVet gv, GraphList gl){
    int i,k;
    EList tmp;

    for (i = 0; i < NV; i++){
        gl[i] = NULL;
        for (k = gv.vertices[i+1]-1; k >= gv.vertices[i]; k--){
            tmp = malloc(sizeof(struct edge));
            tmp->dest = gv.edges[k].dest;
            tmp->cost = gv.edges[k].cost;
            tmp->next = gl[i];
            gd[i] = tmp;
        }
    }
}

//capacidade de um vértice num grafo
// T(V,E) = Ɵ(V+E)
int capL(GraphList gl, int v){
    int r = 0;
    EList it;

    //sempre que o destino da aresta é v incrementamos com o peso
    //se a origem for o vértice, retiramos
    //no final temos entradas - saídas
    for (int i = 0; i < NV; i++)
        for (it = gl[i]; it != NULL && (it->dest == v) ; it = it->next)
            r += it->cost;
         if (it->dest != v && (i == v)) r -= it->cost;

    return r;
}

// T(V,E) = Ɵ(V)
//capacidade de um vértice num grafo (peso das saídas - peso das entradas ou acc - saidas + entradas)
int capM(GraphList gm, int v){
    int r = 0;

    for (int i = 0; i < NV; i++)
        r +=  (gm[i][v] - gm[v][i]);

    return r;
}


//capacidade máxima de um grafo
//usando a função anterior
int maxCapL(GraphList gl){
    int i, m, cap[NV] = {0};
    EList pt;

    for (i = 0; i < NV; i++)
        for (pt = gl[i]; pt != NULL; pt = pt->next) {
            cap[i] -= pt->cost;
            cap[pt->dest] += pt->cost;
        }

    //procura do vértice de maior capacidade
    m = 0;
    for (i = 1; i < NV; i++)
        if (cap[i] > cap[m]) m = i;

    return m;
}

// Calcula o vértice com maior capacidade dum grafo
// T(V,E) = Ɵ(V^2)
int maxCapM (GraphMat gm) {
    int i, m, cap[NV];

    for (i = 0; i < NV; i++)
        cap[i] = capM(gm, i);

    m = 0;
    for (i = 1; i < NV; i++)
        if (cap[i] > cap[m]) m = i;

    return m;
}

//testa se o conjunto c é uma cobertura do grafo
//ou seja, se uma das extremidades das arestas pertence ao conjunto de vértices do grafo
//c é array de flags (cada índice represent um nodo e o seu conteúdo é 1 se o nodo existir ou 0 se não)
//retorna 0 se não for e 1 se for
int VCoverage (GraphList gl, int c[]){
    int result = 0;
    EList it;

    for (int i = 0; i < NV; i++){
        for (it = gl[i]; it != NULL; it = it->next){
            if (c[it->dest] == 1 || c[i] == 1) result = 1;
            else {
                result = 0;
                break;
            }
        }
    }
    return result;
}

//verifica validade da coloração do ARRAY DE CORES
//a cor do vértice tem de ser diferente da do sucessor adjacente
// T(V,E) = Ɵ(V+E)
int colorOK (GraphList gl, int cor[]) {
    r = 1;
    EList it;

    for (int i = 0; i < NV && r != 0; i++)
        for (it = gl[i]; it != NULL && r != 0; it = it->next)
            if (cor[i] == cor[it->dest]) r = 0;

    return r;
}

//testa se uma ordenação v[] é uma ordenação topológica de um grafo orientado e acíclico
//é ordenação topológica se
//v contém os NV vértices sem repetições
//T(N) = O(V+E)
//verifica se pertence ao array, dando a posição onde o encontrou, ou -1 se não encontrou
int pertence(int v[], int N, int elem) {
    for (int i = 0; i < N && v[i] != elem; i ++);
    if (v[i] == elem) return i;
    return -1;
}

int testTopologica (GraphList gl, int v[]) {
    int result = 1;
    int sizeV = sizeof v / sizeof(int);
    EList it;

    for (int i = 0; i < NV; i++)
        for (it = gl[i]; it != NULL; it = it->next)
            if (pertence(v, sizeV, i) > pertence(v, sizeV, it->dest))
                return 0;

    return result;
}

//determinar quantos vértices são alcancáveis a partir de um vértice
//funciona para grafos com e sem ciclos
//utiliza estratégia em profundidade (procura DFS)
//estratégia recursiva
int DFRec(GraphList gl, int o, v[], int p[]) {
    int found = 1;
    v[o] = 1;

    for (EList it = gl[o]; it != NULL; it = it->next) {
        if (v[it->dest] == 0) {
            //it.dest é pai do vértice o
            p[it->dest] = o
            found += travessiaDF(gl, it->dest, v,p);
        }
    }

    return found;
}

//forma a árvore com os caminhos utilizados na procura
int travessiaDFTree (GraphList gl, int o, int p[]){
    int visitados[NV];
    for (int i = 0; i < NV; i++) {
        visitados[i] = 0;
        p[i] = -2;
    }
    p[o] = -1;
    return (DFRec(gl,o,visitados,p));
}

//vértices alcançaveis a partir de or
//com matriz de adj

//auxíliar
int DFS(GraphMat g, int or, int vis[], int n){
    if(vir[or] != 0) return 0;
    vis[or] = 1; int a = 1;
    for(int i = 0; i < n; i++){
        if(g[or][i]!=0)
            a+=DFS(g,i,vis,n);
    }
    return a;
}
//vértices alcançaveis a partir de or
int count_Reachable(GraphMat g, int or, int n){
    int vis[n] = {0};
    return DFS(g,or,vis,n) - 1;
}


//A função anterior pode ser utilizada para determinar componentes ligadas
//Componentes ligadas é quando temos pelo menos um caminho entre qualquer par de vértices
//Uma componente ligada é um subgrafo do grafo original
//determirna o tamanho (número de vértices) da maior componente ligada
int maiorComponente(GraphList gl){
    int i, c, max = 0;
    int visitados[NV] = {0};

    for (i = 0; i < NV; i++){
        if (visitados[i] == 0){
            c = DFRec(gl,i,visitados);
            if (c>max) max = c;
        }
    }

    return max;
}

//grafo bipartido: conseguimos separar os vértices em dois conjuntos,
//onde todas as arestas possuem uma extremidade num conjunto e a outra no outro.
//testa se o grafo não orientado é bipartido, usando cores
int testBiPartite (GraphList gl, int v1[]) {
    int v, inicio, fim, r = 1;
    int orla[NV], cor[NV];
    EList it;
    for(i = 0; i < NV; i++) cor[i] = BRANCO; // nao visitado
    inicio = fim = 0;
    orla[fim++] = 0; // é o mesmo que: orla[fim] = 0; fim++;
    v1[0] = AZUL;
    cor[0] = CINZENTO;
    while (inicio != fim && r) {
        v = orla[inicio++];
        //muda para visitado
        cor[v] = PRETO;
        for (it = gl[v]; it != NULL && r; it = it->next) {
            //nodo não visitado
            if (cor[it->dest] == BRANCO) {
                if (v1[v] == VERDE) v1[it->dest] = AZUL;
                else  v1[it->dest] = VERDE;
                orla[fim++] = it->dest;
                cor[it->dest] = CINZENTO;
            }
            //nodo visitado -> seguinte -> sair do ciclo
            else if (v1[v] == v1[it->dest]) r = 0;
        }
    }
    return r;
}

//estratégia de procura em largura, por níveis
//nao precisa de recursividade porque tem uma fila!
int travessiaBF (GraphList gl, int o, int ant[]){
    int visitados[NV];
    int q[NV];
    int fim, inicio, i;
    int count = 0;
    EList it;


    fim = inicio = 0;  //emptyQueue
    q[fim++] = o; //enqueue do o
    visitados[o] = 1;

    //enquanto a file nao esta vazia
    while (inicio < fim){
        o = q[inicio++]; //dequeue do primeiro elemento da fila
        count++; //incrementar contador
        for (it = g[o]; it != NULL; it = it->next){
            if (visitados[it->dest] == 0){
                q[fim++] = it->dest; //enqueue desse nodo adjacente
            }
        }
    }

    return count;
}

//mesma funçao, mas construindo a arvore com a sequencia dos nodos
//Propriedades: Exaustivo, Terminaçao, Fila garante ordenaçao topologica e caminhos mais curtos
//em termos do numero de vertices do caminho (da os caminhos com menos nodos), e
//nao tem em consideraçao o peso.
int travessiaBFTree (GraphList gl, int o, ant[]){
    int q[NV];
    int inicio, fim, i;
    int count;
    EList it;

    //iniciar o array de antecessores com -2
    for (i = 0; i < NV; i++){
        ant[i] = -2;
    }

    inicio=fim=0;
    q[fim++] = o;
    ant[o] = -1;
    while (inicio < fim){
        o = q[inicio++]; //remover o vertice da fila
        count++;
        for (it = g[o]; it != NULL; it = it->next){
            //acrescenta-se os sucessores a fila
            if (ant[it->dest] = -2){
                ant[it->dest] = o;
                q[fim++] = it->dest;
            }
        }
    }
    return count;
}

//algoritmo de khan
//ordenaçao topologica com base numa fila e grau de entrada e cada vertice
//retorna o numero de vertices visitados, se esse numero for maior que o numero
//de vertices presentes no grafo, entao o grafo tem ciclos.
// T(N) = Ɵ(V+E)
int khanTS (GraphList gl, int seq[]){
    int inicio, fim;
    int i;
    EList it;

    //inicializar array seq
    for (i = 0; i < NV; i++){
        seq[i] = -1;
    }
    //calcular o grau de entrada de cada vertice
    for (i = 0; i < NV; i++){
        for (it = gl[i]; it != NULL; it = it->next){
           seq[it->dest]++; //incrementar o destino (i entra para it->dest)
        }
    }

    //inicializar a fila e adicionar o elemento com indegree = 0
    //usa-se seq como a nossa fila
    inicio = fim = 0;
    for (i = 0; i < NV; i++){
        if (seq[i] == 0) {
            seq[fim++] = i; //enqueue -> adicionar ao último índice do array
        }
    }

    //construçao da ordenaçao
    while (inicio < fim){
        i = seq[inicio++]; // dequeue -> incrementar o inicio
        for (it = gl[i]; it != NULL; it = it->next){
            seq[it->dest]--; //indegree decrementa dos adjacentes
            if (seq[it->dest] == 0)
                seq[fim++] = it->dest; //enqueue
        }
    }
    return inicio;
}

//função que determina se é acíclico
// Determina se um grafo é acíclico
// T(N) = Ɵ(V+E)
int isAcyclic (GraphList gl) {
    int seq[NV];
    return ((khanTS(gl, seq) != NV);
}

//algoritmo de Tarjan para ordenação topológica em profundida
//segue uma estratégia DFS
int tarjanTS (GraphList gl, int seq[]) {
    int color[NV];
    int v,j,t,r;

    //inicializar o array de cores/estados, com todos a NÃO VISITADOS (WHITE)
    for (v = 0; v < NV; v++){
        color[v] = BRANCO;
    }

    //chamar a função TopSort para cada vértice
    r=1; t=0; //t=tamanho de seq (vértices colocados no array)
    for (v = 0; v < NV; v++){
        t += dfirstTopSort(gl,v,color,&r,seq+t);
    }

    //inverter a sequência produzida pela função anterior
    //vai acabar por ordenar por ordem crescente
    for (v = 0, j = t; v < j; v++,j--){
        swap(seq[v],seq[j],seq);
    }
    return r;
}

//retorna o número de elementos colocaodos em seq[], vértices visitados
int dfirstTopSort (GraphList gl, int o, int color[], int * success, int seq[]){
    int t;
    EList it;
    //colocar nodo EM VISITA
    color[o] = CINZENTO;

    //APLICAR FUNÇÃO AOS SUCESSORES
    t=0;
    for (it = g[o]; it!=NULL; it = it->next){
        if (color[it->dest] == BRANCO)
            t += dfirstTopSort(gl,it->dest,color,success,seq+t);
        else if (color[it->dest] == CINZENTO)
            *success = 0;
    }

    //adicionar o vértice à sequência
    seq[t++] = o; //já aplicamos a procura ao vértice o

    //marcá-lo como visitado
    color[0] = PRETO;
    return t;
}

//marcar vértices de um grafo de acordo com a sua componente fortemente ligada
//usar o array comp
//se os vértices 1 e 2, 3 e 4 pertencerem à mesma componente, tem-se comp[1] = comp[2] = 0,
//comp[3] = comp[4] = 1, e assim sucessivamente

//função auxíliar para travessia em profundidade
void df (GraphList gl, int o, int comp[], int c){
    EList it;

    //marca no array de componentes, no seu índice, com o número c, dado à função
    comp[o] = c;

    //percorremos, a partir desse nodo o, os seus sucessores
    for (it = gl[o]; it != NULL; it = it->next){
        //vemos no array de componentes se esses sucessores estão marcados com -1
        if (comp[it->dest] == -1)
            df(gl, it->dest,comp,c);
    }
}

void componentes(GraphList gl, int comp[], int n) {
    int i, c = 0;

    //inicializamos o array comp com -1
    for (i = 0; i < n; i++){
        comp[i] = -1;
    }

    for (i = 0; i < n; i++){
        if (comp[i] == -1) {
            df(gl, i, comp, c);
            c++;
        }
    }
}

//calcula o peso de um caminho presente no array passado como argumento
int pesoC (GraphMat gm, int v[], int k){
    int cost = 0;

    for (int i = 0; i < k - 1; i++){
       int a = v[i];
       int b = v[1+1];
       if (gm[a][b] != NE) cost += gm[a][b];
       else return -1;
    }
    return cost;
}

//versão alternativa da função anterior
int pesoCv2 (GraphMat gm, int v[], int k) {
    int i = 0;
    while (i < k-1){
        int pesoNodoI = g[i][v[i]];
        int dif = v[i+1] + v[i];
        if (pesoNodoI == NE){
            cost = -1;
            break;
        }
        i += dif;
    }
    return cost;
}

//função que conta o número de componentes fortemente ligadas de um grafo
//usa uma função auxíliar e seque uma abordagem em profundidade
int secRec (GraphList gl, int *tStamp, int v, int color[], int t[], int M[]) {
    EList it;
    int r = 0;
    //colocar nodo recebido EM VISITA
    color[v] = CINZENTO;
    //inicializar o M e o t
    M[v] = t[v] = *tStamp++;

    //percorrer elementos adjacentes a v
    for (it = gl[v]; it != NULL; it = it->next) {
        if (color[it->dest] != PRETO) {
            if (color[it->dest] == BRANCO)
                r += secRec(gl, tStamp, it->dest, color, t, M);
            if (M[it->dest] < M[v])
                M[v] = M[it->dest];
        }
    }

    //encontramos uma componente fortemente ligada
    //nodo visitado
    if (M[v] == t[v]) r++;
    color[v] = PRETO;

    return r;
}

int tarjanSCC (GraphList gl) {
    int color[NV], tIn[NV], mtIn[NV];
    int i;
    int tStamp = 0;
    int r = 0;

    //inicializar array de visitados
    for (i = 0; i < NV; i++)
        color[i] = BRANCO;

    //aplicar recursivamente a função auxíliar a cada vértice
    for (i = 0; i < NV; i++) {
        if (color[i] == BRANCO)
            r += secRec(gl, &tStamp, i, color, tIn, mtIn);
    }
    return r;
}

//função que verifica se um grafo é fortemente ligado
//se existir apenas uma componente, então o grafo é SC

//INIT na stack
void initStack (Stack *s){
    s->sp = 0;
}

//EMPTY na stack
int emptyStack (Stack *s){
    return (s->sp == 0);
}

//PUSH na stack
//retorna 1 se não for possível e 0 se for
int push (Stack * s, int x){
    int r = 0;
    if(s->sp == NV) r = 1;
    else
        s->values[s->sp++] = x;
    return r;
}

//POP na stack
int pop (Stack *s, int *x){
    int r=0;
    if (s->sp == 0) r=1;
    else
        *x = s->values[--s->sp];
    return r;
}

//verificar se um elemento pertence à stack
int isInStack (Stack *s, int x){
    int i = 0;
    if (!emptyStack(s)){
        while (s->sp){
            if (s->values[s->sp] == x){
                return 1;
            }
            i++;
        }
    }
    return 0;
}

//determinar se um grafo é fortemente ligado
//um grafo é fortemente ligado se para cada par
//de vértices há um caminho entre eles
//Forma 1: usar DFS para cada vértice, verificando se todos os vértices são visitados
//Forma 2: usar Floyd-Warsharll
//Forma 3: usar Tarjan (Gabow's variation)
//função recursiva para a de baixo
int secRecStack (GraphList gl, int *tStamp, int i, int color[], int t[], int M[], Stack *stack, int comp[], int count) {
    EList it;
    int r = 0;

//colocar nodo recebido EM VISITA
    color[v] = CINZENTO;

//inicializar o M e o t
    M[v] = t[v] = *tStamp++;

//dar push do vértice na stack
    push(stack);

//percorrer elementos adjacentes a v
    for (it = gl[i]; it != NULL; it = it->next) {
        if (color[it->dest] != PRETO) {
            if (color[it->dest] == BRANCO)
                r += secRecStack(gl, tStamp, it->dest, color, t, M,stack,comp, count);
            else if (isInStack(stack, it->dest)) {
                if (M[it->dest] < M[i]) M[i] = M[it->dest];
            }
        }
    }

//encontramos uma componente fortemente ligada
//nodo visitado
    if (M[i] == t[i]) r++;
    color[i] = PRETO;
    comp[count++] = stack->sp;
    return r;
}

int tarjanSCCTest (GraphList gl){
    int color[NV], tIn[NV], mtIn[NV], comp[NV];
    int i;
    int tStamp = 0;
    int r = 0;
    Stack * stack;
    int count = 0;

    //inicializar stack
    initStack(stack);

    //inicializar array de visitados e comp
    for (i=0; i < NV; i++) {
        color[i] = BRANCO;
        comp[i] = 0;
    }

    //aplicar recursivamente a função auxíliar a cada vértice
    for(i=0; i < NV; i++){
        if (color[i] == BRANCO)
            r += secRecStack (gl, &tStamp, i, color, tIn, mtIn, stack,comp,count);
    }
    return r;
}

//determinar se um grafo é fortemente ligado, com estratégia mais simples
//utilizando uma abordagem em profundidade
int travessiaDFS(GraphList gl, int v, int color[]){
    EList it;
    color[v] = PRETO;
    for (it = gl[v]; it != NULL; it = it->next){
        if (color[it->dest] == BRANCO){
            travessiaDFS(gl,it->dest, color);
        }
    }
}

//iniciamos uma taravessia em cada nodo e verificamos se todos os nodos adjacentes são visitados
int testSCC(GraphList gl){
    int color[NV] = {BRANCO};
    int i;

    for (i = 0; i < NV; i++) {
        travessiaDFS(gl, i, color);
        for (i = 0; i < NV; i++)
            if (color[i] == BRANCO)
                return 0;
    }
    return 1;
}

//para um grafo representado por matriz, podemos obter o fecho transitivo e verificar se a matrix tem uma diagonal com 0?
//fecho transitivo de um grafo
void tclosure (GraphList gl, GraphMat gp){
    int v, i;
    int p[] = {0}; //não é usado
    for (v=0; v < NV; v++){
        for(i=0; i < NV; i++)
            gp[v][i] = 0;
        //o último argumento pode ser retirado
        DFRec(gl,v,gp[v],p);
    }
}

//Algoritmo de Warshall
//Cálculo da conectividade de um grafo não orientado
//Fecho transitivo de um grafo Não Orientado
//T(N) = O(V³)
void warshall (GraphList gl, GraphMat gm) {
    EList it;
    int u, v, x;

    //incializar gm
    for (u = 0; u < NV; u++) {
        for (v = 0; v < NV; v++) gm[u][v] = NE;
        for (it = gl[u]; it != NULL; it = it->next)
            gm[v][it->dest] = 1;
    }

    //adição de arestas
    for (x = 0; x < NV; x++)
        for (u = 0; u < NV; u++)
            for (v = 0; v < NV; v++)
                gm[u][v] = gm[u][v] || (gm[u][x] && gm[x][u]);
}

//verificar se há um caminho de comprimento <= n, entre dois nodos
//dá para todos os tipos de grafos
int haCaminho (GraphList gl, int o, int d, int n) {
    int visitados[NV], orla[NV], inicio, fim, passos = 1;
    EList it;
    for (int i = 0; i < NV; i++)
        visitados[i] = BRANCO;
    inicio = fim = 0;
    orla[fim++] = o;
    visitados[o] = CINZENTO; //o está visitado;

    if (n>0) {
        while (inicio != fim && passos <= n) {
            o = orla[inicio++];
            visitados[o] = PRETO;
            for (it = gl[o]; it != NULL; it = it->next) {
                if (it->dest == d) return 1;
                else if (visitados[it->dest] == BRANCO) {
                    visitados[it->dest] == CINZENTO;
                    orla[fim++] = it->dest;
                    passos++;
                }
            }
        }
    }
    if (passos > n) return 1;
    return 0;
}

//conjunto de funções utilitárias para a Orla
//vamos manter os vertices por ordem decrescente do seu peso
//inicializar a orla
int initFringe (Fringe f){
    f->size = 0;
    return 0;
}

//adição de novo elemento à orla
int addEdgeFringe (Fringe f, int v, int cost[]) {
    int i;
    for (i = f->size++; i > 0 && cost[f->edges[i]] < cost[v]; i--)
        f->edges[i] = f->edges[i - 1];
    f->edges[i] = v;
    return 0;
}

//atualização do peso de um vértice
int updateFringeCost (Fringe f, int v, int cost[]){
    int i;
    for (i = 0; f->edges[i] != v; i++);
    for (; i<f->size && cost[f->edges[i]] < cost[f->edges[i+1]]; i++)
        swap(i,i+1, f->edges);
    }
    return 0;
}

int getdge (Fringe f, int cost[]){
    f->size--;
    return (f->edges[f->size]);
}

//calculo da arvore geradora de custo minimo
//Algoritmo de Prim
//T(N) = O(V+E*V)
int PrimMST(GraphList gl, int cost[], int ant[]){
    int res=0;
    int v;
    int color[NV];
    int fringesize;
    EList it;
    Fringe ff, *f;
    f = &ff;

    for (v=0; v < NV; v++)
        color[v] = BRANCO;

    initFringe(f);
    fringesize = 0;
    color[v] = PRETO;
    cost[v] = 0;
    addEdgeFringe(f,v,cost);
    fringesize++;

    while (fringesize > 0){
        v = getdge(f,cost);
        fringesize--;
        res += cost[v];
        color[v] = PRETO;
        for (it = gl[v]; it != NULLL; it = it->next){
            if ((color[it->dest] == BRANCO) || (color[it->dest] == CINZENTO && cost[it->dest] > it->cost)){
                ant[it->dest] = v;
                cost[it->dest] = it->cost;
                if (color[it->dest] == BRANCO){
                    addEdgeFringe(f,it->dest,cost);
                    fringesize++;
                } else updateFringeCost(f,it->dest,cost);
            }
        }
    }
    return res;
}

//Obtém todos os caminhos mais curtos a partir de um vértice até todos os outros
//Devolve o número de vértices que visitou (desnecessário)
// Utiliza um vetor desordenado como fronteira (orla)
int dijkstraSP (GraphList g, int v, int pesos[], int ant[]) {
    int i;
    int res = 0; //número de vértices visitados
    int newcost, fringesize;
    EList pt;
    int color[NV];
    Fringe ff, *f;
    f = &ff;

    for (i = 0; i < NV; i++) color[i] = BRANCO;

    initFringe(f); fringesize = 0;
    color[v] = CINZENTO; pesos[v] = 0;
    addEdgeFringe(f, v, pesos); fringesize++; //adicionar v à orla

    while (fringesize > 0) { // enquanto a orla não estiver vazia
        v = getdge(f,pesos) //escolhe v da orla (vértice com menor custo até ao momento)
        fringesize--;
        res++;
        color[v] = PRETO; // v passa a visitado
        for (pt = g[v]; pt != NULL; pt = pt->next) {
            newcost = pesos[v] + pt->peso; //novo custo descoberto para o vértice
            if ((color[pt->dest] == BRANCO) || ((color[pt->dest] == CINZENTO) && pesos[pt->dest] > newcost)) {
                ant[pt->dest] = v;
                pesos[pt->dest] = newcost;
                if (color[pt->dest] == BRANCO) {
                    addEdgeFringe(f, pt->dest, pesos[pt->dest]); // adicionar pt->dest à orla se este ainda não foi visitado
                    fringesize++;
                } else updateFringeCost(f, pt->dest, pesos[pt->dest]); //atualizar pt->dest na orla
            }
        }
    }
    return res;
}

//Algoritmo de FloydWarshall
//utilizado para determinar o caminho mais curto entre todos os pares de vertices
//utiliza o algoritmo anterior
//em cada iteraçao do ciclo sao calculados os caminhos mais curtos em G que usam
//como nodos intermedios apens os vertices ja processados
// T(V,E) = Ɵ(V^3) -> Compensa em grafos muito densos
void floydWarshallL (GraphList g, int pesos[NV][NV]) {
    int i, j, v;
    EList pt;

    for (i = 0; i < NV; i++)
        for (j = 0; j < NV; j++)
            pesos[i][j] = 0;

    for (i = 0; i < NV; i++)
        for (pt = g[i]; pt; pt = pt->next)
            pesos[i][pt->dest] = pt->cost;

    for (v = 0; v < NV; v++)
        // para todos os antecessores de v
        for (i = 0; i < NV; i++)
            if (pesos[i][v])
                for (j = 0; j < NV; j++)
                    if (pesos[v][j])
                        if (pesos[i][j] == 0 || pesos[i][j] > pesos[i][v] + pesos[v][j])
                            pesos[i][j] = pesos[i][v] + pesos[v][j];
}

//mesmo que o anterior, mas com matriz de adjacencias
// T(V,E) = Ɵ(V^3)
void floydWarshallM (GraphMat g, int pesos[NV][NV]) {
    int i, j, v;

    for (i = 0; i < NV; i++)
        for (j = 0; j < NV; j++)
            pesos[i][j] = g[i][j];

    for (v = 0; v < NV; v++)
        for (i = 0; i < NV; i++)
            if (pesos[i][v])
                for (j = 0; j < NV; j++)
                    if (pesos[v][j])
                        if (pesos[i][j] == 0 || pesos[i][j] > pesos[i][v] + pesos[v][j])
                            pesos[i][j] = pesos[i][v] + pesos[v][j];
}

// Calcula o caminho mais longo de um grafo recorrendo à sua ordenação topológica
// grafo orientado e acíclico
// T(V,E) = Ɵ(V+E)
int longestPath (GraphList g, int ant[]) {
    int seq[NV], dist[NV], i, v, r;
    EList pt;

    khanTS(g, seq);

    for (i = 0; i < NV; ant[i++] = -1)
        dist[i] = 0;

    for (i = 0; i < NV; i++) {
        v = seq[i];
        for (pt = g[v]; pt; pt = pt->next) {
            if (dist[v] + pt->cost > dist[pt->dest]) {
                dist[pt->dest] = dist[v] + pt->cost;
                ant[pt->dest] = v;
            }
        }
    }

    r = 0;
    for (i = 1; i < NV; i++)
        if (dist[i] > dist[r]) r = i;

    return r;
}

// Calcula o caminho mais curto de um grafo recorrendo à sua ordenação topológica
// grafo orientado e acíclico
// T(V,E) = Ɵ(V+E)
int shortestPath (GraphList g, int o, int d, int ant[]) {
    int seq[NV], dist[NV], i, v, start;
    EList pt;

    khanTS(g, seq);

    for (i = 0; i < NV; ant[i++] = -1) {
        dist[i] = INFINITY;
        if (seq[i] == o) start = i;
    }

    v = INFINITY;
    dist[o] = 0;

    for (i = start; i < NV && v != d; i++) {
        v = seq[i];
        for (pt = g[v]; pt && v != d; pt = pt->next) {
            if (dist[v] + pt->cost < dist[pt->dest]) {
                dist[pt->dest] = dist[v] + pt->cost;
                ant[pt->dest] = v;
            }
        }
    }

    return dist[d];
}

//devolve o peso do arco com menor peso de um grafo
int minPeso(GraphList gl){
    int min = INFINITY;

    for (int i = 0; i < NV; i++){
        for (EList it = gl[i]; it != NULL; it = it->next){
            if (it->cost < min) min = it->cost;
        }
    }
    return min;
}

//Recebe uma árvore resultado de uma travessia (vector de pais)
//faz uma travessia preorder (raiz, esquerda, direita)
//imprime os índices correspondentes
//Grafo com NV = N e raíz árvore pai = -1
//pais[v] = pai do vértice v
void tree2Transversal (int pais[], int poi, int N) {
    int i;
    printf("%d\n", pais[poi - 1]);
    for (i = 0; i < N; i++)
        if (pais[i] == poi)
            tree2Transversal(pais, i, N);
}

//click: subconjunto de vértices onde quais dois elementos estão ligados por uma aresta
//ou seja, é verificar adjacência entre todos os pares de vértices
//testar se um conjunto de vértices de um grafo é um click

//função auxiliar que teste se dois vértices são adjacentes
int testAdjacency(GraphList gl, int o, int d){
    for (EList it = gl[o]; it != NULL; it = it->next)
        if (it->dest == d) return 1;
    return 0;
}

//vamos assumir que v não é vazio, nem tem apenas um elemento
//vamos assumir que o grafo não é nulo
//basta testar o -> d, pois d -> o existe se o anterior existir (grafo não orientado)
int testClick (GraphList gl, int v[]){
    int i,j;

    for (i=0; i < NV; i++){
        for (j = i+1; j < NV - 1; j++){
            if (testAdjacency(gl,v[i],v[j]) == 0) return 0;
        }
    }
    return 1;
}

//comprimento do caminho mais longo a partir do vértice dado
//grafo orientado e acíclico
//vamos optar por uma estratégia em largura

//precisamos de uma função que crie uma ordem topológica
void criaOT(GraphList gm, int o, int ot[NV]) {
    int color[NV];
    int inicio, fim;
    int i, it;

    for (i = 0; i < NV; i++) {
        color[i] = BRANCO;
    }

    inicio = fim = 0;
    ot[fim++] = o;
    visitados[o] = PRETO;

    while (inicio != fim) {
        o = ot[inicio++];
        for (it = 0; it < NV; it++) {
            if (gm[o][it] >= 0 && color[it] == BRANCO) {
                ot[fim++] = it;
                color[it] = PRETO;
            }
        }
    }
}

int maisLongo(GraphMat gm, int o) {
    int ot[NV], cost[NV];
    int i, v, r;
    int pt;

    criaOT(gl, o, ot);

    for (i = 0; i < NV; i++)
        cost[i] = 0;


    for (i = 0; i < NV; i++) {
        v = ot[i];
        for (pt = 0; pt < NV; pt++)
            if (gm[v][pt] > 0)
                if (cost[v] + gm[v][pt] > cost[pt])
                    cost[pt] = cost[v] + gm[v][pt];
    }

    r = 0;
    for (i = 1; i < NV; i++)
        if (cost[i] > cost[r]) r = i;

    return r;
}

//Composição de dois grafos R e S
//Grafos em matriz de adjacência
//A composição tem a aresta a->b, se
//                                 S tem a->c
//                                 R tem c->b

//podemos usar uma função que verifica se dois nodos são adjacentes
//grafo orientado e aciclico
int testAdjacencyMat (GraphMat gm, int o, int v){
    return (gm[o][v] != NE);
}

void compoe(GraphMat R, GraphMat S, GraphMat C) {
    int i, j, k;

    for (i = 0; i < NV; i++)
        for (j = 0; j < NV; j++)
            if (testAdjacencyMat(S, j, i))
                for (k = 0; k < NV; k++)
                    if (testAdjacencyMat(R, R[i], R[k]))
                        C[j][k] == 1;
}

//verifica se o array contém uma sequência válida de caminhos
//T(N) = {1,T(E)}
int valid_path(GraphList gl, int path[], int n) {
    int i, r;
    EList it;

    for (i = 0; i < n - 1 && r != 0; i++) {
        r = 0;
        for (it = gl[path[i]]; it != NULL; it = it->next)
            if (it->dest == path[i + 1]) {
                r = 1;
                it = NULL;
            }
    }

    return r;
}

//inverso de um grafo
//T(N) >= T(V+E), pois temos em qualquer dos casos que percorrer todos os vértices e arestas do grafo
//na procura das adjacências existentes
GraphList inverso (GraphList gl){
    int i;
    EList it;
    GraphList inv;

    for (i=0; i < NV; i++)
        inv[i] = NULL;

    for (i = 0; i < NV; i++) {
        for (it = gl[i]; it != NULL; it = it->next) {
            if (testAdjacency(gl,i,it->dest)) {
                EList new = malloc(sizeof (struct edge));
                new->dest = i;
                new->cost = it->cost;
                new->next = inv[it->dest];
                inv[it->dest] = new;
            }
        }
    }
    return inv;
}

// Inverte um grafo
// T(N) = Ɵ(V^2)
void reverseGraphM (GraphMat g, GraphMat r) {
    int i, j;

    for (i = 0; i < NV; i++)
        for (j = 0; j < NV; j++)
            r[i][j] = 0;

    for (i = 0; i < NV; i++)
        for (j = 0; j < NV; j++)
            if (g[i][j]) r[j][i] = g[i][j];
}


//Capacidade Total de todos os vértices do grafo
void maxCapacity(GraphList gl, int cap[]) {
    EList it;
    int i;

    for (i = 0; i < NV; i++) {
        for (it = gl[i]; it != NULL; it = it->next) {
            cap[i] -= it->cost;
            cap[it->dest] += it->cost;
        }
    }
}

//quais dos vértices alcancáveis está mais longe
//vértice alcancável mais distante
//T(V,E) = O(V^2 + V)
int maisLonge (GraphList gl, int v){
    int i, r = 0, max = v;
    int pesos[NV], pais[NV];

    for (i=0; i< NV; i++){
        pesos[i] = 0;
        pais[i] = -2;
    }

    pais[v] = -1;
    i = dijkstraSP(gl,v,pesos,pais);

    while (i){
        if (pais[r] != -2){
            i--;
            if (pesos[r] > pesos[max]) max = r;
        }
        r++;
    }
    return max;
}

//determina vértices alcançaveis a partir de um dado vértice
//retorna o número de vértices alcançaveis
//semelhante ao algortimo de dijkstra

// Travessia Breadth First (em largura)
void BFS (GraphList g, int o, int dist[]) {
    int color[NV], orla[NV]; // queue
    int inicio, fim; // inteiros para controlar a queue
    int v; // vertice em execuçao
    EList pt;

    for (v = 0; v < NV; v++)
        color[v] = BRANCO;

    inicio = fim = 0;
    orla[fim++] = o;
    dist[o] = 0;
    color[o] = CINZENTO;

    while (inicio != fim) {
        v = orla[inicio++];
        color[v] = PRETO;
        for (pt = g[v]; pt != NULL; pt = pt->next) {
            if (color[pt->dest] == BRANCO) {
                dist[pt->dest] = 1 + dist[v];
                orla[fim++] = pt->dest;
            }
        }
    }
}

//Função Principal
int main() {

    //GRAFO PESADO ORIENTADO
    GraphMat g1 = {
            {NE,2,7,NE,NE,NE},
            {NE,NE,NE,1,NE,NE},
            {NE,NE,NE,NE,NE,1},
            {5,NE,NE,NE,8,NE},
            {3,NE,NE,NE,NE,NE},
            {4,NE,NE,3,2,NE},
            };

    //GRAFO PESADO NÃO ORIENTADO
    GraphMat g2 = {
            {0,1,1,0,0,0},
            {0,0,0,1,0,0},
            {0,0,0,0,0,1},
            {1,0,0,0,1,0},
            {1,0,0,0,0,0},
            {1,0,0,1,1,0},
            };

    //GRAFO NÃO PESADO ORIENTADO
    GraphMat g3 = {
            {NE,2,7,5,3,4},
            {2,NE,NE,1,NE,NE},
            {7,NE,NE,NE,NE,1},
            {5,1,NE,NE,8,3},
            {3,NE,NE,8,NE,2},
            {4,NE,1,3,2,NE},
            };

    return 0;
};
