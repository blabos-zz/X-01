//--------------------------------------------------------------------
// loop.c
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    struct timespec tv;
    tv.tv_sec  = (time_t)(5);           // Configurando timer para 5
    tv.tv_nsec = (long)(0);             // segundos
    
    printf("Current process ID: %d\n", getpid());
    
    while (1) {
        printf("Aguardando 5 sec\n");
        nanosleep(&tv, &tv);
    }
    return EXIT_SUCCESS;
}
//--------------------------------------------------------------------
