#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define MAX_STR 1024

int main(int argc, char** argv) {
    char dir[MAX_STR];
    
    if (argc <= 1) {
        strncpy(dir, "~", MAX_STR);
    }
    else {
        strncpy(dir, argv[1], MAX_STR);
    }
    
    if (chdir(dir)) {
        printf("Cannot change\n");
    }
    
    return 0;
}
