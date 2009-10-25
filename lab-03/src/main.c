/*
 * main.c
 *
 *  Created on: Oct 25, 2009
 *      Author: wesley
 */
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	list_t* list = new_list();
	
	node_t node;
	
	node.code = 1;
	strncpy(node.name, "Nome 1", MAX_STR);
	push_back(list, &node);
	
	node.code = 2;
	strncpy(node.name, "Nome 2", MAX_STR);
	push_back(list, &node);
	
	node.code = 3;
	strncpy(node.name, "Nome 3", MAX_STR);
	push_back(list, &node);
	
	node.code = 4;
	strncpy(node.name, "Nome 4", MAX_STR);
	push_back(list, &node);
	
	print_list(list);
	
	pop_front(list, &node);
	pop_front(list, &node);
	
	print_list(list);
	print_node(&node);
	
	del_list(list);
	return EXIT_SUCCESS;
}
