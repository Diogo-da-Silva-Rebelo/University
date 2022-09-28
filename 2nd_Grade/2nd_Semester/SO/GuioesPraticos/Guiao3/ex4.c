#include "exec.h"

/* Implemente um programa que execute o programa da questão anterior com uma qualquer lista de argu-
mentos. Mantendo o nome do ficheiro que corresponde o programa executável, experimente alterar o
primeiro elemento da lista de argumentos (índice zero do argv). */

int FakeMain(void){
    char *buf = malloc(sizeof(char)*1024);
    size_t i = 1, len;
    char* args[1024];

    strcpy(args[0],"./ex3");
    while (getline(&buf,&len,stdin)>0) {
        buf[strcspn(buf,"\n\r")] = 0;
        strcpy(args[i++],strdup(buf));
    }

    (args[i]) = NULL;
    execv("./ex3",args);

    return 0;
}

int main (int argc , char* argv[]){

    pid_t pid = fork();
    if(pid==0){
        /* processo filho*/
        argv[0]= "já não é ./run";
        execvp("./ex3",argv);
        _exit(0);
    }
    else{
        int status;
        /* processo pai*/
        wait(&status);
    }
    return 0;
}

//Antes de executar: não esquecer que o programa precisa do executável do ex3, ou seja, ./ex3