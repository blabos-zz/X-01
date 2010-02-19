/*
 * main.c
 *
 *  Created on: 04/12/2009
 *      Author: wesley
 */
#include <stdio.h>
#include <stdlib.h>

#include "rbtree.h"

int main(void) {
	node_t* tree = new_tree();

	print_in(tree);

	del_tree(tree);
	return EXIT_SUCCESS;
}
