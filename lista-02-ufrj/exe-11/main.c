/*
 * main.c
 *
 *  Created on: Sep 16, 2009
 *      Author: blabos
 *  
 *  11. Escreva um programa que leia duas cadeias de caracteres e concatene a
 *  segunda cadeia ao final da primeira.
 *
 *  Solução: concatena.c
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF_SIZE 80

int _strlen(const char* str) {
    int length = 0;
    while (str[length] != '\0') length++;
    return length;
}

void _strcat(char* dest, const char* src) {
    int dlen = _strlen(dest);
    int slen = _strlen(src);
    
    int i = dlen;
    int j = 0;
    
    while ((i < (MAX_BUFF_SIZE - 1)) && (j < slen)) {
        dest[i++] = src[j++];
    }
    dest[i] = '\0';
}

int main(void) {
	char first[MAX_BUFF_SIZE];
    char last[MAX_BUFF_SIZE];
	
	printf("Enter the first string: ");
	fgets(first, MAX_BUFF_SIZE, stdin);
    first[_strlen(first) - 1] = '\0';
    
    printf("Enter the last string: ");
    fgets(last, MAX_BUFF_SIZE, stdin);
    last[_strlen(last) - 1] = '\0';
    
	_strcat(first, last);
    
    printf("'%s'\n", first);
    
	return EXIT_SUCCESS;
}
