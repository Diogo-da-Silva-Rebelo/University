#include "exec.h"

/* Implemente um programa que execute concorrentemente uma lista de executáveis especificados como
argumentos da linha de comando. Considere os executáveis sem quaisquer argumentos próprios. O
programa deverá esperar pelo fim da execução de todos processos por si criados. */

int main(int argc, const char* argv[]) {
    //EX: ./programa <executavel1> <executavel2> ...
    for(size_t i = 1; i < argc; i++)
        if(fork() == 0)
            execlp(argv[i], argv[i], NULL);

    for(size_t i = 1; i < argc; i++)
        wait(NULL);
    return 0;
}
