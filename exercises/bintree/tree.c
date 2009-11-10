/*
 * tree.c
 *
 *  Created on: 10/11/2009
 *      Author: blabos
 */
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

void        _print_node(node_t*, int);

node_t* insert(node_t** node, int data) {
    node_t* temp;
    
    if (*node == NULL) {
        (*node) = (node_t*)malloc(sizeof(node_t));
        if (*node) (*node)->data = data;
        return (*node);
    }
    else if (data <= (*node)->data) temp = insert(&((*node)->left), data);
    else temp = insert(&((*node)->right), data);
    
    temp->parent = (*node);
    
    return (*node);
}

void print_in(node_t* node, int level) {
    if (node) {
        print_in(node->left, level + 1);
        _print_node(node, level);
        print_in(node->right, level + 1);
    }
}

void print_pre(node_t* node, int level) {
    if (node) {
        _print_node(node, level);
        print_in(node->left, level + 1);
        print_in(node->right, level + 1);
    }
}

void print_pos(node_t* node, int level) {
    if (node) {
        print_in(node->left, level + 1);
        print_in(node->right, level + 1);
        _print_node(node, level);
    }
}


void _print_node(node_t* node, int level) {
    int i;
    
    printf("{%10p %10p %10p %10p}: ",
            node->parent, node, node->left, node->right);
    for (i = 0; i <= level; i++) printf(".");
    printf("%d\n", node->data);
}
