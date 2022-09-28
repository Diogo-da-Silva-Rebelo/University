#include "process.h"

/* Pretende-se determinar a existência de um determinado número inteiro nas linhas de numa matriz de
números inteiros, em que o número de colunas é muito maior do que o número de linhas. Implemente,
utilizando processos um programa que determine a existência de um determinado número, recebido como
argumento, numa matriz gerada aleatoriamente. */

/* Aspetos a ter em conta:
 * -> Como o numero de colunas é >> ao número de linhas, então, podemos adotar a estratégia de ter um processo filho por
 * linha que pequisa esse elemento. Enquanto o pai continua a percorrer as colunas.
 * -> Alocamos um número de colunas >> número de linhas;
 * -> Note-se que a matriz é gerada aleatoriamente!
 */
int main(int argc, char* argv[]){

    if (argc < 2){
        printf("Usage: program <needle>\n");
        exit(-1);
    }

    pid_t pid;
    int needle = atoi(argv[1]);
    int rows = 10;
    int cols = 10000;
    int rand_max = 10000;
    int status;
    int **matrix;

    //Allocate and populate matrix with random numbers
    printf("Generating numbers from 0 to %d ... ", rand_max);
    matrix = (int **) malloc(sizeof (int*) * rows);
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*) malloc(sizeof (int) * cols);
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % rand_max;
        }
    }
    printf("Done.\n");

    for (int i = 0; i < rows; i++) {
        if ((pid = fork()) == 0){
            printf("[pid %d] row: %d\n", getpid(), i);

            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == needle) _exit(i);
            }
            _exit(-1);
        }
    }


    for (int i = 0; i < rows; i++){
        pid_t terminated_pid = wait(&status);

        if(WIFEXITED(status)) {
            if (WEXITSTATUS(status) < 255)
                printf("[pai] process %d exited. found number at row %d: ", terminated_pid, WEXITSTATUS(status));
            else
                printf("[pai] process %d exited. nothing found\n", terminated_pid);
        }
        else
            printf("[pai] process %d exited. something went wrong\n", terminated_pid);
        }
    return 0;
}