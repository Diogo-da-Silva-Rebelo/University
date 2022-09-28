#include "files.h"

/* Ex.2: Implemente em C um programa mycat com funcionalidade similar ao comando cat, que lê do seu
* stdin e escreve para o seu stdout. Note-se que o descritor para o stdinput é 0 e do stdoutput é 1.*/
int main(int argc, char *argv[]){
    void *buffer[BUF_SIZE];
    int bytes_read;

    while ((bytes_read = read(0, buffer, BUF_SIZE))>0)
        write(1,buffer,bytes_read);

    return 0;
}
