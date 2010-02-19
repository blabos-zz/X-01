/*
 * main.c
 *
 *  Created on: Sep 17, 2009
 *      Author: blabos
 *  
 *  23. (POLI 89) Dados um inteiro positivo n e uma seqüência de n números
 *  inteiros, determinar o comprimento de um segmento crescente de comprimento
 *  máximo.
 *
 *  Exemplos:
 *      Na seqüência
 *      5, 10, 3, 2, 4, 7, 9, 8, 5
 *      -----  -  ----------  -  -
 *      o comprimento do segmento crescente máximo é 4.
 *
 *      Na seqüência
 *      10, 8, 7, 5, 2
 *      --  -  -  -  -
 *      o comprimento de um segmento crescente máximo é 1.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int n, count;
	int max_seq;
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
    
    max_seq = count = 1;
	while (--n) {
	    printf("Enter the next number: ");
	    fgets(buffer, MAX_BUFF_SIZE, stdin);
	    curr_number = buffer != NULL ? atoi(buffer) : 0;
	    
	    if (curr_number > prev_number) {
	        count++;
	    }
	    else if (count > max_seq){
	        max_seq = count;
	        count = 1;
	    }
	    
	    prev_number = curr_number;
	}
	
	printf("The highest segment has a size of %d number(s)\n", max_seq);
	
	return EXIT_SUCCESS;
}
