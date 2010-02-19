/*
 * menu.c
 *
 *  Created on: Sep 7, 2009
 *      Author: wesley
 */

#include "menu.h"
#include "contacts.h"

#include <stdio.h>
#include <stdlib.h>


void _menu_exit();
void _menu_insert(contacts_t* list);
void _menu_find_by_name(contacts_t* list);
void _menu_find_by_place(contacts_t* list);
void _menu_delete(contacts_t* list);
void _menu_list(contacts_t* list);
void _menu_default(int option);


void print_menu(const contacts_t* list) {
	printf("\n\nCC3651 - Exercicio de Laboratorio #1\n\n");
	
	if (list->_length != MAX_LIST_SIZE) {
		printf("1 - Inserir\n");
	}
	
	printf("2 - Pesquisar por Nome\n");
	printf("3 - Persquisar por Lugar\n");
	
	if (list->_length != 0) {
		printf("4 - Excluir\n");
	}
	
	printf("5 - Listar Todos\n");
	printf("6 - Sair\n");
	
	printf("\nEstado da lista: %d/%d elemento(s) ocupado(s)\n",
			count(list), MAX_LIST_SIZE);
	
	printf("\nSua opcao: ");
}

int read_option() {
	string_t option;
	char* ret;			// Only to suppress warnings.
	
	setbuf(stdin, 0);
	ret = fgets(option, MAX_STR_SIZE, stdin);
	
	return atoi(option);
}

void dispatch(contacts_t* list, int option) {
	switch (option) {
		case 1: {
			_menu_insert(list);
			break;
		}
		
		case 2: {
			_menu_find_by_name(list);
			break;
		}
		
		case 3: {
			_menu_find_by_place(list);
			break;
		}
		
		case 4: {
			_menu_delete(list);
			break;
		}
		
		case 5: {
			_menu_list(list);
			break;
		}
		
		
		case 6: {
			_menu_exit();
			break;
		}
		
		default: {
			_menu_default(option);
		}
	}
}


void _menu_exit() {
	printf("\nEncerrando aplicacao\n\n");
}


void _menu_insert(contacts_t* list) {
	contact_t contact;
	int pos;
	
	printf("\n\nInserir\n\n");
	
	if (list->_length < MAX_LIST_SIZE) {
		read_one(&contact);
		pos = insert(list, contact);
		
		if (pos >= 0) {
			printf("\n\nContato '%s' adicionado com sucesso!\n\n",
					list->_contacts[pos]._name);
			return;
		}
	}
	
	printf("Lista cheia.\n\n");
}

void _menu_find_by_name(contacts_t* list) {
	string_t name;
	char* ret;			// Only to suppress warnings.
	int pos;
	
	setbuf(stdin, 0);
	printf("\n\nBusca por Nome\n\n");
	
	printf("Nome do contato: ");
	ret = fgets(name, MAX_STR_SIZE, stdin);
	chomp(name);
	
	pos = find_by_name(list, name, 0, list->_length - 1);
	
	if (pos >= 0) {
		printf("\nEncontrei:\n");
		print_one(list, pos);
	}
	else {
		printf("\nO contato '%s' nao foi encontrado.\n\n", name);
	}
}

void _menu_find_by_place(contacts_t* list) {
	string_t place;
	char* ret;			// Only to suppress warnings.
	int pos;
	
	setbuf(stdin, 0);
	printf("\n\nBusca por Lugar\n\n");
	
	printf("Lugar onde conheceu o contato: ");
	ret = fgets(place, MAX_STR_SIZE, stdin);
	chomp(place);
	
	pos = find_by_place(list, place, 0, list->_length - 1);
	
	if (pos >= 0) {
		printf("\nEncontrei:\n");
		print_one(list, pos);
	}
	else {
		printf("\nO lugar '%s' nao foi encontrado.\n\n", place);
	}
}

void _menu_delete(contacts_t* list) {
	string_t name;
	char* ret;			// Only to suppress warnings;
	int pos;
	
	setbuf(stdin, 0);
	printf("\n\nExcluir\n\n");
	
	printf("Digite o nome do contato a excluir: ");
	ret = fgets(name, MAX_STR_SIZE, stdin);
	chomp(name);
	
	pos = delete(list, name);
	
	if (pos >= 0) {
		printf("\nContato '%s' excluido com sucesso.\n", name);
	}
	else {
		printf("\nFalha ao tentar excluir '%s'\n", name);
	}
}

void _menu_default(int option) {
	printf("\n\nOpcao %d invalida. Tente alguma disponivel no Menu!\n\n",
			option);
}

void _menu_list(contacts_t* list) {
	printf("\n\nListar Todos (%d)\n\n", list->_length);
	print_all(list);
	printf("\n");
}
