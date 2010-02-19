/*
 * main.c
 *
 *  Created on: Sep 17, 2009
 *      Author: blabos
 *  14. (MAT 89) Dado n inteiro positivo, dizemos que n é perfeito se for
 *  igual à soma de seus divisores positivos diferentes de n.
 *  
 *  Exemplo: 6 é perfeito, pois 1+2+3 = 6.
 *  Verificar se um dado número inteiro positivo é perfeito.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int n, sum, i;
	
	printf("Enter the number: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	n = buffer != NULL ? abs(atoi(buffer)) : 0;
	
	for(sum = 0, i = 1; i <= 1 + n/2; i++) {
		if (!(n % i)) sum += i;
	}
	
	if (sum == n) {
		printf("%d is a perfect number.\n", n);
	}
	else {
		printf("%d isn't a perfect number.\n", n);
	}
	
	return EXIT_SUCCESS;
}
