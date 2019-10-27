#include "trab02.h"

void runTrab02() {
    int N_THREADS = 2;
    int endVet = 0;
    Params params[N_THREADS];
    pthread_t threads[N_THREADS];

    generateRandomNumber();

    // Remover Pares e Multiplos de 5
    params[0].operation = 2;
    params[1].operation = 5;

    for (int i = 0; i < N_THREADS; i++) {
        params[i].current = (VETORGLOBAL) - 1;
        params[i].endVet = &endVet;
        pthread_create(&(threads[i]), NULL, (void *) buscaDoVetor, (void *) &(params[i]));
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
void buscaDoVetor(Params *arg) {
    printf("\n\nTHREAD %d INICIADA:\n", pthread_self());
    while (arg->current >= *(arg->endVet)) {
        if ((myGlobalVector[arg->current] % arg->operation) != 0) {
            arg->current = (arg->current - 1);
            continue;
        }
        sem_wait(&mutex);
        // Zona Crítica
        removeDoVetor(arg);
        // Fim Zona Crítica
        sem_post(&mutex);
        arg->current = (VETORGLOBAL) - 1;
    }
    if (arg->operation == 5) checkVetor(arg);
    if (arg->operation == 2) checkVetor(arg);
    pthread_exit(0);
}

// Organiza da posicao de recebeu ate index 0
void removeDoVetor(Params *arg) {
    int posicao = arg->current;
    while (posicao > *(arg->endVet)) {
        // Evita ciclos desnecessários de troca
        myGlobalVector[posicao] = myGlobalVector[posicao - 1];
        posicao--;
    }
    *(arg->endVet) = (*(arg->endVet) + 1);          // Diminui o Vetor conforme fazemos remocoes e realocacoes
}

// Busca elementos y com resto 0 no vetor
void checkVetor(Params *arg) {
    int status = 1;
    int auxIndex = VETORGLOBAL - 1;
    while (auxIndex >= *(arg->endVet)) {
        if (myGlobalVector[auxIndex] != 0) {
            if (myGlobalVector[auxIndex] % arg->operation == 0) {
                status = 0;
                printf("Encontrei o número %d na posicao: %d do vetor\n", myGlobalVector[auxIndex], auxIndex);
            }
        }
        auxIndex--;
    }
    if (status) {
        printf("NENHUMA OCORRÊNCIA ENCONTRADA PARA %d\n", arg->operation);
    }
}

void imprimirVetor() {
    int auxIndex = VETORGLOBAL - 1;
    printf("\n---------------------------INICIO--------------------------------\n");
    while (auxIndex >= 0) {
        if (myGlobalVector[auxIndex] != 0) {
            printf("%d\t", myGlobalVector[auxIndex]);
        }
        auxIndex--;
    }
    printf("\n---------------------------FIM--------------------------------\n");
}