#include "dup.h"

//vemos na próxima aula!

/* Escreva um programa redir que permita executar um comando, opcionalmente redireccionando a en-
trada e/ou a saı́da. O programa poderá ser invocado, com:
redir [-i fich_entrada] [-o fich_saida] comando arg1 arg2 ... */

int main (int argc, char* argv[]){
    if (argc < 6) _exit(1);

    int input_fd;
    int output_fd;

    if (strcmp(argv[1], "-i") == 0)
        input_fd = open(argv[2], O_RDONLY);
    else _exit(1);

    if (strcmp(argv[3], "-o") == 0)
        output_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else _exit(1);

    dup(input_fd);
    dup(output_fd);

    argv[argc] = NULL;

    if (fork() == 0){
        execvp(argv[5], argv +5);
        _exit(1);
    }
    else wait(NULL);

    return 0;
}
