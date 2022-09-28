#include "pipe.h"

/* Acrescente ao interpretador de comandos proposto nos guiões anteriores a possibilidade de encadear as
entradas e saı́das de programas a executar através de pipes anónimos (operador |). */

/* Esquema com pseudocódigo:
 * for (i=0; i < n_comandos; i++){
 *           if(i=0){
 *           pipe();
 *           switch(fork());
 *
 *           else{ if (i = n_comandos -1 ){
 *
 *                  switch(fork())
 *
 *                  } else{
 *                  pipe();
 *                  switch(fork())
 *                  }
 *                  }
 */
int main() {
    int pipefd[2];

    int res = pipe(pipefd);

    if(res < 0) {
        perror("Erro na criação do pipe!");
        _exit(1);
    }

    switch (fork()) {
        case -1:
            perror("Erro na criação do processo filho!");
            _exit(1);
        case 0:
            close(pipefd[0]);
            dup2(pipefd[1], 1);
            close(pipefd[1]);
            execlp("cat", "cat", "message.txt", NULL);
            perror("Exec com algum erro!");
            _exit(1);
        default:
            close(pipefd[1]);

            switch (fork()) {
                case -1:
                    perror("Erro na criação do processo filho!");
                    _exit(1);
                case 0:
                    close(pipefd[1]);
                    dup2(pipefd[0], 0);
                    close(pipefd[0]);
                    execlp("wc", "wc", "-l", NULL);
                    perror("Erro no exec!");
                    _exit(1);
                default:
                    close(pipefd[0]);
                    wait(NULL);
                    wait(NULL);
            }
    }
    return 0;
}