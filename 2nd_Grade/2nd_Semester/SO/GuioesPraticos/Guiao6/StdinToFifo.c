#include "namedPipes.h"

int FakeMain(int argc, const char * argv[]){
    int bytes_read = 0;
    char* buf = malloc(sizeof (char)*1024);
    int fd = open("/tmp/fifo", O_WRONLY);

    while((bytes_read = read(0,buf,1024)) > 0){
        write(fd, buffer, bytesRead);
    }
    close(fd);
}

//Se o input for maior que 1024, há problemas!
//Sendo assim, o ideal é criar um função que lê uma linha e a copia para o fifo!
//Nova versão da main abaixo!

//Função que recebe um fd e lê uma linha do stdin
//Usamos ssize_t para permitir identificar erro em caso de -1
ssize_t myReadLn(int fd, char* line, size_t size){
    ssize_t bytes_read = 0;
    bytes_read = read(STDIN_FILENO,line,size);
     if (bytes_read < 0) {
         perror("Erro na leitura da linha!");
         return -1;
     } else if (bytes_read == 0) return 0;
     else {
        size_t line_len = 0;
        line_len = strcspn(line,"\n\r") + 1;
        if (bytes_read < line_len){
            line_len = bytes_read;
        }

        line[line_len] = 0;

         //o fd vai para o fim da linha para eu continuar a ler a partir daí!
         lseek(fd, length_line, SEEK_CUR);
         return length_line;
     }
}

int main(){
    int fd_fifo = open("tmp/fifo", O_WRONLY | O_TRUNC);
    size_t bytes_read = 0;
    char* buf = malloc(sizeof (char)*1024);

    while ((bytes_read = myReadLn(0,buf,1024)) > 0){
        write(fd_fifo,buf,bytes_read);
    }
    close(fd_fifo);
    return 0;
}
