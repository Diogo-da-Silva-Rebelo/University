#ifndef SISTEMAS_OPERATIVOS_DUP_H
#define SISTEMAS_OPERATIVOS_DUP_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

/* chamadas ao sistema: defs e decls essenciais */
int dup(int fd);
int dup2(int fd1, int fd2);

#endif //SISTEMAS_OPERATIVOS_DUP_H
