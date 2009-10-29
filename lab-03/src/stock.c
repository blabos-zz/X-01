
/*
 * stock.c
 *
 *  Created on: Oct 29, 2009
 *      Author: wesley
 */
#include "stock.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

stock_t*	_get_stock();
queue_t*	_get_wake();

int			_random(int a, int b);

product_t	_new_product(int);
product_t	_new_tv();
product_t	_new_mo();
product_t	_new_pa();




void init_stock() {
	stock_t* stock = _get_stock();
	
	stock->tv	= new_list();
	stock->mo	= new_list();
	stock->pa	= new_list();
	
	srand(time(NULL));
}

void view_stock() {
	stock_t* stock = _get_stock();
	
	printf("\nEstoque de TVs\n");
	print_list(stock->tv);
	
	printf("\nEstoque de Microondas\n");
	print_list(stock->mo);
	
	printf("\nEstoque de Panificadoras\n");
	print_list(stock->pa);
}

void view_wake() {
	queue_t* wake = _get_wake();
	
	printf("\nEstado da Esteira\n");
	print_list(wake);
}

void reload_wake() {
	int i;
	product_t prod;
	int nprod = _random(MIN_WAKE, MAX_WAKE);
	
	for (i = 0; i < nprod; i++) {
		prod = _new_product(_random(TV, PA));
		push_back(_get_wake(), &prod);
	}
}

void reload_stock() {
	product_t prod;
	int type;
	
	while (_get_wake()->size) {
		pop_front(_get_wake(), &prod);
		
		type = prod.code / TYPE_OFFSET;
		
		switch(type) {
		case TV:	push_front(_get_stock()->tv, &prod); break;
		case MO:	push_front(_get_stock()->mo, &prod); break;
		case PA:	push_front(_get_stock()->pa, &prod); break;
		default:	printf("Produto desconhecido na esteira: {%10d, %20s}",
				prod.code, prod.name);
		}
	}
}


stock_t* _get_stock() {
	static stock_t _stock;
	return &_stock;
}

queue_t* _get_wake() {
	static queue_t* _wake = new_list();
	return _wake;
}

int _random(int a, int b) {
	return a + (rand() % abs(1 + b - a));
}

product_t _new_product(int type) {
	product_t prod;
	
	switch (type) {
		case TV:	prod = _new_tv(); break;
		case MO:	prod = _new_mo(); break;
		case PA:	prod = _new_pa(); break;
		default:	prod = _new_tv();
	}
	
	return prod;
}

product_t _new_tv() {
	static int serial = 1;
	
	product_t prod;
	
	prod.code = TYPE_OFFSET * TV + serial++;
	strncpy(prod.name, "TV Full-Fill", MAX_STR);
	
	return prod;
}

product_t _new_mo() {
	static int serial = 1;
	
	product_t prod;
	
	prod.code = TYPE_OFFSET * MO + serial++;
	strncpy(prod.name, "Microondas D. Maria", MAX_STR);
	
	return prod;
}

product_t _new_pa() {
	static int serial = 1;
	
	product_t prod;
	
	prod.code = TYPE_OFFSET * PA + serial++;
	strncpy(prod.name, "Panificadora Panaca", MAX_STR);
	
	return prod;
}
