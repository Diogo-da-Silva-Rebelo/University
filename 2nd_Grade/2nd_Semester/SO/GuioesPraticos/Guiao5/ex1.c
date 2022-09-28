#include "pipe.h"

/* Escreva um programa que crie um pipe anónimo e de seguida crie um processo filho. Relembre que as
associações dos descritores de ficheiros são preservadas na criação do processo filho. Experimente o pai
enviar uma linha de texto através do descritor de escrita do pipe, e o filho receber uma linha a partir do
respectivo descritor de leitura. Note que a informação foi transferida do pai para o filho. Experimente
de seguida provocar um atraso antes do pai enviar a linha de texto (p. ex., sleep(5)). Note agora que
a leitura do filho bloqueia enquanto o pai não realizar a operação de escrita no pipe. Experimente agora
inverter os papeis de modo à informação ser transmitida do filho para o pai. */

//pai2filho: mensagem do pai para o filho, logo o pai vai escrver no fildes e o filho vai LER do fildes[0]!
int main (int argc, char const *argv[]) {
    int pipe_fd[2];
    int status;
    char line[40];
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
            read(pipe_fd[0], line, 40);
            write(STDOUT_FILENO, line, bytes);
            _exit(0);
            break;
            //caso do pai
        default:
            close(pipe_fd[1]);
            char *str = "teste";
            //sleep(5);
            write(pipe_fd[1], str, strlen(str));
            close(pipe_fd[1]);
            wait(&status);
    }
    return 0;
}