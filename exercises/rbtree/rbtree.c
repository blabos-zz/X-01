/*
 * rbtree.c
 *
 *  Created on: 04/12/2009
 *      Author: wesley
 */
#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>


void		_print_in(node_t*, int);
void 		_print_node(node_t* node, int level);


node_t* new_tree() {
	nil = (node_t*)malloc(sizeof(node_t));
	nil->color = 'B';
	nil->parent = nil->left = nil->right = nil;

	return nil;
}

void del_tree(node_t* tree) {
	(void)tree;
}

void print_in(node_t* node) {
    _print_in(node, 0);
}


void _print_in(node_t* node, int level) {
    if (node != nil) {
        _print_in(node->left, level + 1);
        _print_node(node, level);
        _print_in(node->right, level + 1);
    }
}

void _print_node(node_t* node, int level) {
    int i;

    printf("%10p: {N:%10p L:%10p R:%10p}: ", node->parent, node, node->left, node->right);
    for (i = 0; i <= level; i++) printf(".");
    printf("%c:%d\n", node->color, node->key);
}
