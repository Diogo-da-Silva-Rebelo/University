#ifndef SISTEMAS_OPERATIVOS_FILES_H
#define SISTEMAS_OPERATIVOS_FILES_H
#define BUF_SIZE 1000
#define LINE_SIZE 100
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>

//Estrutura de dados para o ficheiro person.c
typedef struct Pessoa{
    char nome[120];
    int idade;
} PESSOA;

/* O_RDONLY, O_WRONLY, O_CREAT, O_*
int open(const char *path, int oflag [, mode]);
ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t write(int fildes, const void *buf, size_t nbyte);
off_t lseek(int fd, off_t offset, int whence);
close(int fildes);*/

ssize_t myreadln(int fd, char* line, size_t size);
ssize_t myreadln2(int fd, char* line, size_t size);

#endif //SISTEMAS_OPERATIVOS_FILES_H
