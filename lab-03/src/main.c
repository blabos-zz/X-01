/*
 * main.c
 *
 *  Created on: Oct 25, 2009
 *      Author: wesley
 */
#include "stock.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	init_stock();
	
	reload_wake();
	view_wake();
	
	reload_stock();
	view_stock();
	view_wake();
	
	return EXIT_SUCCESS;
}
