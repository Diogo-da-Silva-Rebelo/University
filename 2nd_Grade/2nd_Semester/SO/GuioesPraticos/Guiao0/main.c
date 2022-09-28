#include "API.h"

//De um modo geral, poderíamos utilizar esta main:
int vetor1[19]; //variável global

int main ( ){
    int vetor2[89]; //variável local
    int *vetor3 = malloc(sizeof (int)*172); //alocação
    fill(vetor1,19,77);
    fill(vetor2,89,42);
    fill(vetor3,172,137);
    int a=find(vetor1,19,129);
    int b=find(vetor2,89,190);
    int c=find(vetor3,172,74);
    return 0;
}

/*Com vetores em variáveis automática/local:
int main() {
    int i, value, *vector, size; //variável local

    printf("Dimensão do array seguida do inteiro a inserir: ");
    scanf("%d %d", &size, &value);
    fill(vector, size, value);

    printf("O array é: ");
    for (i=0;i<size;i++) printf("%d ", vector[i]);

    return 0;
}
*/

/* Com vetores em memória dinâmica:
int main() {
    int i, value, size;

    int *vector;

    printf("Dimensão do array seguida do inteiro a inserir: ");
    scanf("%d %d", &size, &value);

    vector = malloc(sizeof (int)*size); //variável alocada

    fill(vector, size, value);

    printf("O array é: ");
    for (i=0;i<size;i++) printf("%d ", vector[i]);

    return 0;
}
*/

/* Com variáveis globais:
int *vector; //variável global
int main() {
    int i, value, size;

    printf("Dimensão do array seguida do inteiro a inserir: ");
    scanf("%d %d", &size, &value);

    vector = malloc(sizeof (int)*size); //necessaŕio para não dar SEG
    fill(vector, size, value);

    printf("O array é: ");
    for (i=0;i<size;i++) printf("%d ", vector[i]);

    return 0;
}
*/

/* Procura de um elemento entre os índices a e b
int main() {
    int i, value, size, a, b, proc;

    int *vector;

    //Inserção dos números no array
    printf("[Inserção] Dimensão do array seguida do inteiro a inserir: ");
    scanf("%d %d", &size, &value);
    vector = malloc(sizeof (int)*size); //variável alocada
    fill(vector, size, value);
    printf("O array é: ");
    for (i=0;i<size;i++) printf("%d ", vector[i]);

    //Procura do elemento no array, dados os índices
    printf("\n\n[Procura] Indices inicial e final e elemento a procurar: ");
    scanf("%d %d %d", &a,&b,&proc);
    int elemento= find_ind(vector,proc,a,b);
    if (elemento != -1) printf("Elemento encontrado na posição %d", elemento);
    else printf("Elemento não encontrado");

    return 0;
}
*/

/* Preenchimento do array para além do seu tamanho limite:
 * Na função abaixo, declara-se um array de tamanho 3, e tenta-se preencher as posições seguintes,
 * tentando-se imprimir depois uma das posições fora da dimensão do array. É de esperar que surja
 * um erro do compilador, pois estamos a tentar aceder a posições que não existem.
int main(){
    int *vector[3];

    vector[0]= 1;
    vector[1]= 2;
    vector[2]= 3;
    vector[3]= 4;
    vector[4]= 5;

    printf("Posição de índice 5: %d", vector[4]);
    return 0;
}
*/