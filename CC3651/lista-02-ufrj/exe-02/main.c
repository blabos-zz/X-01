/*
 * main.c
 *
 *  Created on: Sep 16, 2009
 *      Author: blabos
 *  
 *  Escreva um programa que gere um vetor de três dimensões (X, Y e Z) em que
 *  cada posição guarda a soma de suas coordenadas. As dimensões da matriz
 *  deverão ser determinadas em tempo de execução e o programa deverá informar
 *  os valores gerados.
 *  Solução: vetor.c
 *  
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 16

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int i, j, k;
	int x, y, z;
	int* mat;
	
	printf("Enter the X dimension: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	x = buffer != NULL ? abs(atoi(buffer)) : 0;
	
	printf("Enter the Y dimension: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	y = buffer != NULL ? abs(atoi(buffer)) : 0;
	
	printf("Enter the Z dimension: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	z = buffer != NULL ? abs(atoi(buffer)) : 0;
	
	mat = (int*)malloc(x * y * z * sizeof(int));
	if (mat == NULL) return EXIT_FAILURE;
	
	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			for (k = 0; k < z; k++) {
				mat[i*y*z + j*z + k] = i + j + k;
			}
		}
	}
	
	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			for (k = 0; k < z; k++) {
				printf("%d\t", mat[i*y*z + j*z + k]);
			}
			printf("\n");
		}
		printf("\n");
	}
	printf("\n");
	
	free(mat);
	
	return EXIT_SUCCESS;
}
