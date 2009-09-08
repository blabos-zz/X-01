/*
 * main.c
 *
 *  Created on: Aug 27, 2009
 *      Author: wesley
 */

#include "contacts.h"
#include "menu.h"

#include <stdio.h>

int main(int argc, char** argv) {
	contacts_t list;
	int option = 0;
	
	init(&list);
	
	do {
		print_menu();
		option = read_option();
		dispatch(&list, option);
	} while (option != 0);
	
	return 0;
}
