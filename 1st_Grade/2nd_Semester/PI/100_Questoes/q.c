#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

//1.Maior elemento de uma sequência
void maior_sequencia(){
    int num, maior = INT_MIN;
    printf("Insira a sua sequência: ");

    do{
        scanf("%d", &num);
        if (num == 0) break;
        if (num > maior) maior=num;
    }
    while (num);
    printf("O maior elemento é: %d\n", maior);
}

//Versão com apontador numero
void maior_sequencia2() {
    int *num, maior = INT_MIN;
    printf("Insira a sua sequência: ");

    do {
        scanf("%d", num);
        if (*num == 0) break;
        if (*num > maior) maior = *num;
    } while (*num);
    printf("O maior elemento é: %d\n", maior);
}

//2.Média da sequência
void media (){
    int num, total=0;
    float media, soma=0;

    printf("Insira a sua sequência: ");
    do {
        scanf("%d", &num);
        if (num == 0) break;
        soma += num;
        total++;
    } while (num != 0);
    media = soma/total;
    printf("A média é: %.2f\n ", media);
}

//3.Segundo maior elemento da sequência
void segundo_maior() {
    int maior = INT_MIN, seg_maior = INT_MIN, num;
    printf("Insira a sua sequência: ");

    do {
        scanf("%d", &num);
        if (num == 0) break;
        if (num > maior){
            seg_maior = maior;
            maior = num;
        }
    } while (num != 0);
    printf("O segundo maior elemento é: %d\n", seg_maior);
}

//4.Número de bits iguais a 1 num número
int bitsUm (unsigned int n){
    int res = 0;
    while (n) {
        if (n%2 == 1) res++;
        n = n/2;
    }
    return res;
}

//5.Número de zeros no final da representação binária
int trailingZ (unsigned int n) {
    int i=0;

    if (n == 0) return 32;
    while(n && n%2 == 0) {
        i++;
        n/=2;
    }
    return i;
}

//6.Dígitos necessaŕios para escrever um número em decimal
int qDig (unsigned int n) {
    int res = 0;
    while (n){
        n/=10;
        res++;
    }
    return res;
}

//7. Concatenação de duas strings
char *mystrcat (char s1[], char s2[]){
    int i, j;

    for(i=0;s1[i];i++); //coloca i na última posição de s1;
    for(j=0;s2[j];j++)
    {
        s1[i+j]= s2[j];
        s1[i+j+1]='\0'; //por cada iteração é posto no final o '\0'
    }
    //s1[i+j]='\0'; Isto também funcionaria (retirando a linha comentada acima)
    return s1;
}

//8.Cópia de duas strings
char *mystrcpy(char s1[], char s2[]) {
    int i;
    for (i=0;s2[i];i++) s1[i]=s2[i];
    s1[i] = '\0';
    return s1;
    //obs. se s2 for maior que s1, s2 não fica totalmente copiado para s1
}

//9.Comparação de duas strings
int mystrcmp (char s1[], char s2[]) {
    int i;

    for (i=0;;i++) {
        if (s1[i] != s2[i]) return s1[i] < s2[i] ? -1 : 1;
        if (s1[i] == '\0') return 0;
    }
}
//Obs. esta função não relaciona tamanhos. Ela olha para o código ASCII de char

//10. Posição onde s2 ocorre em s1, retornando onde ocorre em s1
char* mystrstr (char s1[], char s2[]) {
    //length[s2]<length[s1], pois s2 está contido em s1
    int i, j;
    if (!*s2) return s1;
    if (!*s1) return (!*s2) ? s1 : NULL;
    for (i = 0; s1[i]; i++) {
        for (j = 0; s1[i + j] && s2[j] && s1[i + j] == s2[j]; j++) {
            if (!s2[j + 1]) return s1 + i;
            //anda tantas vezes quanto as chars iguais, daí s1+i.
        }
    }
    return NULL;
}
/*
Análise detalhada da função acima:
A função retorna a posição onde s2 ocorre em s1. Assim, vamos analisar
o seguinte exemplo:

 s1: "O Diogo"
 s2: "Diogo" [note-se que o tamanho de s2 é sempre menor que o de s1]

 Casos:
-> Se não existir s2, ou seja, se s2 for NULL, então retorna-se a pri
meira posição de s1, imprimindo s1;
-> Se não existir s1 (ou seja, s1: ""), convém verificar se s2 é "". Se
sim, então, retorna-se s1. Caso s2 != "", então retorna-se NULL, pois s2
não ocorre em s1;
-> Se ambas as strings existirem, temos o caso geral:
Vamos ter de comparar todas as poisições de s1 com todas as posições de
s2. Mas, se a posição atual i de s1 for igual à j de s2, então, continuamos
a verificar as duas posições se coincidem. Assim que elas deixarem de coin
cidir, então, avançamos com a posição de s1 e voltamos a analisar com todas
as posições de s2. A comparação para até que as posições sejam diferentes.
Enquanto forem iguais, vamos avançando para "guardar" a string a devolver.
 */

