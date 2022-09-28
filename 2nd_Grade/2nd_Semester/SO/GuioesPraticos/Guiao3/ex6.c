#include "exec.h"
#define N 1024

/* Implemente uma versão simplificada da função system(). Ao contrário da função original, não tente
suportar qualquer tipo de redireccionamento, ou composição/encadeamento de programas executáveis.
O único argumento deverá ser uma string que especifica um programa executável e uma eventual lista de
argumentos. Procure que o comportamento e valor de retorno da sua função sejam compatíveis com a
original. */

int my_system(char* command) {
    char* args[N];
    char* token;
    char* rest = command;
    size_t i = 0;
    while((token = strtok_r(rest, " ", &rest)))
        args[i++] = strdup(token);
    args[i] = NULL;

    if(fork() == 0) {
        int exec_ret = execvp(args[0], args);
        _exit(exec_ret);
    }
    return;
}

int main(int argc, const char * argv[]) {
    char buffer[N];
    puts("Insert a command:");
    fgets(buffer, N, stdin);
    buffer[strcspn(buffer, "\n\r")] = 0;
    int ret = my_system(buffer);
    return 0;
}
