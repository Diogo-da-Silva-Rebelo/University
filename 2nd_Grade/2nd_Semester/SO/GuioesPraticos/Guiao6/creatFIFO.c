#include "namedPipes.h"

int main(int argc, char const *argv[]) {
    int res;
    res = mkfifo("/tmp/fifo", 0644);
    if (res == -1){
        perror("Erro na criação do named PIPE!");
        _exit(1);
    }
    return 0;
}