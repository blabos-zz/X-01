/*
 * main.c
 *
 *  Created on: Sep 16, 2009
 *      Author: blabos
 *  
 *  10. Dado n e dois números naturais i e j diferentes de 0, imprimir em
 *  ordem crescente os n primeiros naturais que são múltiplos de i ou de j e 
 *  ou de ambos.
 *  
 *  Exemplo: Para n = 6 , i = 2 e j = 3 a saída deverá ser : 0,2,3,4,6,8.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int n, i, j, k, count;
	
	printf("Enter n: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	n = buffer != NULL ? atoi(buffer) : 0;
	
	printf("Enter i: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	i = buffer != NULL ? atoi(buffer) : 0;
	
	printf("Enter j: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	j = buffer != NULL ? atoi(buffer) : 0;
	
	count = k = 0;
	
	do {
		if (!((k % i) && (k % j))) {
			printf("%d, ", k);
			count++;
		}
		k++;
	} while (count < n);
	printf("\b\b.\n");
	
	return EXIT_SUCCESS;
}
