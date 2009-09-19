/*
 * order.c
 *
 *  Created on: Sep 19, 2009
 *      Author: blabos
 */
#include "order.h"

#include <stdlib.h>
#include <stdio.h>

order_t* new_order() {
	order_t* order = (order_t*)malloc(sizeof(order_t));
	
	return order;
}

void del_order(order_t* order) {
	free(order);
}

void print_order(const order_t* order) {
	printf("%10p: %10d\n", order, order->num);
}

void print_all_orders(list_t* list) {
	node_t* curr = list->head;
	
	while (curr) {
		printf("%10p <- %10p -> %10p: %10p = %d\n",
				curr->prev, curr, curr->next, curr->data, ((order_t*)(curr->data))->num);
		curr = curr->next;
	}
}
