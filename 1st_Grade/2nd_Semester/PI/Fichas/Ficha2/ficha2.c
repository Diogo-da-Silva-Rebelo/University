#include "stdio.h"
#define "stdlib.h"

//VERSÕES DE MULT
float multInt1 (int n, float m){
    float r = 0.0;
    while (n>0) {
        n--;
        r += m;
    }
    return r;
}

//Versão recursiva
float multInt1Aux (int n,int m, float r) {
    if (n == 0) return r;
    return multInt1Aux(n - 1, m, r + m);
}

float multInt1Rec (int n, int m, float r) {
    if (n == 0) return r;
    return multInt1Aux(n-1, m, r+m);
}

//Esquema

/*  l  n   m
   ------------
    1  17  16
    2  8   32     n * m = 16 + 256 = 272
    3  4   64     17 * 16 = 272
    4  2   128
    5  1   256
   ------------
 */

float multInt2 (int n, float m){
    int r = 0.0;
    while (n>0){
        if(!n%2) r+=m;
        m*=2;
        n /=2;
    }
    return r;
}

//versão recursiva
float  multInt2Rec(int n, int m, float r){
    if (n == 0) return (r);
    else if (n%2 == 0) return multInt2Aux(n/2, m*2, r);
}

float  multInt2Aux(int n, int m, float r) {
    r = 0.0;
    return multInt2Aux();
}

//Pasar argumento por referencia leva a que a função produza dois valores
float multInt3 (int n, float m, int *count){
    //count = NULL; Fazemos assim sempre que queremos inicializar apontadores.
    float r = 0.0;
    *count = 0;
    while (n>0){
        if(!n%2) {
            r+=m;
            (*count)++;
        }
        m*=2;
        n /=2;
    }
    return r;
}
//OBS. há produção de um efeito lateral na variável count.


//VERSÕES DE MDC
/* 16 24 -- [1..16] */

//versão recursiva
int mdcaux(int a,int b,int c) {
    if (a%c == 0 && b%c == 0) return c;
    else return mdcaux(a,b,c-1);
}

int mdc1Rec (int a, int b) {
    return mdcaux(a,b,a>b?b:a);
}

void swap (int *a, int *b){
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

int mdc1 (int a, int b) {
    int divisor;
    if (a<b) return divisor = a;
    else divisor = b;
    while (((a%divisor != 0) || (b%divisor !=0)) && (divisor>1)) divisor--;
    return divisor;
}

//versão recursiva olhando para a versão imperativa acima

//versão recursiva
int mdc2Rec (int a, int b) {
    int mdc2_rec(int a, int b) {
        if (a > b) return mdc2_rec(a - b, b);
        else if (a < b) return mdc2_rec(a, b - a);
        else return a;
    }
    return 0;
}

int mdc2 (int a, int b) {
    while (a != b){
        if (a < b) b = b - a;
        else a = a - b;
    }
    return a;
}

int mdc3 (int a, int b, int *count) {
    //*count = 0;
    while (a != b) {
        if (a < b) b = b - a;
        else a = a - b;
        (*count)++;
    }
    return a;
}


int mdc4 (int a, int b, int *count) {
    while (a != b) {
        if (a < b) b = b % a;
        else a = a % b;
        (*count)++;
    }
    return a;
}


//VERSOES DE FIB
int fib (int n){
    if(n<2) return 1;
    else return fib(n-1) + fib(n-2);
}

//Versão mais eficiente - guarda os dois valores anteriores
int fastfib (int n) {
    int a = 0;
    int b = 1;
    int c, i;

    if (n == 0)
        return 0;
    for (i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}
