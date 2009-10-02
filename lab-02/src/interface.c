/*
 * interface.c
 *
 *  Created on: Oct 2, 2009
 *      Author: blabos
 */

#include "interface.h"

#include <stdio.h>
#include <stdlib.h>


void _menu_default(int option);
void _menu_status(order_list_t* orders);
void _menu_send_order(order_list_t* orders);
void _menu_attend_orders(order_list_t* orders);
void _menu_show_all(order_list_t* orders);
void _menu_show_stock();
void _menu_reload_stock();
void _menu_exit();


void print_menu() {
	printf("\n\nCC3651 - Exercicio de Laboratorio #2\n\n");
	printf("0 - Resumo\n");
	printf("1 - Enviar Pedido\n");
	printf("2 - Atender Pedidos\n");
	printf("3 - Verificar Pedido\n");
	printf("4 - Mostrar Pedidos\n");
	printf("5 - Mostrar Estoque\n");
	printf("6 - Reabastecer Estoque\n");
	printf("7 - Salvar Lista\n");
	printf("8 - Carregar Lista\n");
	printf("9 - Sair\n");
	
	printf("\nSua opcao: ");
}

int read_option() {
	char option[4] = {0,0,0,0};
	
	setbuf(stdin, 0);
	fgets(option, 4, stdin);
	
	return atoi(option);
}

void dispatch(order_list_t* orders, int option) {
	switch (option) {
	    case 0: {
			_menu_status(orders);
			break;
		}
		
		case 1: {
			_menu_send_order(orders);
			break;
		}
		
		case 2: {
			_menu_attend_orders(orders);
			break;
		}
		
		case 4: {
			_menu_show_all(orders);
			break;
		}
		
		case 5: {
			_menu_show_stock();
			break;
		}
		
		case 6: {
			_menu_reload_stock();
			break;
		}
		
		
		/*case 3: {
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
		
		*/
		
		case 9: {
			_menu_exit();
			break;
		}
		
		default: {
			_menu_default(option);
		}
	}
}

void _menu_status(order_list_t* orders) {
    printf("Resumo das operações:\n");
    
    printf("Pedidos pendentes: %03d\n", orders->size);
    
    printf("Estoque Atual:\n");
    stock_show();
}

void _menu_send_order(order_list_t* orders) {
    char buff[16];
    order_t order;
	
	setbuf(stdin, 0);
	
    printf("Gerando pedido #1. Digite as quantidades de cada ingrediente:\n");
    
    printf("Arroz:  ");
    fgets(buff, 16, stdin);
    order.data.rice = abs(atoi(buff));
    
    printf("Feijão: ");
    fgets(buff, 16, stdin);
    order.data.bean = abs(atoi(buff));
    
    printf("Milho:  ");
    fgets(buff, 16, stdin);
    order.data.corn = abs(atoi(buff));
    
    printf("Leite:  ");
    fgets(buff, 16, stdin);
    order.data.milk = abs(atoi(buff));
    
    printf("Vinho:  ");
    fgets(buff, 16, stdin);
    order.data.wine = abs(atoi(buff));
    
    if (request_order(orders, order)) {
        printf("Pedido inserido com sucesso.\n");
    }
    else {
        printf("Falha ao inserir pedido.\n");
    }
}

void _menu_show_all(order_list_t* orders) {
    printf("Mostrando pedidos:\n");
    
    order_t* it;
    for (it = orders->tail; it != orders->head->prev; it = it->prev) {
        printf("\nPedido #1:\n");
        printf("Arroz:  %3d\n", it->data.rice);
        printf("Feijão: %3d\n", it->data.bean);
        printf("Milho:  %3d\n", it->data.corn);
        printf("Leite:  %3d\n", it->data.milk);
        printf("Vinho:  %3d\n", it->data.wine);
    }
}

void _menu_attend_orders(order_list_t* orders) {
    order_t order;
    
    printf("Atendendo pedidos:\n");
    
    while (attend_order(orders, &order)) {
        printf("Arroz:  %03d\n", order.data.rice);
    }
}

void _menu_show_stock() {
    printf("Mostrando Estoque:\n");
    stock_show();
}

void _menu_reload_stock() {
    printf("Reabastecendo Estoque...\n");
    stock_reload();
    stock_show();
}

void _menu_exit() {
	printf("\nEncerrando aplicacao\n\n");
}

/*
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
}*/

void _menu_default(int option) {
	printf("\n\nOpcao %d invalida. Tente alguma disponivel no Menu!\n\n",
			option);
}

