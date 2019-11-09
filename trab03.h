#ifndef TRABALHO_01_TRAB03_H
#define TRABALHO_01_TRAB03_H
#include "config.h"
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */

typedef struct paramsB {
    int operation; // Qual n deve possuir resto = 0   
    int *sizeVet;  // Tamanho do Vetor
    int current;  // Posição que esta sendo lida
    int *currentBrother; // Current do irmao
} ParamsB;

int myGlobalVector[VETORGLOBAL];

void gerarNumeros_();
void removerDoVetor_(ParamsB *arg);
void checkVetor_(ParamsB *arg);
void buscarDoVetor_(ParamsB *arg);
void imprimirVetor_(int vetor[VETORGLOBAL], int tamanho);
void runTrab03();

#endif
