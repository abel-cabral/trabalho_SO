#include "trab01.h"

void runTrab01() {
    int N_THREADS = 0;
    userInput(&N_THREADS);
    pthread_t threads[N_THREADS];
    Arguments args[N_THREADS];

    for (int i = 0; i < N_THREADS; i++) {
        args[i].n_thread = i;
        args[i].title = NAME_THREADS;
        pthread_create(&(threads[i]), NULL, thread_func, &(args[i]));
    }

    for (int i = 0; i < N_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

void *thread_func(void *arg) {
    Arguments *argument = (Arguments *) arg;
    char finalTitle[MAX_LIMIT];
    sprintf(finalTitle, "%s%d", argument->title, argument->n_thread);
   
    printf("Eu sou a %s e meu ID é %d(pthread_self) - %ld(gettid) \n", finalTitle, pthread_self(),
           syscall(SYS_gettid));   // Exibe o ID do thread
    pthread_exit(0);
}

void userInput(int *arg) {
    printf("Quantos Threads você deseja criar? ");
    scanf("%i", arg);
}