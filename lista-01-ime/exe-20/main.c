/*
 * main.c
 *
 *  Created on: Sep 17, 2009
 *      Author: blabos
 *  
 *  20. Dados três números, imprimi-los em ordem crescente.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

void sort(int* a, int* b, int*c) {
    int tmp;
    if (*a > *b) {
        tmp = *a;
        *a = *b;
        *b = tmp;
        sort(a, b, c);
    }
    
    if (*b > *c) {
        tmp = *b;
        *b = *c;
        *c = tmp;
        sort(a, b, c);
    }
}

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int a, b, c, tmp;
	int h, m, l;
	
	printf("Enter a: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	a = buffer != NULL ? atoi(buffer) : 0;
	
	printf("Enter b: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	b = buffer != NULL ? atoi(buffer) : 0;
	
	printf("Enter c: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	c = buffer != NULL ? atoi(buffer) : 0;
	
	sort(&a, &b, &c);
	
	printf("%d %d %d\n", a, b, c);
	
	return EXIT_SUCCESS;
}

