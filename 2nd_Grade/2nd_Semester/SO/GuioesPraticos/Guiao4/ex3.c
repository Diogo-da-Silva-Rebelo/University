#include "dup.h"

/* Modifique novamente o programa inicial de modo a que seja executado o comando wc, sem argumentos,
depois do redireccionamento dos descritores de entrada e saı́da. Note que, mais uma vez, as associações
– e redireccionamentos – de descritores de ficheiros são preservados pela primitiva exec(). */

int main (int argc, char* argv[]){
    int res = 0;

    //equivalente a wc < /etc/passwd > saida.txt 2> erros.txt

    int ifd = open("/etc/passwd", O_RDONLY);
    int ofd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY);
    int efd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY);

    res = dup2(ifd,0);
    res = dup2(ofd,1);
    res = dup2(efd,2);

    close(ifd);
    close(ofd);
    close(efd);

    res = execlp("wc","wc", NULL);

    return 0;
}

