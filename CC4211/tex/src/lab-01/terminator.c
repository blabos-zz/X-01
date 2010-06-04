//--------------------------------------------------------------------
// terminator.c
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    pid_t pid_to_kill;
    
    if (argc < 2) {
        printf("Preciso de um pid para exterminar\n");
        return EXIT_FAILURE;
    }
    
    pid_to_kill = (pid_t)abs(atoi(argv[1]));
    
    printf("Hasta la vista %d\n", pid_to_kill);
    kill(pid_to_kill, SIGTERM);
    
    return EXIT_SUCCESS;
}
//--------------------------------------------------------------------
