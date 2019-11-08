#include "trab01.h"
#include "trab02.h"
#include "trab03.h"

int main(int argc, char **argv) {
    int status;
    do {
        printf("Escolha uma parte do trabalho, 1 - 2 - 3 -> ");
        scanf("%d", &status);
    } while (status < 0 && status > 4);

    switch (status) {
        case 1:
            runTrab01();
            break;
        case 2:
            sem_init(&mutex, 0, 1);
            runTrab02();
            sem_destroy(&mutex);
            break;
        case 3:            
            runTrab03();            
            break;
    }
    return 0;
}