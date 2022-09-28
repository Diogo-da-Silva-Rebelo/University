#ifndef GUIAO0_API_H
#define GUIAO0_API_H

#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

//Estruturas da API
void fill(int* vector, int size, int value);
int find(int* vector, int size, int value);
int find_ind(int* vector, int value, int a, int b);
#endif