//11.Função que inverte uma string
void strrev (char s[]) {
    int i, j, last;

    for (i = 0; s[i]; i++);
    i--;
    for (j = 0; j < i; i--, j++) {
        last = s[i];
        s[i] = s[j];
        s[j] = last;
    }
    return;
}

//12.Remoção de vogais de uma string
void mystrnoV (char s[]) {
    int i,j;
    for (i=0; s[i];i++){
        if(s[i] == 'a' ||s[i] == 'e' ||s[i] == 'i' ||s[i] == 'o' ||s[i] == 'u' ||s[i] == 'A' ||s[i] == 'E' ||s[i] == 'I' ||s[i] == 'O' ||s[i] == 'U'){
            for(j = i; s[j]; j++) s[j] = s[j+1];
            i--;
        }
    }
}

//13. Trunca as palavras com, no máximo, n careteres
void truncW (char t[], int n) {
    int i = 0, length = 0, j;
    while (t[i]) {
        if (t[i] == ' ' || t[i] == '\n' || t[i] == '\t') {
            length = 0;
            i++;
        } else if (length < n) {
            i++;
            length++;
        } else {
            for(j = i; t[j]; j++) t[j] = t[j+1];
        }
    }
}

//14.Char mais frequente na string s
//função auxíliar que conta a ocorrência de cada char e a retorna
int ocorrChar(char s[], char a){
    int times = 0;
    for (int i=0; s[i] != '\0'; i++){
        if (s[i] == a) times++;
    }
    return times;
}

char charMaisfreq(char s[])
{
    int acc[257] = {0};
    int max = 0;
    int i;
    char max_char;

    for (i = 0; s[i] != 0; i++) acc[s[i]]++;

    for (i = 0; i < 257; i++)
        if (acc[i] >= max) {
            max = acc[i];
            max_char = i;
        }

    return max_char;
}

//15. Comprimento da maior substring
int iguaisConsecutivos (char s[]){
    int i, j, l, sub[50] = {0}, max = 0, times = 0, k = 0;

    if (!strlen(s)) return 0;

    for (i = 0; s[i] != '\0'; i++){
        for (j = i+1; j != '\0' && s[i] == s[j]; j++){
            times++;
        }
        sub[k] = times;
        k++;
        times = 0;
    }

    for (l = 0; l<50; l++) {
        if (sub[l] >= max) {
            max = sub[l];
        }
    }
    return max+1;
}

//outra função possível
int iguaisConsecutivos2(char s[]){
    int i = 0, max = 0, c = (s[0] != '\0');

    while (s[i]){
        if (s[i] == s[i + 1])
            c++;
        else{
            if (c > max)
                max = c;
            c = 1;
        }
        i++;
    }
    return max;
}

//16. Comprimento da maior substring com chars diferentes
//função auxíliar que retorna o número de ocorrências diferentes num array
int dif(char *s, int j) {
    int i;
    for (i = 0; i < j && s[i] != s[j]; i++);
    return i == j;
}

//função principal
int difConsecutivos (char s[]){
    int max = 0;
    int i,j;
    for(i = 0; s[i]; i++) {
        for(j = i; s[j]!= '\0' && dif(s+i,j-i) != 0; j++);
        if(j-i > max) max = j-i;
    }
    return max;
}

//17. Comprimento do maior prefixo de duas strings
// string: diogo; prefixos: [d],[di],[dio],[diog],[diogo]
// string: diadora; prefixos: [d],[di],[dia],[diad],[diado],[diador],[diadora]
//diogo & diadora
int maiorPrefixo (char s1 [], char s2 []){
    int i = 0;
    while (s1[i] != '\0' && s2[i] !='\0' && s1[i]==s2[i]) i++;
    return i;
}

