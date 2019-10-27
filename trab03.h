#ifndef TRABALHO_01_TRAB03_H
#define TRABALHO_01_TRAB03_H
#include "config.h"

typedef struct params2 {
    int operation; // Qual n deve possuir resto = 0
    int current;   // Posiçao atual de leitura
    int *endVet;    // Ultima posicao do vetor
} Params2;

int myGlobalVector[VETORGLOBAL];

void generateRandomNumber2();
void removeDoVetor2(Params2 *arg);
void checkVetor2(Params2 *arg);
void imprimirVetor2(int *vetor, int size, int last);
void buscaDoVetor2(Params2 *arg);
void runTrab03();

#endif
