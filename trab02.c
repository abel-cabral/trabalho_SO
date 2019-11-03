#include "trab02.h"

void runTrab02() {
    int N_THREADS = 2;   
    int sizeVet = (VETORGLOBAL) - 1;
    Params params[N_THREADS];
    pthread_t threads[N_THREADS];

    // Remover Pares e Multiplos de 5
    params[0].operation = 2;
    params[0].currentBrother = &params[1].current;
    params[1].operation = 5;
    params[1].currentBrother = &params[0].current;

    gerarNumeros();

    // imprimirVetor(myGlobalVector, sizeVet);

    for (int i = 0; i < N_THREADS; i++) {       
        params[i].sizeVet = &sizeVet;
        params[i].current = sizeVet;
        pthread_create(&(threads[i]), NULL, (void *) buscarDoVetor, (void *) &(params[i]));
    }

    for (int i = 0; i < N_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // imprimirVetor(myGlobalVector, sizeVet);
}

void gerarNumeros() {
    for (int i = 0; i < VETORGLOBAL; i++) {
        myGlobalVector[i] = rand() % 100 + 1;
    }
}

// Cada Thread roda uma 'instancia' de buscaDoVetor
void buscarDoVetor(Params *arg) {
    printf("\n\n----------------------------------\n");
    if (arg->operation == 5) 
        printf("MULTIPLOS DE 5\n");
    if (arg->operation == 2) 
        printf("MULTIPLOS DE 2\n");

    do {
        if ((myGlobalVector[arg->current] % arg->operation) != 0) {
            arg->current = (arg->current - 1);                     
            continue;
        }
        
        sem_wait(&mutex);
        /* ############ ZONA CRÍTICA ################ */
        removerDoVetor(arg);
        /* ############ FIM ZONA CRÍTICA ################ */
        sem_post(&mutex);       
    } while(arg->current > -1);

    if (arg->operation == 5)
        checkVetor(arg);
    
    if (arg->operation == 2)
        checkVetor(arg);    
}

// Organiza da posicao de recebeu ate index 0
void removerDoVetor(Params *arg) {
    int auxCurrent = arg->current;    
    while (auxCurrent < *(arg->sizeVet)) {        
        myGlobalVector[auxCurrent] = myGlobalVector[auxCurrent + 1];
        auxCurrent++;
    }   
        
    arg->current = (arg->current - 1);              // Atualizar current 
    *(arg->sizeVet) = (*(arg->sizeVet) - 1);        // Ajustar vetor
    if (*(arg->currentBrother) > *(arg->sizeVet))   // Atualizar brother
        *(arg->currentBrother) = (*(arg->currentBrother) - 1);
}

// Busca elementos y com resto 0 no vetor
void checkVetor(Params *arg) {
    int status = 1;    
    int tamanho = *(arg->sizeVet);

    for(int i = 0; i <= tamanho; i++) {
        if (myGlobalVector[i] % arg->operation == 0) {
                status = 0;
                printf("Encontrei o número %d na posicao: %d do vetor\n", myGlobalVector[i], i);
            }
    }
    if (status)
        printf("NENHUMA OCORRÊNCIA ENCONTRADA PARA %d\n", arg->operation);
    
}

// Imprime todos os elementos de um vetor passado
void imprimirVetor(int vetor[VETORGLOBAL], int tamanho) {
    printf("\n############################################\n");
    for(int i = 0; i <= tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n############################################\n");
}