//18. Comprimento do maior sufixo de duas strings
int maiorSufixo (char s1 [], char s2 []){
    //-1 para dar index
    int size1 = strlen(s1) - 1;
    int size2 = strlen(s2) - 1;
    int i = 0;
    while (size1 >= 0 && size2 >= 0 && s1[size1]==s2[size2]){
        i++;
        size1--;
        size2--;
    }
    return i;
}

//coloca todos os prefixos de uma string num array
char** prefixToArray (char *s1, int N){
    char** array = malloc(sizeof (char*)*(N));
    for (int i = 0; i < N; i++) {
        char *buf = malloc(sizeof (char)*(i+1));
        strncpy(buf,s1,i+1);
        array[i] = buf;
    }
    return array;
}
//retorna o char no index dado
char charOfIndex(int index, char *s){
    return s[index];
}

//troca elementos do array
char* reverseArray(char arr[], int start, int end) {
    int temp;
    while (start < end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
    return arr;
}

//19. Tamanho do maior sufixo de s1 que é um prefixo de s2
int sufPref (char s1[], char s2[]) {
    int i, j = 0, c = 0;
    for (i = 0; s1[i] != '\0'; i++) {
        if (s1[i] == s2[j]) {
            c++;
            j++;
        } else {
            c = 0;
            j = 0;
        }
    }
    return c;
}

//20. conta palavras de uma sring
int contaPal (char s[]) {
    int i;
    int sum = 0;
    int flag = 0;
    for (i = 0; s[i]; i++) {
        if ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && flag == 0) continue;
        else if (s[i] == ' ' && flag == 1) {
            sum++;
            flag = 0;
        } else {
            flag = 1;
            if (s[i + 1] == '\0') {
                sum++;
            }
        }
    }
    return sum;
}

//21. conta vogais na string
int contaVogais (char s[]) {
    int i = 0;
    int sum = 0;
    for (i = 0; s[i]; i++) {
        if (s[i] == 'A' || s[i] == 'a' || s[i] == 'E' || s[i] == 'e' || s[i] == 'I' || s[i] == 'i' || s[i] == 'O' ||
            s[i] == 'o' || s[i] == 'U' || s[i] == 'u') {
            sum++;
        }
    }
    return sum;
}

//22. careteres contidos numa string
//verifica se o char dado está em b
int elem (char s, char b[]) {
    int i;
    for (i = 0; b[i] != '\0'; i++) {
        if (s == b[i]) return 1;
    }
    return 0;
}

int contida (char a[], char b[]) {
    int i;
    for (i = 0; a[i]; i++) {
        if (elem(a[i], b)) continue;
        else {
            return 0;
        }
    }
    return 1;
}

//23. verifica se a palavra é palindrome/capicua
int palindroma (char s[]) {
    int i;
    int j = strlen(s) - 1;

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] != s[j]) return 0;
        else j--;
    }
    return 1;

}

//24. retira careteres repetidos e dá o tamanho da string resultante.
int remRep (char x[]) {
    int i = 0, j = 0;
    for (i = 0; x[i]; i++) {
        if (x[i] == x[i + 1]) {
            for (j = i; x[j]; j++) {
                x[j] = x[j + 1];
            }
            i--;
        }
    }
    return strlen(x);
}

//25. limpa espaços
int limpaEspacos (char t[]) {
    int i, j = 0;
    for (i = 0; t[i]; i++) {
        if (t[i] == ' ' && t[i + 1] != ' ') {
            t[j] = t[i];
            j++;
        } else if (t[i] != ' ') {
            t[j] = t[i];
            j++;
        }
    }
    t[j] = '\0';
    return j;
}

//26. insere num vector ordenado

void insere (int v[], int N, int x) {
    int i;
    for (i = N - 1; i >= 0 && x < v[i]; i--)
        v[i + 1] = v[i];
    v[i + 1] = x;
}

//27. soma de vetores
void merge (int r [], int a[], int b[], int na, int nb) {
    int i, j, z;
    i = j = z = 0;
    int t = na + nb;
    int v[t];
    while (i < na && j < nb) {
        if (a[i] < b[j]){
            v[z] = a[i];
            z++;
            i++;
        }
        else {
            v[z] = b[j];
            z++;
            j++;
        }
    }

    while (i == na) v[z++] = b[j++];
    while (j == nb) v[z++] = a[i++];
    for (i = 0; i < t; i++)
        r[i] = v[i];
}

//28. verifica ordenação crescente
int crescente (int a[], int i, int j){
    for (i; i < j; i++){
        if (a[i] > a[i+1]) return 0;
    }
    return 1;
}

