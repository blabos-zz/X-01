/*
 * interface.c
 *
 *  Created on: Nov 7, 2009
 *      Author: blabos
 */

#include "interface.h"

#include <stdio.h>
#include <stdlib.h>


void _menu_default(int option);
void _menu_status();
void _menu_reload_wake();
void _menu_show_wake();
void _menu_reload_stock();
void _menu_show_stock();
void _menu_attend_order(int);
void _menu_exit();

void _print_blank();
void _wait();


void print_menu() {
	_print_blank();
	
	printf("\n\nCC3651 - Exercicio de Laboratorio #3\n\n");
	printf(" 1 - Resumo\n");
	printf(" 2 - Recarregar Esteira\n");
	printf(" 3 - Mostrar Esteira\n");
	printf(" 4 - Reabastecer Estoque\n");
	printf(" 5 - Mostrar Estoque\n");
	printf(" 6 - Atender Pedido de TV\n");
	printf(" 7 - Atender Pedido de Microondas\n");
	printf(" 8 - Atender Pedido de Panificadora\n");
	printf("10 - Sair\n");
	
	printf("\nSua opcao: ");
}

int read_option() {
	char option[16];
	
	setbuf(stdin, 0);
	fgets(option, 16, stdin);
	
	return atoi(option);
}

void dispatch(int option) {
	switch (option) {
	    case 1: {
			_menu_status();
			break;
		}
		
		case 2: {
			_menu_reload_wake();
			break;
		}
		
		case 3: {
			_menu_show_wake();
			break;
		}
		
		case 4: {
			_menu_reload_stock();
			break;
		}
		
		case 5: {
			_menu_show_stock();
			break;
		}
		
		case 6: {
			_menu_attend_order(TV);
			break;
		}
		
		case 7: {
			_menu_attend_order(MO);
			break;
		}
		
		case 8: {
			_menu_attend_order(PA);
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

void _menu_status() {
	_print_blank();
	
    printf("Resumo Operacional:\n\n");
    
    printf("Produtos na Esteira:    %d\n", wk_size());
    printf("Pilha de TVs:           %d\n", tv_size());
    printf("Pilha de Microondas:    %d\n", mo_size());
    printf("Pilha de Panificadoras: %d\n", pa_size());
    
    _wait();
}

void _menu_reload_wake() {
	_print_blank();
	reload_wake();
    _wait();
}

void _menu_show_wake() {
	node_t* it;
	int size = wk_size();
	
	_print_blank();
	
	printf("Estado da Esteria:\n\n");
	if (size) {
		printf("    Codigo        Produto     \n");
		for (it = wk_begin(); it != wk_end(); it = it->next) {
			printf("%10d %20s\n", it->prod.code, it->prod.name);
		}
	}
	else {
		printf("Esteira Vazia\n");
	}
	
	_wait();
}

void _menu_reload_stock() {
	_print_blank();
	reload_stock();
    _wait();
}

void _menu_show_stock() {
	node_t* it;
	int size;
	
	_print_blank();
	
	printf("Estado do Estoque:\n");
	
	size = tv_size();
	if (size) {
		printf("\nPilha de TVs:\n");
		printf("Itens: %d\n", size);
		printf("    Codigo        Produto     \n");
		for (it = tv_begin(); it != tv_end(); it = it->next) {
			printf("%10d %20s\n", it->prod.code, it->prod.name);
		}
	}
	else {
		printf("\nPilha de TVs vazia\n");
	}
	
	size = mo_size();
	if (size) {
		printf("\nPilha de Microondas:\n");
		printf("Itens: %d\n", size);
		printf("    Codigo        Produto     \n");
		for (it = mo_begin(); it != mo_end(); it = it->next) {
			printf("%10d %20s\n", it->prod.code, it->prod.name);
		}
	}
	else {
		printf("\nPilha de Microondas vazia\n");
	}
	
	size = pa_size();
	if (size) {
		printf("\nPilha de Panificadoras:\n");
		printf("Itens: %d\n", size);
		printf("    Codigo        Produto     \n");
		for (it = pa_begin(); it != pa_end(); it = it->next) {
			printf("%10d %20s\n", it->prod.code, it->prod.name);
		}
	}
	else {
		printf("\nPilha de Panificadoras vazia\n");
	}
	
	_wait();
}

void _menu_attend_order(int type) {
	product_t prod;
	
	_print_blank();
	
	if (attend_order(type, &prod)) {
		printf("Pedido atendido:\n");
		printf("Codigo:  %d\n", prod.code);
		printf("Produto: %s\n", prod.name);
	}
	else {
		printf("Não foi possível atender o pedido\n");
	}
	
    _wait();
}


void _menu_exit() {
	_print_blank();
	
	printf("\nEncerrando aplicação\n\n");
}

void _menu_default(int option) {
	
	_print_blank();
	
	printf("\n\nOpção %d inválida. Tente alguma disponível no Menu!\n\n",
			option);
	
	_wait();
}

void _print_blank() {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void _wait() {
	char c[2];
	printf("Pressione ENTER para continuar");
	fgets(c, 2, stdin);
}
