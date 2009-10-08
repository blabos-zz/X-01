/*
 * lista_dupla.c
 *
 *  Created on: Oct 8, 2009
 *      Author: wesley
 */
#include <stdlib.h>
#include <stdio.h>

struct st_no {
	int num;
	struct st_no* prox;
	struct st_no* ant;
};

typedef struct st_no no;

typedef struct {
	no* cabeca;
	no* rabo;
} lista;


void mostra_lista(const lista* l) {
	no* i;
	
	if (l->cabeca == NULL) {
		printf("Lista vazia\n");
	}
	else {
		for(i = l->cabeca; i && (i != l->rabo->prox); i = i->prox) {
			printf("%10p <- %10p -> %10p : %d\n", i->ant, i, i->prox, i->num);
		}
	}
}

void mostra_elementos(no* cabeca, no* rabo) {
	no* i;
	
	if (cabeca == NULL) {
		printf("Sem elementos\n");
	}
	else {
		for(i = cabeca; i && (i != rabo->prox); i = i->prox) {
			printf("%10p <- %10p -> %10p : %d\n", i->ant, i, i->prox, i->num);
		}
	}
}

void inicia_lista(lista* l) {
	l->cabeca = l->rabo = NULL;
}

void inicia_elementos(no** cabeca, no** rabo) {
	(*cabeca) = (*rabo) = NULL;
}

void insere_cabeca_lista(lista* l, int val) {
	no* temp = (no*)malloc(sizeof(no));
	
	temp->num = val;
	temp->ant = temp->prox = NULL;
	
	if (l->cabeca == NULL) {
		// Primeiro elemento.
		l->cabeca = l->rabo = temp;
	}
	else {
		temp->prox = l->cabeca;
		l->cabeca->ant = temp;
		l->cabeca = temp;
	}
}

void insere_cabeca_elementos(no** cabeca, no** rabo, int val) {
	no* temp = (no*)malloc(sizeof(no));
	
	temp->num = val;
	temp->ant = temp->prox = NULL;
	
	if ((*cabeca) == NULL) {
		// Primeiro elemento.
		(*cabeca) = (*rabo) = temp;
	}
	else {
		temp->prox = (*cabeca);
		(*cabeca)->ant = temp;
		(*cabeca) = temp;
	}
}

void insere_rabo_lista(lista* l, int val) {
	no* temp = (no*)malloc(sizeof(no));
	
	temp->num = val;
	temp->ant = temp->prox = NULL;
	
	if (l->cabeca == NULL) {
		// Primeiro elemento.
		l->cabeca = l->rabo = temp;
	}
	else {
		l->rabo->prox = temp;
		temp->ant = l->rabo;
		l->rabo = temp;
	}
}

void insere_rabo_elementos(no** cabeca, no** rabo, int val) {
	no* temp = (no*)malloc(sizeof(no));
	
	temp->num = val;
	temp->ant = temp->prox = NULL;
	
	if ((*cabeca) == NULL) {
		// Primeiro elemento.
		(*cabeca) = (*rabo) = temp;
	}
	else {
		(*rabo)->prox = temp;
		temp->ant = (*rabo);
		(*rabo) = temp;
	}
}

void remove_cabeca_lista(lista* l) {
	if (l->cabeca != NULL) {
		no* temp = l->cabeca;
		
		if (l->cabeca == l->rabo) {
			// Último elemento
			l->cabeca = l->rabo = NULL;
		}
		else {
			l->cabeca = l->cabeca->prox;
			l->cabeca->ant = NULL;
		}
		
		free(temp);
	}
	else {
		printf("Não posso remover da cabeça. Lista vazia\n");
	}
}

void remove_cabeca_elementos(no** cabeca, no** rabo) {
	if ((*cabeca) != NULL) {
		no* temp = (*cabeca);
		
		if ((*cabeca) == (*rabo)) {
			// Último elemento
			(*cabeca) = (*rabo) = NULL;
		}
		else {
			(*cabeca) = (*cabeca)->prox;
			(*cabeca)->ant = NULL;
		}
		
		free(temp);
	}
	else {
		printf("Não posso remover da cabeça. Sem elementos\n");
	}
}

