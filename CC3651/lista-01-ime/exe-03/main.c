/*
 * main.c
 *
 *  Created on: Sep 15, 2009
 *      Author: blabos
 *  
 *  3. Dado um número inteiro positivo n, imprimir os n primeiros naturais
 *  ímpares. Exemplo: Para n=4 a saída deverá ser 1,3,5,7.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int number, i;
	
	printf("Enter the number of odd: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	number = buffer != NULL ? atoi(buffer) : 0;
	
	for (i = 0; i < number; i++) {
		printf("%d, ", 2*i + 1);
	}
	
	if (number > 0) printf("\b\b.\n");
	
	return EXIT_SUCCESS;
}
