/*
 * main.c
 *
 *  Created on: 08/11/2009
 *      Author: blabos
 */
#include "list.h"

#include <stdlib.h>
#include <stdio.h>

int main(void) {
	list_t* list = new_list();
	node_t* node;
	
	insert(list, 1);
	insert(list, 2);
	insert(list, 3);
	
	print_list(list);
	
	node = find(list, 2);
	delete(list, node);
	
	printf("\n");
	print_list(list);
	
	del_list(list);
	return EXIT_SUCCESS;
}
