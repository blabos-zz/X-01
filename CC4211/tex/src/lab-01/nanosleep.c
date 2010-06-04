//--------------------------------------------------------------------
// nanosleep.c
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    struct timespec tv;
    tv.tv_sec  = (time_t)(2);           // Configurando timer para 2
    tv.tv_nsec = (long)(0.5 * 1e+9);    // segundos e meio
    
    printf("0.0 sec\n");
    nanosleep(&tv, &tv);
    printf("2.5 sec\n");
    
    return EXIT_SUCCESS;
}
//--------------------------------------------------------------------
