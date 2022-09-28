#include "dup.h"

/* Modifique o programa anterior de modo a que, depois de realizar os redireccionamentos, seja criado um
novo processo que realize operações de leitura e escrita. Observe o conteúdo dos ficheiros. Repare que o
processo filho “nasce” com as mesmas associações de descritores de ficheiros do processo pai. */

int main (int argc, char* argv[]){
    int res = 0;
    int res2 = 0;
    int i = 0;
    char buffer;
    char line[1024];
    int read_res;
    int wait_ret, status;

    //setbuf(stdout, NULL); //Alternativa a fflush: desliga completamente o buffering.

    int ifd = open("/etc/passwd", O_RDONLY);
    int ofd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int efd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

    int fdin = dup(0);
    int fdout = dup(1);
    int fderr = dup(2);

    res = dup2(ifd,0);
    res = dup2(ofd,1);
    res = dup2(efd,2);

    close(ifd);
    close(ofd);
    close(efd);

    int pid = -1;

    if ((pid = fork()) == 0) {
        while ((read_res = read(0, &buffer, 1)) != 0) {
            line[i] = buffer;
            i++;
            if (buffer == '\n') {
                write(1, line, i);
                write(2, line, i);
                printf("after write line\n");
                fflush(stdout); //se tivermos coisas presas num buffer com o descritor 1 é flushed para o ecrã!
                i = 0;
            }
        }
        _exit(0);
    }
    else {
        printf("Sou o pai %d\n", getpid());

        wait_ret = wait(&status);
        //Se quiser voltar a ter os descritores originais no pai:
        /* dup2(fdin,0);
         * dup2(fdout,1);
         * dup2(fderr,2);
         * close(fdin);
         * close(fdout);
         * close(fderr);
         */

        if (WEXITSTATUS(status)){
            printf("O filho retornou %d\n", WEXITSTATUS(status));
        }
        else {
            printf("O filho não terminou\n");
        }
    }
    return 0;
}
