/*
 * main.c
 *
 *  Created on: Sep 13, 2009
 *      Author: blabos
 *  
 *  1. Dada uma coleção de números inteiros positivos terminada por 0,
 *  imprimir seus quadrados.
 *  
 *  Notas:
 *  
 *  1) Apenas uma forma alternativa de resolver.
 *  2) Eu não sei quantos números serão inseridos.
 *  3) Estou assumindo que devo mostrar os quadrados apenas no final.
 *  
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 64

int main(void) {
	char* filename = "crazy.txt";
	FILE* fp;
	
	
	/**
	 * Reading input form user.
	 */
	if ((fp = fopen(filename, "w")) != NULL) {
		char buffer[MAX_BUFF_SIZE];
		int number = 0;
		
		printf("Enter a sequence of numbers ended by 0 (zero):\n");
		
		do {
			fgets(buffer, MAX_BUFF_SIZE, stdin);
			number = buffer != NULL ? atoi(buffer) : 0;
			fprintf(fp, "%d\n", number);
		} while (number != 0);
		
		fclose(fp);
	}
	else {
		printf("Cannot create file '%s'.\n", filename);
		return EXIT_FAILURE;
	}
	
	/**
	 * Retrieving data, calculating and showing.
	 */
	if ((fp = fopen(filename, "r")) != NULL) {
		char buffer[MAX_BUFF_SIZE];
		int number = 0;
		
		printf("\nSquares:\n");
		
		while (!feof(fp)) {
			fgets(buffer, MAX_BUFF_SIZE, fp);
			number = buffer != NULL ? atoi(buffer) : 0;
			
			if (number == 0) break;
			
			printf("%d -> %d\n", number, number*number);
		}
		
		fclose(fp);
	}
	else {
		printf("Cannot open file '%s'.\n", filename);
		return EXIT_FAILURE;
	}
	
	/**
	 * Cleaning up
	 */
	remove(filename);
	
	return EXIT_SUCCESS;
}
