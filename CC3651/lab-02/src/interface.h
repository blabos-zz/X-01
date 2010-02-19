/*
 * interface.h
 *
 *  Created on: Oct 2, 2009
 *      Author: blabos
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "orders.h"


#define MENU_EXIT 10


void print_menu();
int read_option();
void dispatch(order_list_t* orders, int option);


#endif /* MENU_H_ */
