#include "namedPipes.h"

/* Escreva três programas. O primeiro cria apenas um pipe com nome “fifo”. O segundo repete para este
pipe todas as linhas de texto lidas a partir do seu standard input. O terceiro programa deverá repetir
para o seu standard output todas as linhas de texto lidas a partir deste pipe. Repare que ao contrário dos
pipes anónimos, o pipe corresponde a uma entrada no sistema de ficheiros, sujeito ao mesmo controlo de
acesso dos ficheiros normais, e não obriga à criação do pipe por um processo ascendente dos processos
em comunicação. Aliás, a comunicação pode mesmo realizar-se entre processos de utilizadores distintos.
Note ainda. que tal como nos pipes anónimos, as operações de leitura e escrita no pipe oferecem um
canal unidireccional sob uma polı́tica FIFO e diluição da eventual fronteira das escritas. No entanto,
ao contrário dos pipes anónimos, a abertura para escrita de um pipe como nome bloqueia até que um
processo o abra para leitura, e vice-versa. */

//ver os respetivos programas nos outros ficheiros.

