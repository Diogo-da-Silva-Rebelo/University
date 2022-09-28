#include "process.h"

/* Implemente um programa que crie uma descendência em profundidade de dez processos, ou seja, o
processo cria um filho, este filho cria outro, e assim por diante até ao décimo nı́vel de descendência.
Cada processo deverá imprimir o seu PID e o PID do seu pai. */
int main(int argc, char* argv[]){
    int i;
    int status;

    for (i=1; i<11; i++){
        pid_t child_pid = getpid();
        pid_t father_pid = getppid();
        printf("O PID do filho é %d.\nO pid do pai é %d.\n", child_pid, father_pid);
        if(fork() != 0){
            int terminated_pid = wait(&status);
            printf("[PAI] Process %d exited, exit code %d.\n", terminated_pid, WEXITSTATUS(status));
            _exit(i);
        }
    }
    return 0;
}
//OBS. exit code dá a ordem peça qual os processos terminam!