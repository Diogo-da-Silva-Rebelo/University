#include "files.h"

/* Ex.1: Implemente em C um programa mycp com funcionalidade similar ao comando cp. Varie o tamanho do
 * buffer usado e meça o tempo necessário para copiar um ficheiro de grande dimensão. Não esquecer de
 * criar o ficheiro de origem.*/
int main(int argc, char *argv[]){
    void *buffer = malloc(BUF_SIZE);
    int desc_origin, desc_dest;

    desc_origin = open(argv[1],O_RDONLY);
    desc_dest = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, 0640);


    if (desc_origin == -1) {
        perror("open");
        printf("open error: %d texto: %s\n", errno, strerror(errno));
        return -1;
    }
    if (desc_dest == -1){
        perror("open");
        return -1;
    }

    //não esquecer que o valor dos bytes lidos têm de ser atualizados!
    int bytes_read;
    while (bytes_read > 0) {
        bytes_read = read(desc_origin, buffer, bytes_read);
        write(desc_dest, buffer, bytes_read);
    }

    close(desc_origin);
    close(desc_dest);

    return 0;
}
/* Como temos de assumir que o ficheiro não cabe todo em memória, usamos malloc para alocar dinamicamente memória;
 * Ao fazer variar o tamanho do buffer,verificamos que o tempo de execução é tanto maior quanto menor o tamanho do buffer;
 * O aceso ao disco é mais lento, logo, por casa system call, mais lento o programa fica. Assim, com um BUF_SIZE grande,
 * vamos ter menos invocações das nossas funções myreadln e myreadln2, pelo que é executado o programa em menos tempo! */