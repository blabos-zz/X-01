/*
 * main.c
 *
 *  Created on: Sep 15, 2009
 *      Author: blabos
 *  
 *  6. Uma loja de discos anota diariamente durante o mês de março a
 *  quantidade de discos vendidos. Determinar em que dia desse mês ocorreu a
 *  maior venda e qual foi a quantidade de discos vendida nesse dia.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int i;
	int q = -1;
	int maxq = -1;
	int maxd = -1;
	
	for (i = 1; i <= 31; i++) {
		printf("Enter the quantity of albums sold on %d: ", i);
		fgets(buffer, MAX_BUFF_SIZE, stdin);
		q = buffer != NULL ? atoi(buffer) : 0;
		
		if (q > maxq) {
			maxq = q;
			maxd = i;
		}
	}
	
	printf("Best sale on %02d/03: %d\n", maxd, maxq);
	
	return EXIT_SUCCESS;
}
