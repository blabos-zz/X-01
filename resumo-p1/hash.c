/*
 * hash.c
 *
 *  Created on: Oct 8, 2009
 *      Author: wesley
 */
#include <stdlib.h>
#include <stdio.h>

#define MAX		10
#define VAZIO	-1

void inicializa(int tabela[]) {
	int i;
	for (i = 0; i < MAX; i++) {
		tabela[i] = VAZIO;
	}
}

void imprime(int tabela[]) {
	int i;
	
	printf("\nTabela:\n");
	for (i = 0; i < MAX; i++) {
		printf("tabela[%2d] = %10d\n", i, tabela[i]);
	}
	printf("\n");
}

int rehash(int num) {
	return ++num >= MAX ? 0 : num;
}

void insere(int tabela[], int* tam, int val) {
	if ((*tam) < MAX) {
		int chave, posicao;
		
		chave = val / 1000;
		
		posicao = chave * 2;
		posicao = posicao >= MAX ? 0 : posicao;
		
		if (tabela[posicao] == VAZIO) {
			tabela[posicao] = val;
			(*tam)++;
		}
		else {
			//rehash linear
			while (tabela[posicao] != VAZIO) {
				posicao = rehash(posicao);
			}
			
			tabela[posicao] = val;
			(*tam)++;
		}
	}
	else {
		printf("Não posso inserir %d. Tabela cheia\n", val);
	}
}

int procura(int tabela[], int elemento) {
	int chave, posicao;
	
	chave = elemento / 1000;
	
	posicao = chave * 2;
	posicao = posicao >= MAX ? 0 : posicao;
	
	if (tabela[posicao] == elemento) {
		return posicao;
	}
	else {
		//rehash linear
		int count = MAX;
		while (count--) {
			posicao = rehash(posicao);
			
			if (tabela[posicao] == elemento) {
				return posicao;
			}
		}
	}
	
	return -1;
}

int main(void) {
	int tam = 0;
	int tabela[MAX];
	
	int elemento, pos;
	
	inicializa(tabela);
	imprime(tabela);
	
	insere(tabela, &tam, 1000);
	imprime(tabela);
	
	insere(tabela, &tam, 2000);
	imprime(tabela);
	
	insere(tabela, &tam, 3000);
	imprime(tabela);
	
	insere(tabela, &tam, 4000);
	imprime(tabela);
	
	insere(tabela, &tam, 5000);
	imprime(tabela);
	
	insere(tabela, &tam, 6000);
	imprime(tabela);
	
	insere(tabela, &tam, 7000);
	imprime(tabela);
	
	insere(tabela, &tam, 1100);
	imprime(tabela);
	
	insere(tabela, &tam, 10);
	imprime(tabela);
	
	insere(tabela, &tam, 11110);
	imprime(tabela);
	
	insere(tabela, &tam, 2222);
	imprime(tabela);
	
	elemento = 7000;
	if ((pos = procura(tabela, elemento)) != -1) {
		printf("\nElemento %d na posição %d\n", elemento, pos);
	}
	else {
		printf("\nElemento %d não encontrado\n", elemento);
	}
	
	elemento = 1234;
	if ((pos = procura(tabela, elemento)) != -1) {
		printf("\nElemento %d na posição %d\n", elemento, pos);
	}
	else {
		printf("\nElemento %d não encontrado\n", elemento);
	}
	
	return EXIT_SUCCESS;
}
