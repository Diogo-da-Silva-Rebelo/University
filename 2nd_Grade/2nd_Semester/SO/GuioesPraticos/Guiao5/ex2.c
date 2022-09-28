#include "pipe.h"

/* Modifique o programa anterior de modo à leitura do pipe ser realizada enquanto não for detectada a
situação de end of file no descritor respectivo. Repare que esta situação acontece apenas quando nenhum
processo – neste caso, pai e filho – têm aberto o descritor de escrita do pipe. */

int main (int argc, char const *argv[]) {
    int pipe_fd[2];
    int status;
    char line[64];
    int bytes;

    if (pipe(pipe_fd) == -1) {
        perror("pipe not created");
        return -1;
    }

    switch (fork()) {
//caso de erro
        case -1:
            perror("something went wrong with fork");
            return -1;
            break;
//caso do filho
//vai herdar os descritores do pai, daí podermos usar!
//os dois descritores (read & write) vêm abertos!
//fechamos os descritores que não são utilizados no processo-filho
        case 0:
            close(pipe_fd[1]);
            while (read(pipe_fd[0], buf, 64) > 0)
                printf("[FILHO]: read %c from pipe\n", buf);
            printf("[FILHO]: out of while");
            break;
//caso do pai
        default:
            close(pipe_fd[0]);
            char *str = "teste";
//sleep(5);
            write(pipe_fd[1], str, strlen(str));
            close(pipe_fd[1]);
            wait(&status);
    }
    return 0;
}