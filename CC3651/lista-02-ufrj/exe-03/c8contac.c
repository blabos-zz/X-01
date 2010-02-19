/* 
   Programa: c8contac.c
   Objetivo: Verifica a frequencia de cada uma das letras do alfabeto em uma
	frase de até 80 caracteres.
   Autor: Adriano Cruz
   Data: 28/03/2000
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM_TEXTO 80
#define TAM_ALFABETO 26

void ZeraFreq (int *);
void ParaMaius(char *);
void ContaFreq(char *, int *);
void ImprimeFreq (int *);

int main (void ) {

  char frase[TAM_TEXTO];
  int freq[TAM_ALFABETO];

  ZeraFreq (freq);

  fgets(frase, TAM_TEXTO, stdin);
  
  ParaMaius(frase);
  puts(frase);
  ContaFreq(frase, freq); 
  ImprimeFreq(freq);
  exit(0);
}

void ZeraFreq (int *freq) {
  int i;

  for (i=0; i<TAM_ALFABETO; i++) *(freq+i)=0;
}

void ParaMaius(char *frase) {
  int i;

  for (i=0; *(frase + i) != '\0'; i++) {
    *(frase+i) = toupper(*(frase+i));
  }
}

void ContaFreq (char *frase, int *freq) {
  int i;

  for (i=0; *(frase +i) != '\0'; i++) 
    *(freq + *(frase + i) - 'A') = *(freq + *(frase + i) - 'A') + 1;
} 

void ImprimeFreq (int *freq) {
  int i;
  char c='A';

  for (i=0; i<TAM_ALFABETO; i++) printf("%c = %d\n", c+i, *(freq+i));
}