//29. retira negativos
int retiraNeg (int v[], int N) {
    int i, j = 0;
    for (i = 0; i < N; i++) {
        if (v[i] >= 0) {
            v[j] = v[i];
            j++;
        }
    }
    return j;
}

//30. dá o elemento menos frequente
int menosFreq (int v[], int N) {
    int i, c = 0, menor = v[0];
    int cont = 1;

    for (i = 0; i < N - 1; i++) {
        if (v[i] == v[i + 1])
            cont++;
        else {
            if (c == 0 || cont < c) {
                c = cont;
                menor = v[i];
            }
            cont = 1;
        }
    }
    if (cont < c)
        menor = v[i];
    return menor;
}

//31. mais frequente num array de inteiros (corrigir)
//dá o número de ocorrências
int OccElem(int v[], int N, int x) {
    int i, count = 0;
    if (N == 0) return count;
    for (i = 0; i < N; i++) {
        if (v[i] == x) count++;
    }
    return count;
}

//Assume já [1,2;3,4;...]
int maxElem(int v[], int N) {
    int i;
    int max = v[0];
    int maxOcc = v[1];
    if (N == 1) {
        return v[0];
    } else {
        for (i = 0; i < N - 1; i++) {
            if (i % 2 != 0) {
                if (v[i] > maxOcc) {
                    maxOcc = v[i];
                    max = v[i - 1];
                }
            }
        }
    }
    return maxOcc;
}

int maisFreq(int v[], int N){
    int o[N];
    int i,d = 0;
    for (i = 0; i < N ; i++){
        o[i] = v[i];
        d = OccElem(v,N,v[i]);
        o[i+1] = d;
    }
    o[i] = '\0';
    return maxElem(o,N);
}

//versão correta
int maisFreq (int v[], int N) {
    int i, c = 0, maior;
    int cont = 1;
    for (i = 0; i < N - 1; i++) {
        if (v[i] == v[i + 1])
            cont++;
        else cont = 1;
        if (cont > c) {
            c = cont;
            maior = v[i];
        }
    }
    if (cont > c)
        maior = v[i];
    return maior;
}

//33. elimina repetições
int repetido (int a, int v[], int n){
    int i;
    for (i=0; i<n; i++){
        if(a==v[i])
            return 1;
    }
    return 0;
}

int elimRep (int v[], int n) {
    int i, j = 0;
    int f[n];
    for (i = 0; i < n; i++) {
        if (!repetido(v[i], f, j)) {
            f[j] = v[i];
            v[j] = v[i];
            j++;
        }
    }
    return j;
}

//34. elimina repetições num array ordenado
int elimRepOrd (int v[], int n) {
    int i, j = 0;
    for (i = 0; i < n - 1; i++) {
        if (v[i] != v[i + 1]) {
            v[j] = v[i];
            j++;
        }
    }
    v[j] = v[i];
    return j + 1;
}
//35. elementos em comum de dois vectores
int comunsOrd (int a[], int na, int b[], int nb) {
    int i, j, c;
    i = j = c = 0;
    while (i < na && j < nb) {
        if (a[i] == b[j]) {
            c++;
            i++;
            j++;
        } else {
            if (a[i] < b[j])
                i++;
            else j++;
        }
    }
    return c;
}

//36. Número de elementos em comum
int comuns (int a[], int na, int b[], int nb) {
    int i, j, c = 0;
    for (i = 0; i < na; i++) {
        for (j = 0; j < nb; j++) {
            if (a[i] == b[j]) {
                c++;
                break;
            }
        }
    }
    return c;
}

//37. Indice do menor elemento do vector.
int minInd (int v[], int n) {
    int i, idx_min = 0, min = v[0];
    for (i = 0; i < n; i++) {
        if (v[i] < min) {
            min = v[i];
            idx_min = i;
        }
    }
    return z;
}

//38. Somas acumuladas
void somasAc (int v[], int Ac[], int N) {
    int i, soma = 0;
    for (i = 0; i < N; i++) {
        soma += v[i];
        Ac[i] = soma;
    }
}

//39. Verifica se matriz é triangular Superior
int triSup (int N, float m[N][N]) {
    int i, j;
    for (j = 0; j < N; j++) {
        for (i = j + 1; i < N; i++) {
            if (m[i][j] != 0)
                return 0;
        }
    }
    return 1;
}
//40. Matriz transposta
void transposta (int N, float m [N][N]) {
    int i, j;
    int v[N][N];
    //cria uma nova matriz transposta
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            v[i][j] = m[j][i];
    }
    //copia matriz criada para a dada
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            m[i][j] = v[i][j];
    }
}

