/*
 * orders.h
 *
 *  Created on: Sep 19, 2009
 *      Author: blabos
 */
#ifndef ORDERS_H_
#define ORDERS_H_

#include "stock.h"

typedef stock_t order_item_t;

struct order_st {
	order_item_t		data;
	struct order_st*	next;
	struct order_st*	prev;
};

typedef struct order_st order_t;

typedef struct {
	order_t*			head;
	order_t*			tail;
	unsigned			size;
} order_list_t;


order_list_t*	new_order_list();
void			del_order_list(order_list_t* list);
void			print_order_list(const order_list_t* list);
void			print_order(const order_t* order);

int				request_order(order_list_t* list, order_t order);
int				attend_order(order_list_t* list, order_t* order);

order_t*	    orders_begin(const order_list_t* list);
order_t*	    orders_end(const order_list_t* list);




#endif /* ORDERS_H_ */
