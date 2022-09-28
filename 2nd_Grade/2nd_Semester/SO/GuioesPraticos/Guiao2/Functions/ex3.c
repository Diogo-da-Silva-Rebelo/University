#include "process.h"
/* Implemente um programa que crie dez processos filhos que deverão executar sequencialmente. Para este
efeito, os filhos podem imprimir o seu PID e o do seu pai, e finalmente, terminarem a sua execução com
um valor de saı́da igual ao seu número de ordem (e.g.: primeiro filho criado termina com o valor 1). O
pai deverá imprimir o código de saı́da de cada um dos seus filhos. */
int main(int argc, char const *argv[]) {
    for (int i = 1; i < 11; i++) {
        if (fork() == 0) {
            printf("PID Filho: %d\n", getpid());
            printf("PID Pai: %d\n", getppid());
            _exit(i);
        }
        else {
            int exit_status;
            wait(&exit_status);
            printf("Exit: %d\n", WEXITSTATUS(exit_status));
        }
    }
    return 0;
}