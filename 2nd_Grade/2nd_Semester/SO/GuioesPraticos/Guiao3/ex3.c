#include "exec.h"

/* Implemente um programa que imprima a lista de argumentos recebidos na sua linha de comando. */

int main(int argc, char const *argv[]) {
    for (int i = 0; i < argc; i++){
        puts(argv[i]);
    }
    return 0;
}