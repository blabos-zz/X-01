/*
 * main.c
 *
 *  Created on: Oct 25, 2009
 *      Author: wesley
 */
#include "interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int option;

	init_stock();
	
	do {
		print_menu();
		option = read_option();
		dispatch(option);
	} while (option != MENU_EXIT);

	return EXIT_SUCCESS;
}