//41. Adiciona duas matrizes
void addTo (int N, int M, int a[N][M], int b[N][M]) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++)
            a[i][j] += b[i][j];
    }
}
//42. União de dois conjuntos
int unionSet (int N, int v1[N], int v2[N], int r[N]) {
    int i;
    for (i = 0; i < N; i++) {
        if (v1[i] == 1 || v2[i] == 1) {
            r[i] = 1;
        } else r[i] = 0;
    }
    return 0;
}
//43. Interseção de dois conjuntos
int intersectSet (int N, int v1[N], int v2[N], int r[N]) {
    int i;
    for (i = 0; i < N; i++) {
        if (v1[i] == 0 || v2[i] == 0)
            r[i] = 0;
        else r[i] = 1;
    }
    return 0;
}

//44. Interseção de multiconjuntos
int intersectMSet (int N, int v1[N], int v2[N], int r[N]) {
    int i;
    for (i = 0; i < N; i++) {
        if (v1[i] == 0 || v2[i] == 0)
            r[i] = 0;
        else if (v1[i] > v2[i])
            r[i] = v2[i];
        else r[i] = v1[i];
    }
    return 0;
}

//45.União de multiconjuntos
int unionMSet (int N, int v1[N], int v2[N], int r[N]) {
    int i;
    for (i = 0; i < N; i++) {
        if (v1[i] > v2[i])
            r[i] = v1[i];
        else r[i] = v2[i];
    }
    return 0;
}

//46. Nº de elementos do multiconjunto
int cardinalMSet (int N, int v[N]) {
    int i, soma = 0;
    for (i = 0; i < N; i++)
        soma += v[i];
    return soma;
}

//47.Posição final do robot após sequência de movimentos
typedef enum movimento {
    Norte, Oeste, Sul, Este
} Movimento;

typedef struct posicao {
    int x, y;
} Posicao;

Posicao posFinal (Posicao inicial, Movimento mov[], int N) {
    int i;
    for (i = 0; i < N; i++) {
        if (mov[i] == Norte) {
            inicial.y += 1;
        } else if (mov[i] == Sul) {
            inicial.y -= 1;
        } else if (mov[i] == Oeste) {
            inicial.x -= 1;
        } else {
            inicial.x += 1;
        }
    }
    return inicial;
}
//48. Caminho de posições
int caminho (Posicao inicial, Posicao final, Movimento v[], int N) {
    int i, a;

    if (abs(final.x - inicial.x + final.y - inicial.y) > N) {
        return (N - abs(final.x - inicial.x + final.y - inicial.y));
    } else {
        if (inicial.x > final.x) {
            for (i = 0; inicial.x > final.x; i++) {
                v[i] = Oeste;
                inicial.x = inicial.x - 1;
            }
        } else {
            for (i = 0; final.x > inicial.x; i++) {
                v[i] = Este;
                final.x = final.x - 1;
            }
        }
        if (inicial.y > final.y) {
            for (a = i; inicial.y > final.y; a++) {
                v[a] = Sul;
                inicial.y = inicial.y - 1;
            }
        } else {
            for (a = i; final.y > inicial.y; a++) {
                v[a] = Norte;
                final.y = final.y - 1;
            }
        }
    }
    return a;
}
//49. Posição mais perto da origem
int maiscentral (Posicao pos[], int N) {
    int index,i,distancia;
    index = 0;
    //distâcia à origem da primeira posição
    distancia = pos[0].x*pos[0].x + pos[0].y*pos[0].y;

    for (i = 1; i < N; i++) {
        if (pos[i].x*pos[i].x + pos[i].y*pos[i].y < distancia) {
            distancia = pos[i].x*pos[i].x + pos[i].y*pos[i].y;
            index = i;
        }
    }
    return index;
}
//50.Posições adjacentes (dist == 1)
//Poderia ter usado esta função em cima (oops)
int distancia (Posicao p, Posicao k) {
    int dist;
    dist = abs(p.x-k.x) + abs(p.y-k.y);
    return dist;
}

int vizinhos (Posicao p, Posicao pos[], int N) {
    int i, conta = 0;

    for (i = 0; i < N; i++) {
        if (distancia(p, pos[i]) == 1) {
            conta++;
        }
    }
    return conta;
}