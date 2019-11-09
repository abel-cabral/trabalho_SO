#ifndef TRABALHO_01_CONFIG_H
#define TRABALHO_01_CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/mman.h>

// Funcoes e definicoes
#define MAX_LIMIT 20
#define NAME_THREADS "thread_"
#define VETORGLOBAL 100000
#define true 1

// Necessarios para exclusao mutua
int sem_init(sem_t *mutex, int pshared, unsigned int value);
sem_t mutex;
#endif
