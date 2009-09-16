/*
 * main.c
 *
 *  Created on: Sep 16, 2009
 *      Author: blabos
 *  
 *  11. Dizemos que um número natural é triangular se ele é produto de três
 *  números naturais consecutivos.
 *  
 *  Exemplo: 120 é triangular, pois 4.5.6 = 120. Dado n natural, verificar se
 *  n é triangular.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int is_triangular(int n) {
	int i = 2;
	int p = 0;
	
	while ((p = (i-1)*(i)*(i+1)) <= n) {
		if (p == n) return 1;
		i++;
	}
	return 0;
}

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int n;
	
	printf("Enter n: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	n = buffer != NULL ? atoi(buffer) : 0;
	
	if (is_triangular(n)) {
		printf("%d is triangular\n", n);
	}
	else {
		printf("%d isn't triangular\n", n);
	}
	
	return EXIT_SUCCESS;
}
