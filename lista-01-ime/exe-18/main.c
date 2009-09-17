/*
 * main.c
 *
 *  Created on: Sep 17, 2009
 *      Author: blabos
 *  
 *  17. Dado um número natural na base binária, transformá-lo para a base
 *  decimal.
 *  
 *  Exemplo:
 *  Dado 10010 a saída será 18, pois
 *  1*2^4 + 0*2^3 + 0*2^2 + 1*2^1 + 0*2^0 = 18.
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
