#ifndef PROGRAMA_O_IMPERATIVA_PESSOAS_H
#define PROGRAMA_O_IMPERATIVA_PESSOAS_H
typedef struct data {
    int ano, mes, dia;
} Data;

typedef struct pessoa {
    char nome [80];
    Data nascimento;
} Pessoa;
#endif //PROGRAMA_O_IMPERATIVA_PESSOAS_H
