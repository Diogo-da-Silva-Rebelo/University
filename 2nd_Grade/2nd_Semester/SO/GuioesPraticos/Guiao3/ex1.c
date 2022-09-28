#include "exec.h"

int main(int argc, char** argv) {
    /* Alguns aspetos a ter em conta:
     * -> e se o comando não existir e o exec retornar erro?
     * -> e quando mudamos arg0?
     */

    int ret;
    ret = execlp("ls","-l",NULL);
    printf("Erro. Resultado do ret = %d\n", ret);
    perror("reached return");

    /* Existiriam outras formas de chamar o comando -ls
     * char * exec_args[] = {"/bin/ls","l", NULL};
     * -> ret = execl("/bin/ls","-l", NULL);
     * -> ret = execv("/bin/ls", exec_args);
     * -> ret = execvp("ls", exec_args)
     */

    return 0;
}