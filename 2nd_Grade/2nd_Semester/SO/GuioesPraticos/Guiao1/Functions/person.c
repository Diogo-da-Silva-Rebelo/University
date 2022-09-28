#include "files.h"

/* Considere uma estrutura (struct) com dados de uma pessoa (nome, idade, ...) e um ficheiro binário que contém
 * registos organizados segundo esta estrutura. Não assuma que o ficheiro cabe todos em memória.
 * Escreva um programa que, consoante a opção, permita:
 * -> -i: Acrescentar pessoas a um ficheiro de dados (binario – a idade é um inteiro).
 * -> -u: Actualizar a idade de uma determinada pessoa no ficheiro de dados.
 * -> Exemplos:
 *  -> $ pessoas -i "José Mourinho" 55
 *  -> $ pessoas -u "José Mourinho" 56 */


int novaPessoa(int fd, const char *nome, int idade){
    if (fd == -1) {
        perror("Não foi possível abrir o ficheiro! ");
        return 1;
    }

    puts("Modo de inserção.");

    /* dá o resgisto em questão. Alguns aspetos importantes sobre a struct stat:
     * -> int fstat(int fd, struct stat *statbuf); fstat() is identical to stat(), except that the file about which
     * information is to be retrieved is specified by the file descriptor fd.
     * -> struct stat {
    dev_t     st_dev;      ID of device containing file
    ino_t     st_ino;         Inode number
    mode_t    st_mode;        File type and mode
    nlink_t   st_nlink;       Number of hard links
    uid_t     st_uid;         User ID of owner
    gid_t     st_gid;         Group ID of owner
    dev_t     st_rdev;        Device ID (if special file)
    off_t  -> st_size;        Total size, in bytes
    blksize_t st_blksize;     Block size for filesystem I/O
    blkcnt_t  st_blocks;      Number of 512B blocks allocated
     */

    struct stat st;
    fstat(fd, &st);
    off_t filesize = st.st_size;
    int position = (int)filesize / sizeof(struct Pessoa);

    PESSOA p1;
    strcpy(p1.nome,nome);
    p1.idade = idade;
    lseek(fd,0,SEEK_END);
    write(fd,&p1, sizeof(struct Pessoa));
    printf("Inserção concluída com sucesso - registo %d\n", position);

    return 0;
}

int atualizaPessoa(int fd, const char *nome, int idade) {
    int bytes_read = 0;

    if (fd == -1) {
        perror("ERROR - open file");
        return 1;
    }

    puts("Modo de atualização 1. Pessoa + idade ");

    PESSOA p1;
    lseek(fd, 0, SEEK_SET);
    while ((bytes_read = read(fd, &p1, sizeof(struct Pessoa))) > 0)
        if (!strcmp(nome, p1.nome)) {
        strcpy(p1.nome,nome);
        p1.idade = idade;
        lseek(fd, -sizeof(struct Pessoa), SEEK_CUR);
        write(fd, &p1, sizeof(struct Pessoa));
    }
    return 0;
}

int atualizaComIndex(int fd, int idade, int index) {
    //index é o registo que queremos alterar!
    if (fd == -1) {
        perror("Não foi possível abrir o ficheiro! ");
        return 1;
    }

    puts("Modo de edição com índice.");

    struct Pessoa p1;
    lseek(fd, index * sizeof(struct Pessoa), SEEK_SET);
    if (read(fd, &p1, sizeof(struct Pessoa)) <= 0) return 1;
    p1.idade = idade;
    lseek(fd, -(sizeof(struct Pessoa)), SEEK_CUR);
    write(fd, &p1, sizeof(struct Pessoa));
    return 0;
}

void verFicheiro(int fd, const char *nome, int idade){
    PESSOA p1; //Cria pessoa
    lseek(fd,0,SEEK_SET);
    int byte_read;
    while((byte_read = read(fd,&p1,sizeof(struct Pessoa))) > 0){
        printf("\t--------------------\n");
        printf("\tidade: %d\n\tnome: %s\n",p1.idade,p1.nome);
        printf("\t--------------------\n");
    }
}

int main(int argc, char const *argv[]) {

    /* Ideias a desenvolver:
     * -> 2 comandos que permitam inserir e alterar dados de pessoas, num determinado ficheiro.
     * -> Criar um ficheiro de leitura;
     * -> Programar a sua alteração e inserção;
     * -> Os registos começam em 0!!!
     * -> Não esquecer de utilizar o stdin e stdout, pois é a partir daí que os comandos serão utilizados! */

    if (argc != 4) {
        perror("Modo de inserção desrespeitado!\n");
        return 1;
    }

    int fd = open("registo", O_CREAT | O_RDWR , 0640);

    const char *nome = argv[2];
    int idade = atoi(argv[3]);

    switch (*(argv[1] + 1)) {

        case 'i':
            novaPessoa(fd, nome, idade);
            break;

        case 'u':
            if(isdigit(*argv[2])) atualizaComIndex(fd, idade, atoi(argv[2]));
            atualizaPessoa(fd, nome, idade);
            break;

        default:
            puts("Erro: modo inválido");
            break;
    }
    verFicheiro(fd, nome, idade);
    close(fd);
    return 0;
}
