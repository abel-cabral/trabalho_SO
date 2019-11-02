#ifndef TRABALHO_01_TRAB02_H
#define TRABALHO_01_TRAB02_H
#include "config.h"

typedef struct params {
    int operation; // Qual n deve possuir resto = 0
    int *initVet;  // Posição 0 do Vetor
    int *sizeVet;  // Tamanho do Vetor
    int current;  // Posição que esta sendo lida
    int *currentBrother; // Current do irmao
} Params;

int myGlobalVector[VETORGLOBAL];

void generateRandomNumber();
void removerDoVetor(Params *arg);
void checkVetor(Params *arg);
void buscarDoVetor(Params *arg);
void runTrab02();

#endif
