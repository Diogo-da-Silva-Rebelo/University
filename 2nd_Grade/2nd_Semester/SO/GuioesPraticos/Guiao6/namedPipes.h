#ifndef SISTEMAS_OPERATIVOS_NAMEDPIPES_H
#define SISTEMAS_OPERATIVOS_NAMEDPIPES_H
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int mkfifo(const char *pathname, mode_t mode);
#endif //SISTEMAS_OPERATIVOS_NAMEDPIPES_H
