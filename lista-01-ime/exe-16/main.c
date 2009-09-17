/*
 * main.c
 *
 *  Created on: Sep 17, 2009
 *      Author: blabos
 *  
 *  16. Dizemos que um número i é congruente módulo m a j se i % m = j % m.
 *  Exemplo: 35 é congruente módulo 4 a 39, pois 35 % 4 = 3 = 39 % 4.
 *  Dados n , j e m naturais não nulos, imprimir os n primeiros naturais
 *  congruentes a j módulo m.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int is_congruent(int i, int j, int m) {
    return (i % m) == (j % m);
}

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int n, j, m;
	int i;
	
	printf("Enter n: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	n = buffer != NULL ? abs(atoi(buffer)) : 0;
	
	printf("Enter j: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	j = buffer != NULL ? abs(atoi(buffer)) : 0;
	
	printf("Enter m: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	m = buffer != NULL ? abs(atoi(buffer)) : 0;
	
	i = 0;
	while (n) {
		if (is_congruent(i, j, m)) {
			printf("(%d %% %d) == (%d %% %d)\n", i, m, j, m);
			n--;
		}
		i++;
	}
	
	return EXIT_SUCCESS;
}
