#include "pipe.h"
#include "../Guiao1/Functions/files.h"
#include "../Guiao4/dup.h"

/* Escreva um programa que emule o funcionamento do interpretador de comandos na execução encadeada. */
// Ex: ls /etc | wc -l.

/* Como fazer:
 * 1. Pai: cria pipe; fork() x2; wait()x2;
 * 2. Filho 0: redireciona sdout para escrever no extremo de escrita do pipe; exec(ls /etc);
 * 3. Filho 1: redireciona sdtin para ler do extremos de leitura do pipe; exec(wc -l);
 * Notas: concorrência entre pai e filhos; exec herda descritores redirecionados;
*/

int main (int argc, char const *argv[]) {
    int pipe_fd[2];
    int status;

    if (pipe(pipe_fd) < 0) {
        perror("pipe not created");
        return -1;
    }

    //Filho 0
    switch (fork()) {
        case -1:
            perror("something went wrong with fork");
            return -1;
        case 0:
            close(pipe_fd[0]);
            dup2(pipe_fd[1],STDOUT_FILENO);
            close(pipe_fd[1]);
            execlp("/bin/ls","ls","/etc", NULL);
            _exit(0);
        default:
            wait(&status);
    }
    close(pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);

    //Filho1
    switch (fork()) {
        case -1:
            perror("something went wrong with fork");
            return -1;
        case 0:
            execlp("/bin/wc", "wc", "-l", NULL);
            _exit(0);
        default:
            wait(&status);
    }

    //para testar : ./ex4
    //4 comandos , 3 pipes
    // nº pipes = nºcomandos - 1
    return 0;
}