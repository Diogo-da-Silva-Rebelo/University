#include "signal.h"

/* Usando SIGINT, SIGQUIT e SIGALRM, escreva um programa que vá contando o tempo em segundos
desde que começou. Se, entretanto, o utilizador carregar em Ctrl+C, o programa deverá imprimir o
tempo passado. Se carregar em Ctrl+\ o programa deverá indicar quantas vezes o utilizador carregou
em Ctrl+C e terminar de seguida. */

unsigned int seconds = 0;
unsigned int ctrl_c = 0;

void sigint_handler(int signum) {
    clock_t end = clock();
    ctrl_c++;
    printf("received[%d] %d executing...\n", signum, seconds);

}

void sigquit_handler(int signum) {
    printf("received[%d] called CTRL+C %d times...\n", signum, ctrl_c);
    exit(0);
}

void sigalrm_handler(int signum) {
    seconds++;
    alarm(1);
}

int main(int argc, char const *argv[]){
    if(signal(SIGALRM,sigalarm_handler) == SIG_ERR){
        puts("SIGALARM ERROR");
        exit(1);
    }

    if (signal(SIGQUIT, sigquit_handler) == SIG_ERR){
        puts("SIGQUIT ERROR");
        exit(1);
    }

    if(signal(SIGINT, sigint_handler) == SIG_ERR){
        puts("SIGINT ERROR");
        exit(1);
    }

    //O alarm manda uma alarm de 1 em 1 segundo
    //mal é registado o código fica em pause
    //o ctrl+c quebra o pause e volta ao alarm
    //se o antigo ainda não acabou, então o novo substitui-lo

    alarm(1);
    while(1){
        //alarm(1);
        pause();
        //printf("teste\n");
    }
}
