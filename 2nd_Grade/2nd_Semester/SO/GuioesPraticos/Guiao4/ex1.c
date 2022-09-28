#include "dup.h"

/* Escreva um programa que redireccione o descritor associado ao seu standard input para o ficheiro
/etc/passwd, e o standard output e error respectivamente para saida.txt e erros.txt. */
int main (int argc, char* argv[]){

    int res = 0;
    int i = 0;
    char buffer;
    char line[1024];

    //setbuf(stdout, NULL); //Alternativa a fflush: desliga completamente o buffering.

    int ifd = open("/etc/passwd", O_RDONLY);
    int ofd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    int efd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);

    res = dup2(ifd,0);
    res = dup2(ofd,1);
    res = dup2(efd,2);

    /*
    int stdin_fd = dup2(input_fd, STDIN_FILENO);
    int stdout_fd = dup2(output_fd, STDOUT_FILENO);
    int stderr_fd = dup2(error_fd, STDERR_FILENO);
     */

    close(ifd);
    close(ofd);
    close(efd);

    //O código a seguir é para teste apenas!!
    int read_res;
    while ((read_res = read (0, &buffer, 1)) != 0){
        line[i] = buffer;
        i++;
        if(buffer =='\n') {
            write(1, line, i);
            write(2, line, i);
            printf("after write line\n");
            fflush(stdout); //se tivermos coisas presas num buffer com o descritor 1 é flushed para o ecrã!
            i = 0
        }
    }

    return 0;
}

