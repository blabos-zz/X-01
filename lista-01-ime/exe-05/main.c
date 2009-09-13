/*
 * main.c
 *
 *  Created on: Sep 13, 2009
 *      Author: blabos
 *  
 *  5. Dados x inteiro e n natural, calcular x ** n.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int power(int x, int n) {
	if (n > 0) return x * power(x, n-1);
	else return 1;
}

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int x, n;
	
	printf("Digite x: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	x = buffer != NULL ? atoi(buffer) : 0;
	
	printf("Digite n: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	n = buffer != NULL ? atoi(buffer) : 0;
	n = (n >= 0) ? n : 0;
	
	printf("%d ** %d = %d\n", x, n, power(x, n));
	
	return EXIT_SUCCESS;
}
