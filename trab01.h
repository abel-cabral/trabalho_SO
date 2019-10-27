#ifndef TRABALHO_01_TRAB01_H
#define TRABALHO_01_TRAB01_H

#include "config.h"

typedef struct arguments {
    char *title;
    int n_thread;
} Arguments;

void *thread_func(void *arg);

void userInput(int *arg);

void runTrab01();

#endif
