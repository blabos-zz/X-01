/*
 * interface.h
 *
 *  Created on: Nov 7, 2009
 *      Author: blabos
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "stock.h"

typedef struct {
	stock_t*	stock;
	queue_t*	wake;
} data_t;


#define MENU_EXIT 10


void print_menu();
int read_option();
void dispatch(int option);


#endif /* MENU_H_ */
