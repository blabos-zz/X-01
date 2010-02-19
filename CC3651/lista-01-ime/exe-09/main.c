/*
 * main.c
 *
 *  Created on: Sep 16, 2009
 *      Author: blabos
 *  
 *  9. Dado um inteiro n não-negativo, determinar n!
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int fat(int n) {
	if (n < 2) return 1;
	else return n * fat(n-1);
}

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int n, f;
	
	printf("Enter the number to calculate n!: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	n = buffer != NULL ? atoi(buffer) : 0;
	
	f = fat(n);
	
	printf("%d! = %d\n", n, f);
	
	return EXIT_SUCCESS;
}
