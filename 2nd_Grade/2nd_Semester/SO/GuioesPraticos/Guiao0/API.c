#include "API.h"

/* Guião 0: revisão de conceitos em C
 * Conceitos fundamentais:
 * -> variáveis locais/automáticas:
 *  Só tem validade dentro da função onde foram declaradas/passadas;
 *  Podem ser declaradas no início da função;
 *  Podem ser passadas como parâmetros (Parâmetros formais);
 *  Recebem uma cópia do valor passado à função;
 *  Alterações no valor dos parâmetros da função não são percebidos
 *  pelo programa, exceto se o parâmetro for do tipo array;
 * -> variáveis globais:
 *  Tem validade dentro do programa em questão;
 *  São declaradas antes de todas as funções do programa (fora da main);
 *  Podem ser alteradas por todas as funções do programa;
 *  Se uma função tem uma variável local com o mesmo nome que a variá
 *  vel global, então, para essa função, a variável é local;
 *  Evitar usar, pois ocupam memória por mais tempo.
 *  ATENÇÃO: Deve ser feito o guião sem ser numa IDE, criando o makefile
 *  com "touch Makefile" com:
 *  all:
 *  gcc *.c *.h
 */

/* Função que preenche um array com inteiros [1,2,3,...]
 * Se value for 2, fica: [2,3,4,...]
 * Se value for 5, fica: [5,6,7,...]
 * Poder-se-ia mandar o utilizador preencher o array com
 * os nºs por ele escolhidos, mas para o efeito seria o mesmo.
*/
void fill(int* vector, int size, int value){
    int i;
    for (i=0;i<size;i++) vector[i]=value+i;
}

//Função que encontra um determinado elemento no array, dados o valor
int find(int* vector, int size, int value){
    int i;
    for (i=0;i<size;i++){
        if (vector[i]==value) return i;
    }
    return -1;
}

/* Para fazer uma pesquisa no array entre dois índices (inicial e final)
 * podemos passar os índices como parâmetro formal da função "find", então:
*/

//Função que encontra um determinado elemento no array, dados os índices
int find_ind(int* vector, int value, int a, int b) {
    int i;
    for (i=a; i < b; i++) {
        if (vector[i] == value) return i;
        //OBS: Atenção que na comparação usa-se "==" e não só "=" !!!
    }
    return -1;
}