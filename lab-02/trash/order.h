/*
 * order.h
 *
 *  Created on: Sep 19, 2009
 *      Author: blabos
 */

#ifndef ORDER_H_
#define ORDER_H_

#include "double_linked_list.h"

typedef struct {
	int num;
} order_t;

order_t* new_order();
void del_order(order_t* order);
void print_order(const order_t* order);
void print_all_orders(list_t* list);

#endif /* ORDER_H_ */
