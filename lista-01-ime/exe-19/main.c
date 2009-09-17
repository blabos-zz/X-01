/*
 * main.c
 *
 *  Created on: Sep 17, 2009
 *      Author: blabos
 *  
 *  19. Dados três números naturais, verificar se eles formam os lados de um
 *  triângulo retângulo.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE (16 + 1)

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	unsigned int l1, l2, l3;
	
	printf("Enter l1: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	l1 = buffer != NULL ? atoi(buffer) : 0;
	
	printf("Enter l2: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	l2 = buffer != NULL ? atoi(buffer) : 0;
	
	printf("Enter l3: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	l3 = buffer != NULL ? atoi(buffer) : 0;
	
	if ((l1 > 0) && (l2 > 0) && (l3 > 0) &
	    (l1 <= l2 +l3) && (l2 <= l1 + l3) && (l3 <= l1 + l2)) {
	    printf("%d, %d and %d are triangle sides\n", l1, l2, l3);
	}
	else {
	    printf("%d, %d and %d aren't triangle sides\n", l1, l2, l3);
	}
	
	return EXIT_SUCCESS;
}
