//--------------------------------------------------------------------
// command.c
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 1024

char* my_commands[] = {
    "/bin/ls",
    "/bin/pwd",
    "/bin/cat",
    "/bin/nano",
    "muda",
    "ajuda"
};

char* my_index[] = {
    "indice",
    "local",
    "mostra",
    "escreve",
    "muda",
    "ajuda"
};

const int num_cmd = sizeof(my_commands) / sizeof(char*);

void prompt() {
    fprintf(stdout, "%% ");
}

char* real_cmd(char* fake) {
    int i;
    
    if (fake) {
        for (i = 0; i < num_cmd; i++) {
            if (!strcmp(fake, my_index[i])) {
                return my_commands[i];
            }
        }
    }
    
    return NULL;
}

void read_cmd(char*** cmd, int* len) {
    char buffer[MAXLINE];
    char* token = NULL;
    int token_len = 0;
    
    if (fgets(buffer, MAXLINE, stdin) == NULL) *len = -1;
    else {
        buffer[strlen(buffer) - 1] = 0;
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
}

void cleanup(char*** cmd, int len) {
    int i;
    
    if (*cmd) {
        for (i = 0; i <= len; i++) {
            free((*cmd)[i]);
        }
        
        free((*cmd));
        (*cmd) = NULL;
    }
}

void muda(char** argv, int len) {
    char destdir[MAXLINE];
    
    if (len <= 1) {
        strncpy(destdir, ".", 2);
    }
    else {
        strncpy(destdir, argv[1], MAXLINE);
    }
    
    if (chdir(destdir)) {
        printf("Cannot change\n");
    }
}

void ajuda() {
    int i;
    for (i = 0; i < num_cmd; i++) {
        printf("%s\n", my_index[i]);
    }
}

int execute(char** argv, int len) {
    pid_t pid;
    int status;
    
    if (len > 0) {
        char* command = real_cmd(argv[0]);
        
        if (!command) {
            fprintf(stdout, "Comando inválido\n");
            return 1;
        }
        
        if (strcmp(command, "muda") == 0) {
            muda(argv, len);
            return 1;
        }
        
        if (strcmp(command, "ajuda") == 0) {
            ajuda();
            return 1;
        }
        
        if ((pid = fork()) < 0){
            fprintf(stderr, "fork error\n");
        }
        else if (pid == 0) {
            char* command = real_cmd(argv[0]);
            execv(command, argv);
            
            fprintf(stderr, "couldn't execute: %s\n", argv[0]);
        }
        
        if ((pid = waitpid(pid, &status, 0)) < 0){
            fprintf(stderr, "waitpid error\n");
        }
        else {
            return 1;
        }
    }
    
    return 0;
}


int main(int argc, char** argv) {
    char** cmd = NULL;
    int len = 0;
    int repeat = 1;
    
    while (repeat) {
        prompt();
        read_cmd(&cmd, &len);
        repeat = execute(cmd, len);
        cleanup(&cmd, len);
    }
    
    fprintf(stdout, "\n");
    
    return EXIT_SUCCESS;
}
//--------------------------------------------------------------------
