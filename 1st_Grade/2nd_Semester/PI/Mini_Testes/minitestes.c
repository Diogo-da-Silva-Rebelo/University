//MIni-Teste 1
#include "string.h"
#include "stdio.h"

//1
int func(int x) {
    int r = 0;
    while (x > 0) {
        r += 2;
        x = x - r;
    }
    return r;
}

//2
/* Função que desenha a figura abaixo:

########
#######.
######..
#####...
####....
###.....
##......
#.......

 */

void desenhaFigura() {
    int x, y;
    for (y = 0; y < 8; y++) {
        for (x = 0; x < 8; x++) {
            if (x + y <= 7) putchar('#');
            else putchar('.');
        }
        putchar('\n');
    }
}

//Mini-Teste 2
//1 e 2
//função que verifica um número perfeito
int perfeito(int x){
    int sum = 0;
    for (int i = 1; i < x; i++){
        if (x % i == 0) sum = sum + i;
    }
    if (sum == x) return 1;
    else return 0;
}

int sumhtpo (int n){
    int r = 0;
    int count = 0;
    int perfect = 0;
    while (n != 1) {
        r += n;
        if (perfeito(n)) perfect++;
        if (n%2 == 0) {
            n = n / 2;
            count++;
        }
        else n = 1+(3*n);
    }
    printf("O resultado é par para %d parcelas!\n", count);
    printf("Existem %d parcelas que são números perfeitos!\n", perfect);
    return r;
}

//Mini-Teste 3
//1
int hash (char s[]) {
    int r = 0;
    while (*s) {r += *s; s++;}
    return r;
}

int hashAlterada(char s[]){
    int r = 0;
    int j = 1;
   for (int i = strlen(s)-1; i >= 0; i--,j++){
       r += (s[i]) * j;
   }
    return r;
}
//2


//Mini-Teste 5
//1
//2

//Mini-Teste 6
//1
//2


int main(){
    /*MT1
    int count = 0;
    for (int i = 0; i < 20; i++){
        printf("%d", func(i));
        printf(",");
        if (func(i) == 4) count++;
    }
    printf("\n");
    printf("É produzido o resultado \"4\" para %d valores!\n", count);
     */
    /*MT2
    int n = 47;
    sumhtpo(n);
    n = 37;
    sumhtpo(n);
     */
    char *s = NULL;
    int valor = hashAlterada(strdup("programacao funcional"));
    printf("O valor da hash neste caso é: %d\n", valor);
    return 0;
}