#ifndef SISTEMAS_OPERATIVOS_EXEC_H
#define SISTEMAS_OPERATIVOS_EXEC_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "errno.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/* chamadas ao sistema: defs e decls essenciais */
/*
int execl(const char *path, const char *arg0, ...,NULL);
int execlp(const char *file, const char *arg0,...,NULL);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
*/

#endif //SISTEMAS_OPERATIVOS_EXEC_H
