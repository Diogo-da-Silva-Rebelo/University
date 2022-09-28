#ifndef SISTEMAS_OPERATIVOS_PROCESS_H
#define SISTEMAS_OPERATIVOS_PROCESS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/* chamadas ao sistema: defs e decls essenciais */
/* chamadas wait*() e macros relacionadas */

pid_t getpid(void);
pid_t getppid(void);
pid_t fork(void);
void _exit(int status);
pid_t wait(int *status);
pid_t waitPID(pid_t pid, int *status, int options);
//int WIFEXITED(int status); /* macro */
//int WEXITSTATUS(int status); /* macro */

#endif //SISTEMAS_OPERATIVOS_PROCESS_H
