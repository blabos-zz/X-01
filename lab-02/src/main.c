/*
 * main.c
 *
 *  Created on: Sep 19, 2009
 *      Author: blabos
 */
//#include "stock.h"
#include "orders.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	order_list_t* list = new_order_list();
	stock_init();
	stock_reload();
	
	order_t b1 = {{100,1,1,1,1}, NULL, NULL};
	request_order(list, b1);
	order_t b2 = {{2,2,2,2,2}, NULL, NULL};
	request_order(list, b2);
	order_t b3 = {{300,3,3,3,3}, NULL, NULL};
	request_order(list, b3);
	print_order_list(list);
	stock_show();
	printf("\n");
	
	order_t b4;
	if(attend_order(list, &b4)) {
		printf("\natendi: ");
		print_order(&b4);
		print_order_list(list);
		printf("\n");
	}
	else {
		printf("Nao pude atender\n");
	}
	
	if(attend_order(list, &b4)) {
		printf("\natendi: ");
		print_order(&b4);
		print_order_list(list);
		printf("\n");
	}
	else {
		printf("Nao pude atender\n");
	}
	
	if(attend_order(list, &b4)) {
		printf("\natendi: ");
		print_order(&b4);
		print_order_list(list);
		printf("\n");
	}
	else {
		printf("Nao pude atender\n");
	}
	
	if(attend_order(list, &b4)) {
		printf("\natendi: ");
		print_order(&b4);
		print_order_list(list);
		printf("\n");
	}
	else {
		printf("Nao pude atender\n");
	}
	
	del_order_list(list);
	return EXIT_SUCCESS;
}
