#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* -> Um compilador converte de um formato para outro. Normalmente,
 * a conversão é feita de código-fonte para código máquina. Esta
 * conversão não é feita apenas uma vez, mas ao longo de várias
 * vezes. Em c, o nosso compilador tem várias fazes e convém ter-
 * mos consciência de algumas fases para programar. Um interpretador
 * analisa linha-a-linha e difere de um compilador.*/

/* CPP (C preProcessor): analisa o nosso o código e identifica os
 * includes, incluindo o código das respetivas bibliotecas no nosso
 * código;
 * CC (C Compiler): compila o nosso código;
 * Linker: ...
 * Com o comando gcc -c fazem-se apenas as 2 primeiras fazes. */

/* Canais de input/output (IO):
 * -> stdout: associado ao monitor do computador;
 * -> stderr: canal de erros (sinalização de erros), normalmente
 * associado ao monitor, todavia, pode ser redirecionado para o que
 * pretendermos;
 * -> stdprn: impressora (o retorno do programa sai na impressora);
 * -> stdin: canal de entrada, teclado. */

/* Modificadores: estruturas que aparecem em formatos como printf.
 * Podem ser:
 * %d - inteiros;
 * %f - reais;
 * %c - careter;
 * %s - strings; */

/* Código ASCII:
 * letras maiúsculas começam no A 65 até Z 90;
 * letras minúsculas começam no a 97 até z 122;
 * letras estão seguidas e código ascii;
 * Conversão de minúculas/maiúsculas distam 32! */

void quad (int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            putchar('#');
        }
        putchar('\n');
    }
}

void quadw (int n) {
    int i = 0, j = 0;

    while (i < n) {
        while (j < n) {
            putchar('#');
            j++;
        }
        putchar('\n');
        i++;
        j=0; //preparação do controle do ciclo!!
    }
}

void xadrez(int n){
    int i,j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if ((i+j)%2==0) putchar('#');
            else putchar('_');
        }
        putchar('\n');
    }
}

void xadrezw(int n){
    int i=0;
    while (i<n){
        int j=0;
        while (j<n){
            if ((i+j)%2==0) putchar('#');
            else putchar('_');
            j++;
        }
        putchar('\n');
        i++;
    }
    return;
}

/*
#_#_#
(0,0) (0,1) (0,2)
_#_#_
 (1,0) (1,1) (1,2)
#_#_#
 ...
_#_#_
#_#_#
 -> somatório de x e y for par ou ímpar;
 */

//rever
void triangulov (int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            putchar('#');
        }
        putchar('\n');
    }
    n--;
    for (i = n; i > 0; i--) {
        for (j = 0; j <i; j++) {
            putchar('#');
        }
        putchar('\n');
    }
}

//Versão 1 da função que imprime um triângulo na horizontal
void trianguloh (int n) {

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n - i - 1; j++) {
            putchar(' ');
        }
        for (int j = 1; j <= 2 * i - 1; j++) {
            putchar('#');
        }
        putchar('\n');
    }
}

//Versão 2 da função que imprime um triângulo na horizontal
void repeteChar(char c, int n){
    for (int i=0;i<n;i++) putchar(c);
}

void trianguloh2 (int n) {
    int i = 1;
    while (i < (n * 2 - 1)) {
        repeteChar(' ', ((n * 2 - 1) - i) / 2);
        repeteChar('#', i);
        repeteChar(' ', ((n * 2 - 1) - i) / 2);
        i += 2;
        putchar('\n');
    }
}

/* - Um cubo: 3 dimensões;
 * - Dividir o cubo em cubos mais pequenos com aresta igual a 1/2
 * da aresta original;
 * - Fórmula para calcular a área envolvente de um cubo: 6*n^2
 * - Na primeira divisão o somatório das áreas envolventes é
 * 8* (6*(n/2)^2) */

int nCubos(int n){
    return 12*n^2;
}

int areaCubos(int n){
    return 8^n;
}

/* Exercícios propostos:
 * Calcular os primos até 100;
 * Verificar se um número é Primo;
 * Ler uma string em numeração romana e dar o correspondente decimal;
 * Lê uma string em numeração romana e dá o correspondente decimal;
 * Regras para romana:
 * -> Algarismos de menor ou igual valor à direita são somados ao algarismo de maior valor;
 * -> Algarismos de menor valor à esquerda são subtraídos do algarismo de maior valor. */

//Verifica se um número é primo: divisível por ele e pela unidade
int verificaPrimo (int n){
   int res=0, i;
    for (i = 2; i <= (n / 2); i++) {
        if (n % i == 0) {
            res++;
            break;
        }
    }

    if (res == 0 && n != 0 && n != 1) return 1;
    else return 0;
}

//imprime todos os números primos até 100
void primosCem (){
    int i;
    for(i=0; i<100;i++) {
        int eprimo = verificaPrimo(i);
        if (eprimo) printf("%d ", i);
    }
    putchar('\n');
}

/* Desenhar um círculo com chars:

 r = 4

    #  l = 0                         r espaços # r espaços
  #####   l = 1                    r-1 espaços ... r-1 espaços
 #######  ...
 #######                            (1,1) - canto superior esquerdo
#########  Nº char = r*2 +1         (r+1, r+1) - centro do círculo
 #######                            d(ponto,centro) <= r ->> pertence ao círculo
 #######  ...                       dois ponot (x1,y1) (x2,y2)
  ##### l = 6                       sqrt(pow((x2-x1),2) + pow((y2-y1),2))
    #  = 7                        <=> pow((x2-x1),2) + pow((y2-y1),2) <= pow(r,2)
                                  <=> (linha - (r+1))^2 + (coluna-(r+1))^2 <= r^2
                                  <=> condição de teste!!

 Quando condição de teste é V : imprime #
 Quando condição de teste é F : imprime espaço

 matriz dimensão: (2*r+1) * (2*r+1)

*/

// Estrutura com 2 dimensões = 2 ciclos for aninhados
// Estrutura com 3 dimensões = 3 ciclos aninhados
// Assim sucessivamente

int circulo (int r){
    int count = 0;
    for (int i=1; i <= (2*r+1) ; i++){
        for (int j=1 ; j <= (2*r+1); j++){
            if (pow(i -r-1, 2) + pow(j-r-1,2) <= pow(r,2)){
                putchar('#');
                count++;
            }
            else putchar(' ');
        }
        putchar('\n');
    }
    return count;
}

//Função principal
int main() {
    //quadw(5);
    //quadw(6);
    //xadrezw(8);
    //triangulov(5);
    //trianguloh(5);
    //verificaPrimo(0);
    //primosCem();

    /*for(int i=1; i <= 10;i++) {
        printf("%d, nCubos: %d, Área envolvente: %d\n", i, nCubos(i), areaCubos(i));
    }*/
    for (int r = 3; r <= 7; r++) {
        printf("\n\nEste círculo tem %d pontos.\n", circulo(r));
    }
    return 0;
    //OBS: usei o comando gcc ficha1.c -o circulo -lm (para compilar)
}