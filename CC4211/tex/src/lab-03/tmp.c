#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 1024

void read_cmd(char*** cmd, int* len) {
    char buffer[MAXLINE];
    char* token = NULL;
    int token_len = 0;
    
    strncpy(buffer, "   command arg1    arg2 arg3 arg4", MAXLINE);
    
    
    *len = 0;
    *cmd = 0;
    token = strtok(buffer, " ");
    while (token) {
        (*len)++;
        token_len = strlen(token);
        
        (*cmd) = (char**)realloc((*cmd), (*len) * sizeof(char*));
        (*cmd)[(*len) - 1] = (char*)malloc((token_len + 1) * sizeof(char));
        strncpy(((*cmd)[(*len) - 1]), token, (token_len + 1));
        
        token = strtok(NULL, " ");
    }
    
    (*cmd) = (char**)realloc((*cmd), ((*len) + 1) * sizeof(char*));
    (*cmd)[(*len)] = (char*)malloc(sizeof(char));
    ((*cmd)[(*len)]) = NULL;
}

void cleanup(char*** cmd, int len) {
    int i;
    
    for (i = 0; i <= len; i++) {
        free((*cmd)[i]);
    }
    
    free((*cmd));
}

int main(int argc, char** argv) {
    char** cmd;
    int len, i;
    read_cmd(&cmd, &len);
    
    for (i = 0; i <= len; i++) {
        printf("(%s)\n", cmd[i]);
    }
    
    cleanup(&cmd, len);
    
    return EXIT_SUCCESS;
}

