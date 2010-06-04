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

int count_words(char* str) {
    int n = 1;
    
    do {
        if (*str == ' ') {
            ++n;
        }
    } while (*(str++));
    
    return n;
}

void new_parm_list(char* str, char*** list, int* size) {
    int i, words, len;
    char* token;
    
    *size = count_words(str);
    (*list) = (char**)malloc((*size + 1) * sizeof(char*));
    
    token = strtok(str, " ");
    for (i = 0; i < *size; i++) {
        len = strlen(token);
        (*list)[i] = (char*)malloc((len + 1) * sizeof(char));
        strncpy((*list)[i], token, len + 1);
        token = strtok(NULL, " ");
    }
    
    (*list)[*size] = (char*)malloc((len + 1) * sizeof(char));
    (*list)[*size] = NULL;
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

void del_list(char** list, int len) {
    int i;
    if (len) {
        for (i = 0; i <= len; i++) {
            free(list[i]);
        }
        free (list);
    }
}

void print_list(char** list, int len) {
    int i;
    for (i = 0; i < len; i++) {
        printf("list[%d] = (%s)\n", i, list[i]);
    }
}

void help() {
    int i;
    for (i = 0; i < num_cmd; i++) {
        printf("%s\n", my_index[i]);
    }
}

void prompt() {
    printf("%% ");
}

int main(int argc, char** argv, char** env)
{
    char* command;
    char** list;
    int len = 0;
    
    /**
     * Declarações diversas.
     * 
     * Declara um buffer de MAXLINE caracteres, uma variável pid_t e uma outra
     * variável inteira
     */
    char buf[MAXLINE];
    pid_t pid;
    int status;
    
    /**
     * Enquanto não for digitado Ctrl-D (EOF), repete a leitura de um comando
     * para ser executado pelo minishel
     */
    while (1) {
        prompt();
        if (fgets(buf, MAXLINE, stdin) == NULL) break;
        
        /**
         * Remove o caractere \n capturado ao final do comando
         */
        buf[strlen(buf) - 1] = 0;
        if (strlen(buf) <= 0) continue;
        
        del_list(list, len);
        new_parm_list(buf, &list, &len);
        command = real_cmd(list[0]);
        
        if (!command) {
            printf("Invalid command");
            continue;
        }
        
        if (!strcmp(command, "muda")) {
            char dir[MAXLINE];
            
            if (len > 1) {
                strncpy(dir, list[1], MAXLINE);
            }
            else {
                strncpy(dir, "~", MAXLINE);
            }
            
            if (chdir(dir)) {
                printf("Cannot change\n");
            } 
            
            continue;
        }
        
        if (!strcmp(command, "help")) {
            help();
            continue;
        }
        
        
        /**
         * Trecho do código que realiza o fork para a execução do comando
         * externo
         */
        if ((pid = fork()) < 0){
            /**
             * Caso o resultado do fork seja negativo, significa que ele não
             * executou corretamente, então indicaremos uma condição de erro.
             */
            fprintf(stderr, "fork error\n");
        }
        else if (pid == 0) {
            
            /**
             * Caso o resultado do fork seja zero, significa que estamos no
             * processo filho, então chamamos execpl para substituir a imagem
             * do processo atual pela imagem do comando que vamos executar.
             */
            execv(command, list);
            
            /**
             * Se a execpl retornar significa que houve um erro e mostramos
             * uma mensagem. e encerramos o minishel devolvendo ao SO um
             * código de erro (127 ou -1).
             * 
             * Quando as funções da família exec executam corretamente elas
             * nunca retornam.
             */
            fprintf(stderr, "couldn't execute: %s\n", buf);
            exit(127);
        }
        
        /**
         * Caso o fork execute corretamente, no processo pai seguimos com a
         * execução do minishel, aguradando a processo filho encerrar.
         */
       
        if ((pid = waitpid(pid, &status, 0)) < 0){
            fprintf(stderr, "waitpid error\n");
        }
    }
    
    /**
     * Limpando a casa
     */
    printf("\n");
    
    exit(0);
}

