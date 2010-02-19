/*
 * main.c
 *
 *  Created on: Sep 17, 2009
 *      Author: blabos
 *  
 *  15. Um matemático italiano da idade média conseguiu modelar o ritmo de
 *  crescimento da população de coelhos (2) através de uma seqüência de
 *  números naturais que passou a ser conhecida como seqüência de
 *  Fibonacci (3). O n-ésimo número da seqüência de Fibonacci Fn é dado pela
 *  seguinte fórmula de recorrência:
 *    F(n) = 1, se n = 1
 *    F(n) = 1, se n = 2
 *    F(n) = F(n-1) + F(n-2), se n > 2
 *  Faça um programa que dado n calcula Fn.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int fib(int n) {
    if (n > 2) return fib(n-1) + fib(n-2);
    else return 1;
}

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int n;
	
	printf("Enter n: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	n = buffer != NULL ? abs(atoi(buffer)) : 0;
	
	printf("Fib(%d) = %d\n", n, fib(n));
	
	return EXIT_SUCCESS;
}
