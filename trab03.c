#include "./trab03.h"

int *glob_var;

void runTrab03(){       
    int N_PROCESS = 2;
    int *endGlobalVet;     
    ParamsB params[N_PROCESS];    
    int sizeVet = (VETORGLOBAL) - 1; 
    int *alternador;
   
    key_t shmkey;                 /*      shared memory key       */
    int shmid;                    /*      shared memory id        */
    sem_t *sem;                   /*      synch semaphore         */
    pid_t pid;                    /*      fork pid                */
    int *p;                       /*      shared variable         */

    /* cleanup semaphores */
    sem_unlink ("pSem");   
       
    /* initialize a shared variable in shared memory */
    shmkey = ftok ("/dev/null", 5);       /* valid directory name and a number */    
    shmid = shmget (shmkey, sizeof (int), 0644 | IPC_CREAT);
    if (shmid < 0){                           /* shared memory error check */
        perror ("shmget\n");
        exit (1);
    }

    p = (int *) shmat (shmid, NULL, 0);   /* attach p to shared memory */
    *p = 0;

    /* initialize semaphores for shared processes */
    sem = sem_open ("pSem", O_CREAT | O_EXCL, 0644, 1); 
    /* name of semaphore is "pSem", semaphore is reached using this name */

    //Memoria Compartilhada       
    glob_var = mmap(NULL, sizeof *glob_var * sizeof(int) * VETORGLOBAL, PROT_READ | PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, -1, 0);
    endGlobalVet = mmap(NULL, sizeof endGlobalVet, PROT_READ | PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, -1, 0);    
    alternador = mmap(NULL, sizeof alternador, PROT_READ | PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, -1, 0);     
    *endGlobalVet = 0;
    *alternador = 1;
    
    // Remover Pares e Multiplos de 5
    params[0].operation = 2;
    params[0].currentBrother = &params[1].current;
    params[1].operation = 5;
    params[1].currentBrother = &params[0].current;

    gerarNumeros_();
    
    for (int i = 0; i < N_PROCESS; i++) {       
        params[i].sizeVet = &sizeVet;
        params[i].current = sizeVet;        
    }

    pid = fork();

    // Se 0 é um filho, se alguma coisa é o id do pai, se menor que 0 error ao realizar fork
    switch (pid) {
        case -1:
            printf("Error ao iniciar processor filho\n");
            break;
        case 0:  
            // ################# PASSO 02  ################# //  
            while(*alternador);
            sem_wait(sem);   
            *alternador = 0;                 
            printf("INICIANDO PROCESSO FILHO\n");
            buscarDoVetor_(&params[1]);                
            *alternador = 1;  
            sem_post(sem);        

            // ################# PASSO 04  ################# //
            while(*alternador);
            sem_wait(sem);   
            *alternador = 0;                 
            checkVetor_(&params[1]);                    
            sem_post(sem);  
            break;
        default: 
            // ################# PASSO 01  ################# //
            sem_wait(sem);   
            *alternador = 0;
            printf("INICIANDO PROCESSO PAI\n");            
            buscarDoVetor_(&params[0]);   
            *alternador = 1;
            sem_post(sem);    

            // ################# PASSO 03  ################# //
            while(*alternador);
            sem_wait(sem);   
            *alternador = 0;                 
            checkVetor_(&params[0]);  
            *alternador = 1;                   
            sem_post(sem);  

            // ################# PASSO 05  ################# //
            while(*alternador);
            sem_wait(sem);  
            sem_unlink("pSem");   
            sem_close(sem); 
            printf("FIM DA OPERACAO\n");  
            exit(0);           
    }
}


void gerarNumeros_() {
    for (int i = 0; i < VETORGLOBAL; i++) {
        myGlobalVector[i] = rand() % 100 + 1;
    }
}

// Cada Thread roda uma 'instancia' de buscaDoVetor
void buscarDoVetor_(ParamsB *arg) {
    do {
        if ((myGlobalVector[arg->current] % arg->operation) != 0) {
            arg->current = (arg->current - 1);                     
            continue;
        }   
        removerDoVetor_(arg);        
    } while(arg->current > -1);
}

// Organiza da posicao de recebeu ate index 0
void removerDoVetor_(ParamsB *arg) {
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
void checkVetor_(ParamsB *arg) {
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
void imprimirVetor_(int vetor[VETORGLOBAL], int tamanho) {
    printf("\n############################################\n");
    for(int i = 0; i <= tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n############################################\n");
}