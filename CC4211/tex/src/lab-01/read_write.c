//--------------------------------------------------------------------
// read_write.c
#include <unistd.h>
#include <stdlib.h>

#define BUFFSIZE    1024
#define STDIN       0
#define STDOUT      1
#define STDERR      2

int main(void){
    char buffer[BUFFSIZE];
    int read_chars = 0;

    while((read_chars = read(STDIN, buffer, BUFFSIZE)) > 0) {
        write(STDOUT, buffer, read_chars);
    }
    
    return EXIT_SUCCESS;
}
//--------------------------------------------------------------------
