//--------------------------------------------------------------------
// minishell.c
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFSIZE    1024
#define STDIN       0
#define STDOUT      1
#define STDERR      2

int main(int argc, char** argv) {
    char buffer[BUFFSIZE];
    pid_t pid;
    int status, read_chars;
    
    while (1) {
        // prompt
        write(STDOUT, "% ", 2);
        
        if ((read_chars = read(STDIN, buffer, BUFFSIZE)) <= 0) break;
        
        buffer[--read_chars] = '\0';
        if (!read_chars) continue;
        
        if((pid = fork()) < 0) {
            write(STDERR, "fork error\n", 11);
        }
        else if (pid == 0){
            // Child
            execve(buffer, NULL, NULL);
            write(STDERR, "couldn't execute: ", 18);
            write(STDERR, buffer, read_chars);
            write(STDERR, "\n", 1);
            return 127;
        }
        
        // parent
        if((pid = waitpid(pid, &status, 0)) < 0) {
            write(STDERR, "waitpid error\n", 14);
        }
    }
    
    write(STDOUT, "\n", 1);
    return EXIT_SUCCESS;
}
//--------------------------------------------------------------------
