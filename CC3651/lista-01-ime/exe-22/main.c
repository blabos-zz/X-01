/*
 * main.c
 *
 *  Created on: Sep 17, 2009
 *      Author: blabos
 *  
 *  22. (POLI 87) Dados n e uma seqüência de n números inteiros, determinar
 *  quantos segmentos de números iguais consecutivos compõem essa seqüência.
 *
 *  Exemplo: A seguinte seqüência é formada por 5 segmentos de números iguais:
 *  5, 2, 2, 3, 4, 4, 4, 4, 1, 1
 *  -  ----  -  ----------  ----
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int n, count;
	int prev_number, curr_number;
	
	printf("Enter n: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	n = buffer != NULL ? abs(atoi(buffer)) : 0;
	
	if (n < 1) {
	    printf("n must be > 0\n");
	    return EXIT_FAILURE;
	}
	
	printf("Enter the next number: ");
    fgets(buffer, MAX_BUFF_SIZE, stdin);
    prev_number = buffer != NULL ? atoi(buffer) : 0;
    
    count = 1;
	while (--n) {
	    printf("Enter the next number: ");
	    fgets(buffer, MAX_BUFF_SIZE, stdin);
	    curr_number = buffer != NULL ? atoi(buffer) : 0;
	    
	    if (curr_number != prev_number) {
	        prev_number = curr_number;
	        count++;
	    }
	}
	
	printf("We found %d segment(s)\n", count);
	
	return EXIT_SUCCESS;
}
