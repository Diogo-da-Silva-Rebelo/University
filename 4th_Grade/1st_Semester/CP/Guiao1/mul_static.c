//multiplicação estática de matrizes
#include <stdio.h>

int main() {
    int r1, c1, r2, c2;
    //printf("Insira dimensões [r1, c1, r2, c2]: ");
    //scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
    r1 = c1 = r2 = c2 = 512;

    float m1[r1][c1];
    float m2[r2][c2];
    float mul[r1][c2];

    //if (c1 == r2) {
        int i, j, k;
        //inicializar matriz 1
        //printf("\nMatriz 1:\n");
        for (i = 0; i < r1; i++) {
            for (j = 0; j < c1; j++) {
                m1[i][j] = (float) (i + j + 1);
                printf("%.1f ", m1[i][j]);
            }
            printf("\n");
        }

        //inicializar matriz 2
        //printf("\nMatriz 2:\n");
        for (i = 0; i < r2; i++) {
            for (j = 0; j < c2; j++) {
                m2[i][j] = (float) (i + j + 1);
                printf("%.1f ", m2[i][j]);
            }
            printf("\n");
        }

        //multiplicar matrizes
        for (i = 0; i < r1; i++) {
            for (j = 0; j < c2; j++) {
                mul[i][j] = 0;
                for (k = 0; k < c1; k++) {
                    mul[i][j] += m1[i][k] * m2[k][j];
                }
            }
        }

        //imprimir resultado
        /*
        printf("\nMatrix Resultado: \n");
        for (i = 0; i < r1; i++) {
            for (j = 0; j < c2; j++) {
                printf("%.1f ", mul[i][j]);
            }
            printf("\n");
        }
         */

        return 0;
    }
    //else {
    //  perror("As dimensões das matrizes não permitem multiplicação (c1 != r2). ");
    //  main();
    //}
//}
