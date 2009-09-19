/*
 * main.c
 *
 *  Created on: Sep 19, 2009
 *      Author: blabos
 */
#include "double_linked_list.h"
#include "order.h"

#include <stdlib.h>
#include <stdio.h>

int main(void) {
	list_t* list;
	order_t* order;
	
	list = new_list();
	
	order = new_order();
	order->num = 1;
	push(list, order);
	
	order = new_order();
	order->num = 2;
	push(list, order);
	
	print_all_orders(list);
	
	del_list(list);
	return EXIT_SUCCESS;
}
