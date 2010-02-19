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

void _print_order(const order_t* order);

void _print_blank();
void _wait();


void print_menu() {
	_print_blank();
	
	printf("\n\nCC3651 - Exercicio de Laboratorio #2\n\n");
	printf(" 1 - Resumo\n");
	printf(" 2 - Fazer Pedido\n");
	printf(" 3 - Atender Pedidos\n");
	printf(" 4 - Procurar Pedido\n");
	printf(" 5 - Listar Pedidos\n");
	printf(" 6 - Mostrar Estoque\n");
	printf(" 7 - Reabastecer Estoque\n");
	printf(" 8 - Salvar Dados\n");
	printf(" 9 - Carregar Dados\n");
	printf("10 - Sair\n");
	
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
		
		case 10: {
			_menu_exit();
			break;
		}
		
		default: {
			_menu_default(option);
		}
	}
}

void _menu_status(order_list_t* orders) {
	_print_blank();
	
    printf("Resumo Operacional:\n\n");
    
    printf("Pedidos pendentes: %03d\n", orders->size);
    
    printf("Estoque Atual:\n\n");
    stock_show();
    
    _wait();
}

void _menu_send_order(order_list_t* orders) {
    order_t order;
    int code = get_next_code();
	
    _print_blank();
    printf("Digite as quantidades de cada ingrediente para o pedido %03d:\n",
    		code);
    
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
    
    order.code = code;
    
    if (code = request_order(orders, order)) {
        printf("Pedido %03d inserido com sucesso.\n", code);
    }
    else {
        printf("Falha ao inserir pedido.\n");
    }
    
    _wait();
}

void _menu_show_all(order_list_t* orders) {
	
	_print_blank();
    printf("Mostrando %03d pedidos:\n", orders->size);
    
    order_t* it;
    for (it = orders->tail; it && (it != orders->head->prev); it = it->prev) {
        _print_order(it);
    }
    
    _wait();
}

void _menu_attend_orders(order_list_t* orders) {
	order_t order;
	int count = 0;
	
	_print_blank();
    
    printf("Atendendo pedidos:\n");
    
    while (attend_order(orders, &order)) {
    	++count;
        _print_order(&order);
    }
    
    if (count) {
    	printf("\nForam atendidos %03d pedidos.\n", count);
    }
    else {
    	printf("\nNão foi possível atender nenhum pedido.\n");
    }
    
    _wait();
}

void _menu_find(order_list_t* orders) {
    order_t* order = NULL;
    unsigned code = 0;
    
    _print_blank();
    
    printf("Procurando Pedido:\n");
    
    printf("Digite o código para procurar: \n");
    code = read_option();
    if (order = find(orders, code)) {
        printf("Pedido encontrado:\n");
        _print_order(order);
    }
    else {
        printf("Pedido não encontrado.\n");
    }
    
    _wait();
}

void _menu_show_stock() {
	_print_blank();
	
    printf("Mostrando Estoque:\n");
    
    stock_show();
    
    _wait();
}

void _menu_reload_stock() {
	_print_blank();
	
    printf("Reabastecendo Estoque...\n");
    stock_reload();
    stock_show();
    
    _wait();
}

void _menu_exit() {
	_print_blank();
	
	printf("\nEncerrando aplicação\n\n");
}

void _menu_save(const order_list_t* orders) {
	
	_print_blank();
	
    printf("Salvando dados.\n");
    
    save(orders, "restaurant.bin");
    
    _wait();
}

void _menu_load(order_list_t* orders) {
	
	_print_blank();
	
    printf("Carregando dados.\n");
    
    load(orders, "restaurant.bin");
    
    _wait();
}

void _menu_default(int option) {
	
	_print_blank();
	
	printf("\n\nOpção %d inválida. Tente alguma disponível no Menu!\n\n",
			option);
	
	_wait();
}

void _print_order(const order_t* order) {
	printf("\nPedido %03d:\n", order->code);
	printf("Arroz:  %3d  ", order->data.rice);
	printf("Feijão: %3d  ", order->data.bean);
	printf("Milho:  %3d  ", order->data.corn);
	printf("Leite:  %3d  ", order->data.milk);
	printf("Vinho:  %3d\n", order->data.wine);
}

void _print_blank() {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void _wait() {
	char c[2];
	printf("Pressione ENTER para continuar");
	fgets(c, 2, stdin);
}
