#ifndef SISTEMAS_OPERATIVOS_SIGNAL_H
#define SISTEMAS_OPERATIVOS_SIGNAL_H

#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
int kill(pid_t pid, int sig);
unsigned int alarm(unsigned int seconds);
int pause(void);

#endif //SISTEMAS_OPERATIVOS_SIGNAL_H
