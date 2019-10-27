#include "./trab03.h"

int *glob_var;

void runTrab03(){
    int N_PROCESS = 2;
    int *endGlobalVet;
    int *status;
    pid_t pid;
    Params2 params[N_PROCESS];
    glob_var = mmap(NULL, sizeof *glob_var * sizeof(int) * VETORGLOBAL, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    endGlobalVet = mmap(NULL, sizeof endGlobalVet, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    status = mmap(NULL, sizeof *status, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *status = 0;
    *endGlobalVet = 0;

    generateRandomNumber2();

    // Remover Pares e Multiplos de 5
    params[0].operation = 2;
    params[1].operation = 5;

    for(int i = 0; i < N_PROCESS; i++) {
        params[i].current = (VETORGLOBAL) - 1;
        params[i].endVet = endGlobalVet;
    }

    pid = fork();

    // Se 0 é um filho, se alguma coisa é o id do pai, se menor que 0 error ao realizar fork
    switch (pid) {
        case -1:
            printf("Error ao iniciar processor filho\n");
            break;
        case 0:
            while (true) {
                if (*status == 1) break;
                wait(1);
            }
            printf("INICIANDO PROCESSO FILHO\n");
            buscaDoVetor2(&params[1]);
            // imprimirVetor2(glob_var, VETORGLOBAL, *params[1].endVet);
            *status = 0;
            break;
        default:
            printf("INICIANDO PROCESSO PAI\n");
            buscaDoVetor2(&params[0]);
            // imprimirVetor2(glob_var, VETORGLOBAL, *params[0].endVet);
            *status = 1;
            while (true) {
                if (*status == 0) break;
                wait(1);
            }
    }



}

void generateRandomNumber2() {
    for (int i = 0; i < VETORGLOBAL; i++) {
        glob_var[i] = rand() % 100 + 1;
    }
}

void buscaDoVetor2(Params2 *arg) {
    while (arg->current >= *(arg->endVet)) {
        if ((glob_var[arg->current] % arg->operation) != 0 ) {
            arg->current = (arg->current - 1);
            continue;
        }
        removeDoVetor2(arg);
        arg->current = (VETORGLOBAL) - 1;
    }
    if (arg->operation == 5) checkVetor2(arg);
    if (arg->operation == 2) checkVetor2(arg);
}

// Organiza da posicao de recebeu ate index 0
void removeDoVetor2(Params2 *arg) {
    int posicao = arg->current;
    while(posicao > *(arg->endVet)) {
        // Evita ciclos desnecessários de troca
        glob_var[posicao] = glob_var[posicao - 1];
        posicao--;
    }
    *(arg->endVet) = (*(arg->endVet) + 1);          // Diminui o Vetor conforme fazemos remocoes e realocacoes
}

// Busca elementos y com resto 0 no vetor
void checkVetor2(Params2 *arg) {
    int status = 1;
    int auxIndex = VETORGLOBAL - 1;
    while (auxIndex >= *(arg->endVet)) {
        if (glob_var[auxIndex] != 0) {
            if(glob_var[auxIndex] % arg->operation == 0) {
                status = 0;
                printf("Encontrei o número %d na posicao: %d do vetor\n", glob_var[auxIndex], auxIndex);
            }
        }
        auxIndex--;
    }
    if(status) {
        printf("NENHUMA OCORRÊNCIA ENCONTRADA PARA %d\n", arg->operation);
    }
}

void imprimirVetor2(int *vetor, int size, int last) {
    int auxIndex = size - 1;
    printf("\n---------------------------INICIO--------------------------------\n");
    while (auxIndex >= last) {
        if (vetor[auxIndex] != 0) {
            printf("%d\t", vetor[auxIndex]);
        }
        auxIndex--;
    }
    printf("\n---------------------------FIM--------------------------------\n");
}