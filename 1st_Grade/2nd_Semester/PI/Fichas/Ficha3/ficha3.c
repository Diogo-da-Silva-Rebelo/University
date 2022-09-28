#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swapM (int *x, int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void swap1 (int v[], int i, int j){
   swapM(&v[i],&v[j]);
}

void swap2 (int v[], int i, int j) {
    int z;
    z = v[i];
    v[i] = v[j];
    v[j] = z;
}

void swap3 (int v[], int i, int j) {
    swapM(v+i,v+j);
}

void inverteArray (int v[], int N){
    int k;
    for (k=0; k < N/2; k++) {
        swap1(v,k,N-1-k);
        //swapM(&v[k], &v[N-1-k]);
        //swap(v+k,v+N-1-k);
    }
}

void inverteArray2 (int v[], int N) {
    int inicio = 0, fim = N - 1;
    while (inicio < fim) {
        swap(v, inicio, fim);
        //swapM(&v[inicio],&v[fim]);
        inicio++;
        fim--;
    }
}

void dumpV (int v[], int N){
    int i;
    for (i=0; i<N; i++) printf ("%d ", v[i]);
    putchar ('\n');
}

int soma (int v[], int N){
    int sum= 0;
    for (int i=0; i<N; i++) sum += v[i];
    return sum;
}

int maximum (int v[], int N, int *m){
    if (N<=0) return 1;
    else {
        *m = v[0];
        for (int i = 0; i < N; i++) {
            if (v[i] > *m) *m = v[i];
        }
        return 0;
    }

void quadrados (int q[], int N){
    for(int i=0; i<N; i++) v[i] = pow(i,2);
}

void quadrados2 (int q[], int N) {
    for (int i = -1; i < N - 1; i++) {
        int r = i * i + (2 * i + 1);
        q[i + 1] = r;
    }
}

void pascal (int v[], int N){
    int i, j;
    for (i = 0; i < N; i++){
        j = i;
        while (j >= 0){
            if (j == i) v[j] = 1;
            else if (j > 0) v[j] += v[j-1];
            j--;
        }
        dumpV(v, i);
    }

}

//versão mais eficiente de impressão
void desenhaTriangulpP2(int N) {
    int vaux[N];
    pascal(vaux, N);
}

void desenhaTriangulpP1 (int N) {
        int k, v[N];
        for (k = 1; k <= N; k++) {
        pascal(v, k);
        dumpV(v, k);
}

int main()
{
    printf ("Testes\n");
    // teste das funções de swap

    int a, b, v[10] = {10, 6, 2, 3, 5, 1, 5, 9, 8, 7};
    int x = 3, y = 5;
    printf ("x = %d y = %d\n", x, y);
    swapM (&x, &y);
    printf ("x = %d y = %d\n", x, y);

    printf ("%d %d\n", v[0], v[9]);
    swap (v,0,9);
    printf ("%d %d\n", v[0], v[9]);

    /*
    printf ("ao invertemos o array "); dumpV (v,10);
    inverteArray (v,10);
    printf ("obtemos               "); dumpV (v,10);

    */

    // teste das funções maximum, soma e quadrados
    /*
    x = maximum (v,10, &y);
    printf ("O maior elemento de "); dumpV (v,10);
    printf ("é %d\n", y);
    */
    /*
    printf ("Os 10 primeiros quadrados: ");
    quadrados (v,10);
    dumpV (v,10);
    */
    /*
    x = soma (v,10);
    printf ("A soma dos elementos de "); dumpV (v,10);
    printf ("é %d\n", x);
    */

    // teste da função de cálculo do triangulo de Pascal
    /*
    printf ("A linha 5 do triângulo de Pascal é ");
    pascal (v,5); dumpV (v,5);
    */
    /*
    printf ("As linhas 0 a 10 do triângulo de Pascal\n\n");
    desenhaTriangulpP (10);
    */
    printf ("\nFim dos testes\n");

    return 0;
}