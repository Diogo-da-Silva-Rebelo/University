#include "process.h"

/* Implemente um programa que crie dez processos filhos que deverão executar em concorrência. O pai
deverá esperar pelo fim da execução de todos os seus filhos, imprimindo os respectivos códigos de saı́da. */
int main(int argc, char* argv[]) {
    int i;
    int status;

    for (i = 1; i < 11; i++) {
        pid_t pid;
        if ((pid = fork()) == 0) {
            //printf("%d\n", i);
            _exit(i);
        }
    }

    while(wait(&status) != -1) {
        //printf("status: %d\n", status);
        printf("Exit_status do processo-filho: %d\n", WEXITSTATUS(status));
    }

    return 0;
}