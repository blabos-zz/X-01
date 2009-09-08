/*
 * menu.h
 *
 *  Created on: Sep 7, 2009
 *      Author: wesley
 */

#ifndef MENU_H_
#define MENU_H_


#include "contacts.h"


void print_menu();
int read_option();
void dispatch(contacts_t* list, int option);


#endif /* MENU_H_ */
