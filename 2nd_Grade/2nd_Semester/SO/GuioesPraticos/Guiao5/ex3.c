#include "pipe.h"
#include "../Guiao1/Functions/files.h"
#include "../Guiao4/dup.h"

/* Escreva um programa que execute o comando wc num processo filho. O processo pai deve enviar ao
filho através de um pipe anónimo uma sequência de linhas de texto introduzidas pelo utilizador no seu
standard input. Recorra à técnica de redireccionamento estudada no guião anterior de modo a associar
o standard input do processo filho ao descritor de leitura do pipe anónimo criado pelo pai. Recorde a
necessidade de fechar o(s) descritor(es) de escrita no pipe de modo a verificar-se a situação de end of file. */

/* Read function of Ex4 (Guião 1) */
ssize_t myreadln2(int fd, char* line, size_t size) {
    ssize_t bytes_read = read(fd, line, size);
    if (!bytes_read) return 0;

    //definir tamanho da linha
    size_t length_line = strcspn(line, "\n") + 1; //retorna o tamanho entre o primeiro elemento de str1 e str2
    if (bytes_read < length_line) length_line = bytes_read;
    line[length_line] = 0;

    lseek(fd, length_line, SEEK_CUR);
    return length_line;
}

int main (int argc, char const *argv[]) {
    //Processo pai é o criador do pipe
    //Fazer fork antes de abandonar o pipe, para os filhos terem acesso
    //Write e Read bloqueantes

    int pipe_fd[2];
    int status;
    char line[64];
    int bytes;

    if (pipe(pipe_fd) < 0) {
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
            dup2(pipe_fd[0],STDIN_FILENO);
            close(pipe_fd[0]);
            execlp("wc","wc",NULL);
            break;

        default:
            close(pipe_fd[0]);

            while ((bytes = myreadln2(STDIN_FILENO,line,64) > 0))
                write(pipe_fd[1],line,bytes);

            write(pipe_fd[1], str, strlen(str));
            close(pipe_fd[1]);
            wait(&status);
    }
    return 0;
}