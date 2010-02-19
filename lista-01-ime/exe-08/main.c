/*
 * main.c
 *
 *  Created on: Sep 15, 2009
 *      Author: blabos
 *  
 *  8. Dados n e uma seqüência de n números inteiros, determinar a soma dos
 *  números pares.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int n;
	int sum = 0;
	
	printf("Enter the number n: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	n = buffer != NULL ? atoi(buffer) : 0;
	
	sum = n / 2;
	sum *= (sum + 1);
	
	printf("Sum of even from 0 to %d: %d\n", n, sum);
	
	return EXIT_SUCCESS;
}
