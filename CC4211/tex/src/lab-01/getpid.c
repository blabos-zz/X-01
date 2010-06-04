//--------------------------------------------------------------------
// getpid.c
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    printf("Current process ID: %d\n", getpid());
    return EXIT_SUCCESS;
}
//--------------------------------------------------------------------
