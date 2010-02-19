/*
 * main.c
 *
 *  Created on: Sep 15, 2009
 *      Author: blabos
 *  
 *  7. Dados o número n de alunos de uma turma de Introdução aos Autômatos
 *  a Pilha (MAC 414) e suas notas da primeira prova, determinar a maior e a
 *  menor nota obtidas por essa turma (Nota máxima = 100 e nota mínima = 0).
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 4

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int n;
	int score;
	int max_score =  -1;
	int min_score = 101;
	
	printf("Enter the number of scores: ");
	fgets(buffer, MAX_BUFF_SIZE, stdin);
	n = buffer != NULL ? atoi(buffer) : 0;
	
	do {
		printf("Enter the next score: ");
		fgets(buffer, MAX_BUFF_SIZE, stdin);
		score = buffer != NULL ? atoi(buffer) : 0;
		
		if (score > max_score) max_score = score;
		if (score < min_score) min_score = score;
	} while (--n);
	
	printf("The highest score: %d\n", max_score);
	printf("The lowest score:  %d\n", min_score);
	
	return EXIT_SUCCESS;
}
