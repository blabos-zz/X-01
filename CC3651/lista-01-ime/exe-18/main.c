/*
 * main.c
 *
 *  Created on: Sep 17, 2009
 *      Author: blabos
 *  
 *  18. Dado um número natural na base decimal, transformá-lo para a base
 *  binária.
 *
 *  Exemplo: Dado 18 a saída deverá ser 10010.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE (16 + 1)

int power(int x, int n) {
	if (n > 0) return x * power(x, n-1);
	else return 1;
}

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	unsigned int bin, dec, i, d;
	
	printf("Enter the decimal number (max 256): ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	d = dec = buffer != NULL ? atoi(buffer) : 0;
	
	bin = i = 0;
	do {
		bin += d % 2 * power(10, i++);
		d /= 2;
	} while (d);
	
	printf("%dd -> %ddb\n", dec, bin);
	
	return EXIT_SUCCESS;
}
