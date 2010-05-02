#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 1024

int main(void)
{
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
     * Imprime o 'prompt' do minishel 
     */
    printf("%% ");
    
    /**
     * Enquanto não for digitado Ctrl-D (EOF), repete a leitura de um comando
     * para ser executado pelo minishel
     */
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        
        /**
         * Remove o caractere \n capturado ao final do comando
         */
        buf[strlen(buf) - 1] = 0;
        
        
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
            execlp(buf, buf, (char *) 0);
            
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
        
        /**
         * Repetindo o prompt
         */
        printf("%% ");
    }
    
    /**
     * Limpando a casa
     */
    printf("\n");
    
    exit(0);
}

