/*
 * main.c
 *
 *  Created on: Sep 16, 2009
 *      Author: blabos
 *  
 *  12. Dado p inteiro, verificar se p é primo.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int is_prime(int n) {
	int i = 2;
	int factors = 0;
	
	for (i = 1; i <= n/2 + 1; i++) {
		if (!(n%i)) factors++;
		if (factors > 1) return 0;
	}
	
	return 1;
}

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int p;
	
	printf("Enter n: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	p = buffer != NULL ? atoi(buffer) : 0;
	
	if (is_prime(p)) {
		printf("%d is prime\n", p);
	}
	else {
		printf("%d isn't prime\n", p);
	}
	
	return EXIT_SUCCESS;
}
