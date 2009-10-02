/*
 * main.c
 *
 *  Created on: Oct 2, 2009
 *      Author: blabos
 */
#include "interface.h"
#include "orders.h"

#include <stdlib.h>

int main(void) {
	int option = 0;
	
	order_list_t* orders = new_order_list();
	
	do {
		print_menu();
		option = read_option();
		dispatch(orders, option);
	} while (option != MENU_EXIT);
	
	del_order_list(orders);
	return EXIT_SUCCESS;
}


