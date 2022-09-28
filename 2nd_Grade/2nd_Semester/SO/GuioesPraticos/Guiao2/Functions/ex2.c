#include "process.h"

/* Implemente um programa que crie um processo filho. Pai e filho devem imprimir o seu identificador de
processo e o do seu pai. O pai deve ainda imprimir o PID do seu filho. */

int main(int argc, char const *argv[]) {
    pid_t pid;
    int status;

    //optei por fazer com que o pai espere que o filho termina, para ver os pids mais organizados.
    if ((pid = fork()) == 0) {
        pid_t child_pid = getpid();
        pid_t childp_pid = getppid();
        printf("O PID do filho é %d.\nO PID do respetivo pai é %d.\n", child_pid, childp_pid);
        _exit(0);
    } else {
        wait(&status);
        if (pid != -1 && WIFEXITED(status)) {
            puts("Processo filho terminou normalmente.\n");
            int const exit_status = WEXITSTATUS(status);
            printf("Exit status do processor filho: %d\n", exit_status);
        }

        pid_t parent_pid = getpid();
        pid_t parentp_pid = getppid();
        pid_t parentChild_pid = pid;
        printf("O PID do pai é %d.\nO PID do pai do pai é %d.\nO PID do filho do pai inicial é %d.\n", parent_pid,
               parentp_pid, parentChild_pid);
    }
    return 0;
}