void remove_rabo_lista(lista* l) {
	if (l->cabeca != NULL) {
		no* temp = l->rabo;
		
		if (l->cabeca == l->rabo) {
			// Último elemento
			l->cabeca = l->rabo = NULL;
		}
		else {
			l->rabo = l->rabo->ant;
			l->rabo->prox = NULL;
		}
		
		free(temp);
	}
	else {
		printf("Não posso tirar do seu rabo. Lista vazia\n");
	}
}

void remove_rabo_elementos(no** cabeca, no** rabo) {
	if ((*cabeca) != NULL) {
		no* temp = (*rabo);
		
		if ((*cabeca) == (*rabo)) {
			// Último elemento
			(*cabeca) = (*rabo) = NULL;
		}
		else {
			(*rabo) = (*rabo)->ant;
			(*rabo)->prox = NULL;
		}
		
		free(temp);
	}
	else {
		printf("Não posso tirar do seu rabo. Sem elementos\n");
	}
}

int main(void) {
	lista l;
	
	inicia_lista(&l);
	
	printf("\nInserindo Cabeça\n");
	insere_cabeca_lista(&l, 1);
	insere_cabeca_lista(&l, 2);
	insere_cabeca_lista(&l, 3);
	insere_cabeca_lista(&l, 4);
	mostra_lista(&l);
	
	printf("\nRemovendo Cabeça\n");
	remove_cabeca_lista(&l);
	remove_cabeca_lista(&l);
	mostra_lista(&l);
	
	printf("\nInserindo Rabo\n");
	insere_rabo_lista(&l, 5);
	insere_rabo_lista(&l, 6);
	mostra_lista(&l);
	
	printf("\nRemovendo Rabo\n");
	remove_rabo_lista(&l);
	remove_rabo_lista(&l);
	remove_rabo_lista(&l);
	remove_rabo_lista(&l);
	mostra_lista(&l);
	
	printf("\nRemovendo depois de vazia\n");
	remove_cabeca_lista(&l);
	remove_cabeca_lista(&l);
	remove_rabo_lista(&l);
	remove_rabo_lista(&l);
	mostra_lista(&l);
	
	no* cabeca;
	no* rabo;
	
	inicia_elementos(&cabeca, &rabo);
	
	printf("\nInserindo Cabeça\n");
	insere_cabeca_elementos(&cabeca, &rabo, 1);
	insere_cabeca_elementos(&cabeca, &rabo, 2);
	insere_cabeca_elementos(&cabeca, &rabo, 3);
	insere_cabeca_elementos(&cabeca, &rabo, 4);
	mostra_elementos(cabeca, rabo);
	
	printf("\nRemovendo Cabeça\n");
	remove_cabeca_elementos(&cabeca, &rabo);
	remove_cabeca_elementos(&cabeca, &rabo);
	mostra_elementos(cabeca, rabo);
	
	printf("\nInserindo Rabo\n");
	insere_rabo_elementos(&cabeca, &rabo, 5);
	insere_rabo_elementos(&cabeca, &rabo, 6);
	mostra_elementos(cabeca, rabo);
	
	printf("\nRemovendo Rabo\n");
	remove_rabo_elementos(&cabeca, &rabo);
	remove_rabo_elementos(&cabeca, &rabo);
	remove_rabo_elementos(&cabeca, &rabo);
	remove_rabo_elementos(&cabeca, &rabo);
	mostra_elementos(cabeca, rabo);
	
	printf("\nRemovendo depois de vazia\n");
	remove_cabeca_elementos(&cabeca, &rabo);
	remove_cabeca_elementos(&cabeca, &rabo);
	remove_rabo_elementos(&cabeca, &rabo);
	remove_rabo_elementos(&cabeca, &rabo);
	mostra_elementos(cabeca, rabo);
	
	return EXIT_SUCCESS;
}
