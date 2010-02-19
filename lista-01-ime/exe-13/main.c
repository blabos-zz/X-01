/*
 * main.c
 *
 *  Created on: Sep 17, 2009
 *      Author: blabos
 *  
 *  13. Dados dois números inteiros positivos, determinar o máximo divisor
 *  comum entre eles usando o algoritmo de Euclides.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int mdc(int a, int b) {
	if (b == 0) return a;
	else return mdc(b, a%b);
}

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int a, b;
	
	printf("Enter the first number: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	a = buffer != NULL ? abs(atoi(buffer)) : 0;
	
	printf("Enter the second number: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	b = buffer != NULL ? abs(atoi(buffer)) : 0;
	
	printf("MDC(%d, %d) = %d\n", a, b, mdc(a, b));
	
	return EXIT_SUCCESS;
}
