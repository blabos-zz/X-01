/*
 * main.c
 *
 *  Created on: Sep 19, 2009
 *      Author: blabos
 */
#include "orders.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	order_list_t* list = new_order_list();
	stock_init();
	stock_reload();
	
	print_order_list(list);
	
	del_order_list(list);
	return EXIT_SUCCESS;
}

