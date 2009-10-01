/*
 * orders.c
 *
 *  Created on: Sep 19, 2009
 *      Author: blabos
 */
#include "orders.h"

#include <stdlib.h>
#include <stdio.h>

order_t*	_new_order(const order_t* order);
void		_del_order(order_t* order);

void		_remove_order(order_list_t* list, order_t* order);
order_t*	_find_attendable_order(order_list_t* list);
int			_can_attend(const order_t* order);

order_t*	_orders_begin(const order_list_t* list);
order_t*	_orders_end(const order_list_t* list);

order_list_t* new_order_list() {
	order_list_t* list = (order_list_t*)malloc(sizeof(order_list_t));
	
	list->head = list->tail = (void*)(list->size = 0);
	
	return list;
}

void del_order_list(order_list_t* list) {
	free(list);
}

void print_order_list(const order_list_t* list) {
	printf("Head: %10p\n", list->head);
	printf("Tail: %10p\n", list->tail);
	printf("Size: %10d\n", list->size);
	
	order_t* it = _orders_begin(list);
	
	if (it) {
		printf("Data: \n\n");
	}
	
	for (it = _orders_begin(list); it != _orders_end(list); it = it->next) {
		print_order(it);
	}
}

int request_order(order_list_t* list, order_t order) {
	order_t* node = _new_order(&order);
	
	if (node) {
		if (list->tail == NULL) {
			// Cauda não inicializada
			list->tail = node;
		}
		
		if (list->head == NULL) {
			// Lista vazia
			list->head = node;
		}
		else {
			// Há outros elementos
			node->next = list->head;
			list->head->prev = node;
			list->head = node;
		}
		list->size++;
	}
	
	return (int)node;
}

int attend_order(order_list_t* list, order_t* order) {
	int retval = 0;
	order_t* node;
	
	if ((node = _find_attendable_order(list)) != NULL) {
		stock_request_bean(node->data.bean);
		stock_request_corn(node->data.corn);
		stock_request_milk(node->data.milk);
		stock_request_rice(node->data.rice);
		stock_request_wine(node->data.wine);
		
		*order = *node;
		order->next = order->prev = NULL;
		
		_remove_order(list, node);
		list->size--;
		
		retval = 1;
	}
	
	return retval;
}

order_t* _new_order(const order_t* order) {
	order_t* node = (order_t*)malloc(sizeof(order_t));
	
	if (node) {
		(*node) = (*order);
		node->next = node->prev = NULL;
	}
	
	return node;
}

void _del_order(order_t* order) {
	free(order);
}

void print_order(const order_t* order) {
	printf("%10p <- %10p -> %10p: {%3d, %3d, %3d, %3d, %3d}\n",
				order->prev, order, order->next,
				order->data.bean,
				order->data.corn,
				order->data.milk,
				order->data.rice,
				order->data.wine);
}

void _remove_order(order_list_t* list, order_t* order) {
	if (list->head == list->tail) {
		list->head = list->tail = NULL;
	}
	else if (order == list->head) {
		list->head = order->next;
		if (list->head) list->head->prev = NULL;
	}
	else if (order == list->tail) {
		list->tail = order->prev;
		if (list->tail) list->tail->next = NULL;
	}
	else {
		order->prev->next = order->next;
		order->next->prev = order->prev;
	}
	
	_del_order(order);
}

order_t* _find_attendable_order(order_list_t* list) {
	order_t* it;
	
	for (it = _orders_begin(list); it != _orders_end(list); it = it->next) {
		if (_can_attend(it)) {
			return it;
		}
	}
	
	return NULL;
}

int _can_attend(const order_t* order) {
	return (stock_has_bean(order->data.bean) &&
			stock_has_corn(order->data.corn) &&
			stock_has_milk(order->data.milk) &&
			stock_has_rice(order->data.rice) &&
			stock_has_wine(order->data.wine));
}

order_t* _orders_begin(const order_list_t* list) {
	return list->head;
}

order_t* _orders_end(const order_list_t* list) {
	return list-> tail ? list->tail->next: NULL;
}
