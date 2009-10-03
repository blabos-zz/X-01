/*
 * store.h
 *
 *  Created on: Oct 3, 2009
 *      Author: blabos
 */

#ifndef STORE_H_
#define STORE_H_


#include "orders.h"
#include "stock.h"

int save(const order_list_t* list, char* filename);
int load(order_list_t* list, char* filename);

#endif /* STORE_H_ */
