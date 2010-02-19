/*
 * main.c
 *
 *  Created on: Aug 27, 2009
 *      Author: wesley
 */

#include "contacts.h"
#include "menu.h"

#include <stdlib.h>

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	
	contacts_t list;
	int option = 0;
	
	init(&list);
	
	do {
		print_menu(&list);
		option = read_option();
		dispatch(&list, option);
	} while (option != 6);
	
	return 0;
}
