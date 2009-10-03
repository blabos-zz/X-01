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
void _menu_find(order_list_t* orders);
void _menu_show_all(order_list_t* orders);
void _menu_show_stock();
void _menu_reload_stock();
void _menu_save(const order_list_t* orders);
void _menu_load(order_list_t* orders);
void _menu_exit();


void print_menu() {
	printf("\n\nCC3651 - Exercicio de Laboratorio #2\n\n");
	printf("1 - Resumo\n");
	printf("2 - Fazer Pedido\n");
	printf("3 - Atender Pedidos\n");
	printf("4 - Procurar Pedido\n");
	printf("5 - Listar Pedidos\n");
	printf("6 - Mostrar Estoque\n");
	printf("7 - Reabastecer Estoque\n");
	printf("8 - Salvar Dados\n");
	printf("9 - Carregar Dados\n");
	printf("0 - Sair\n");
	
	printf("\nSua opcao: ");
}

int read_option() {
	char option[16];
	
	setbuf(stdin, 0);
	fgets(option, 16, stdin);
	
	return atoi(option);
}

void dispatch(order_list_t* orders, int option) {
	switch (option) {
	    case 1: {
			_menu_status(orders);
			break;
		}
		
		case 2: {
			_menu_send_order(orders);
			break;
		}
		
		case 3: {
			_menu_attend_orders(orders);
			break;
		}
		
		case 4: {
			_menu_find(orders);
			break;
		}
		
		case 5: {
			_menu_show_all(orders);
			break;
		}
		
		case 6: {
			_menu_show_stock();
			break;
		}
		
		case 7: {
			_menu_reload_stock();
			break;
		}
		
		case 8: {
			_menu_save(orders);
			break;
		}
		
		case 9: {
			_menu_load(orders);
			break;
		}
		
		case 0: {
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
    order_t order;
    int code;
	
    printf("Gerando pedido. Digite as quantidades de cada ingrediente:\n");
    
    printf("Arroz:  ");
    order.data.rice = abs(read_option());
    
    printf("Feijão: ");
    order.data.bean = abs(read_option());
    
    printf("Milho:  ");
    order.data.corn = abs(read_option());
    
    printf("Leite:  ");
    order.data.milk = abs(read_option());
    
    printf("Vinho:  ");
    order.data.wine = abs(read_option());
    
    if (code = request_order(orders, order)) {
        printf("Pedido %03d inserido com sucesso.\n", code);
    }
    else {
        printf("Falha ao inserir pedido.\n");
    }
}

void _menu_show_all(order_list_t* orders) {
    printf("Mostrando pedidos:\n");
    
    order_t* it;
    for (it = orders->tail; it != orders->head->prev; it = it->prev) {
        printf("\nPedido %03d:\n", it->code);
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

void _menu_find(order_list_t* orders) {
    order_t* order = NULL;
    unsigned code = 0;
    
    printf("Procurando Pedido:\n");
    
    printf("Digite o código para procurar: \n");
    code = read_option();
    if (order = find(orders, code)) {
        printf("Pedido encontrado:\n");
        printf("\nPedido %03d:\n", order->code);
        printf("Arroz:  %3d\n", order->data.rice);
        printf("Feijão: %3d\n", order->data.bean);
        printf("Milho:  %3d\n", order->data.corn);
        printf("Leite:  %3d\n", order->data.milk);
        printf("Vinho:  %3d\n", order->data.wine);
    }
    else {
        printf("Pedido não encontrado.\n");
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

void _menu_save(const order_list_t* orders) {
    printf("Salvando dados\n");    
}

void _menu_load(order_list_t* orders) {
    printf("carregando dados\n");
}

void _menu_default(int option) {
	printf("\n\nOpcao %d invalida. Tente alguma disponivel no Menu!\n\n",
			option);
}

