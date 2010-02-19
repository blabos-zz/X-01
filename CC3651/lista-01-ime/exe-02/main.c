/*
 * main.c
 *
 *  Created on: Sep 13, 2009
 *      Author: blabos
 *  
 *  2. Dado um número inteiro positivo n, calcular a soma dos n primeiros
 *  números naturais.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 64

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int number = 0;
	int sum = 0;
	
	printf("Enter a positive integer number: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	number = buffer != NULL ? atoi(buffer) : 0;
	sum = number * (number + 1) / 2;
	printf("The sum of %d integers is %d\n", number, sum);
	
	return EXIT_SUCCESS;
}
