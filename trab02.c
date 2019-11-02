#include "trab02.h"

void runTrab02() {
    int N_THREADS = 2;
    int initVet = 0;
    int sizeVet = (VETORGLOBAL) - 1;
    Params params[N_THREADS];
    pthread_t threads[N_THREADS];

    // Remover Pares e Multiplos de 5
    params[0].operation = 2;
    params[0].currentBrother = &params[1].current;
    params[1].operation = 5;
    params[1].currentBrother = &params[0].current;

    generateRandomNumber();

    for (int i = 0; i < N_THREADS; i++) {
        params[i].initVet = &initVet;
        params[i].sizeVet = &sizeVet;
        params[i].current = sizeVet;
        pthread_create(&(threads[i]), NULL, (void *) buscarDoVetor, (void *) &(params[i]));
    }

    for (int i = 0; i < N_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

void generateRandomNumber() {
    for (int i = 0; i < VETORGLOBAL; i++) {
        myGlobalVector[i] = rand() % 100 + 1;
    }
}

// Cada Thread roda uma 'instancia' de buscaDoVetor
void buscarDoVetor(Params *arg) {
    printf("\n\nTHREAD %d INICIADA:\n", pthread_self());    
    while (*(arg->sizeVet) >= *(arg->initVet)) {     

        if ((myGlobalVector[arg->current] % arg->operation) != 0) {
            arg->current = (arg->current - 1);                     
            continue;
        }
        
        sem_wait(&mutex);
        /* ############ ZONA CRÍTICA ################ */
        removerDoVetor(arg);
        /* ############ FIM ZONA CRÍTICA ################ */
        sem_post(&mutex);        
        //arg->current = (arg->current - 1);
    }
    if (arg->operation == 5) checkVetor(arg);
    if (arg->operation == 2) checkVetor(arg);
    pthread_exit(0);
}

// Organiza da posicao de recebeu ate index 0
void removerDoVetor(Params *arg) {
    int auxCurrent = arg->current;    
    while (auxCurrent < *(arg->sizeVet)) {        
        myGlobalVector[auxCurrent] = myGlobalVector[auxCurrent + 1];
        auxCurrent++;
    }   

    *(arg->sizeVet) = (*(arg->sizeVet) - 1);        // Diminui tamanho do vet
    arg->current = (arg->current - 1);              // Current atualiza

    if (arg->current > *(arg->sizeVet)) {           // Ajusta o current do irmao
        *(arg->currentBrother) = (*(arg->currentBrother)) + 1;
    }
}

// Busca elementos y com resto 0 no vetor
void checkVetor(Params *arg) {
    int status = 1;
    int auxCurrent = VETORGLOBAL - 1;
    while (auxCurrent >= *(arg->initVet)) {
        if (myGlobalVector[auxCurrent] != 0) {
            if (myGlobalVector[auxCurrent] % arg->operation == 0) {
                status = 0;
                printf("Encontrei o número %d na posicao: %d do vetor\n", myGlobalVector[auxCurrent], auxCurrent);
            }
        }
        auxCurrent--;
    }
    if (status) {
        printf("NENHUMA OCORRÊNCIA ENCONTRADA PARA %d\n", arg->operation);
    }
}