/*
 * main.c
 *
 *  Created on: Sep 16, 2009
 *      Author: blabos
 *  
 *  Escreva um programa que leia uma frase de até 80 caracteres do teclado e
 *  imprima a frequência com que aparece cada uma das letras do alfabeto na
 *  frase.
 *  Solução: c8contac.c 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUFF_SIZE	(80 + 1)
#define MAX_CHARS		26

int main(void) {
	char buffer[MAX_BUFF_SIZE];
	int rates[MAX_CHARS + 1];
	int i, idx;
	
	memset(rates, 0, sizeof(rates));
	
	printf("Enter the phrase (max 80 chars): ");
	if (fgets(buffer, MAX_BUFF_SIZE, stdin) == NULL) return EXIT_FAILURE;
	
	for (i = 0; i < strlen(buffer); i++) {
		idx = toupper(buffer[i]) - 'A';
		idx = ((idx >= 0) && (idx < MAX_CHARS)) ? idx : MAX_CHARS;
		
		rates[idx]++;
	}
	
	for (i = 0; i < MAX_CHARS; i++) {
		printf("%c: %d\n", 'A' + i, rates[i]);
	}
	
	return EXIT_SUCCESS;
}
