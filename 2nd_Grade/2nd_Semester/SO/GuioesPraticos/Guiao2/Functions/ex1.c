#include "process.h"

/* Implemente um programa que imprima o seu identificador de processo e o do seu pai. Comprove –
invocando o comando ps – que o pai do seu processo é o interpretador de comandos que utilizou para o
executar. */
int main(int argc, char const *argv[]) {
    pid_t main_pid = getpid();
    pid_t father_pid = getppid();
    printf("O PID do processo atual é %d.\nO pid do processo pai é %d.\n", main_pid, father_pid);
    return 0;
}