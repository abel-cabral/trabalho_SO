#ifndef TRABALHO_01_TRAB02_H
#define TRABALHO_01_TRAB02_H
#include "config.h"

typedef struct params {
    int operation; // Qual n deve possuir resto = 0
    int current;   // Posiçao atual de leitura
    int *endVet;    // Ultima posicao do vetor
} Params;

int myGlobalVector[VETORGLOBAL];

void generateRandomNumber();
void removeDoVetor(Params *arg);
void checkVetor(Params *arg);
void imprimirVetor();
void buscaDoVetor(Params *arg);
void runTrab02();

#endif
