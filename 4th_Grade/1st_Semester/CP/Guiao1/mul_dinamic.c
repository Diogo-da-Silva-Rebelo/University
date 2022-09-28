//multiplicação dinâmica de matrizes
//divisão por funções
#include "stdlib.h"
#include "stdio.h"

//função que cria uma matriz de dimensão row * col
int** createM (int row, int col){
    int** matrix;
    matrix = malloc(sizeof (int*) * row);
    for(int i = 0 ; i < row ; i++)
        matrix[i] = malloc( sizeof(int) * col);
    return matrix;
}

//função que inicializa uma matriz desde "value"
void initM (int row, int col, int value, int ** matrix){
    int i, j;
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++) {
            matrix[i][j] = value++;
        }
}

//função que multiplica as duas matrizes
void multM (int r1, int r2, int c1, int c2, int **m1, int **m2, int ** res){
    int i, j, k;
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            res[i][j] = 0;
            for (k = 0; k < c1; k++) {
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void free2Darray(int** matrix, int row) {
    int i;
    for (i = 0; i < row; i++)
        free(matrix[i]);
    free(matrix);
}

void print(int** matrix, int row, int col) {
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(){

    //testar com matriz quadrada 2x2, 512x512, etc.
    int **m1, **m2, **res;
    int row = 512, col = 512;
    m1 = createM(row, col);
    m2 = createM(row, col);
    res = createM(row, col);

    initM(row, col,1,m1);
    initM(row, col,1,m2);

    multM(row,row,col,col,m1,m2,res);

    //print(res,row, col);

    free2Darray(m1,row);
    free2Darray(m2,row);
    free2Darray(res, row);

    //utilizar o comando " sudo perf record ./a.out" e "perf report"

    return 0;
}


