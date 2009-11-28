/*
 * tree.c
 *
 *  Created on: 19/11/2009
 *      Author: wesley
 */
#include "tree.h"

#include <stdlib.h>
#include <stdio.h>


tnode_t*    _del_node(tnode_t**, int key);

void        _print_node(tnode_t*, int);
void        _print_in(tnode_t*, int);


tnode_t* new_tree() {
    return NULL;
}

void del_tree(tnode_t** root) {
    (void)root;
}

tnode_t* new_tnode(char key) {
    tnode_t* node = (tnode_t*)malloc(sizeof(tnode_t));
    if (node) {
        node->key = key;
        
        if ((key == '+') || (key == '-') || (key == '*') || (key == '/')) {
            node->type = 'T';
        } else if (key == '(') {
            node->type = 'P';
        }
        else if (key == ')') {
            node->type = 'C';
        }
        else if ((key >= '0') && (key <= '9')){
            node->type = 'O';
        }
        else {
            node->type = 'X';
        }
        
        node->left = node->right = NULL;
    }
    return node;
}

tnode_t* make_sub_tree(tnode_t* op1, tnode_t* opr, tnode_t* op2) {
    opr->left   = op1;
    opr->right  = op2;
    opr->type   = 'O';
    
    return opr;
}

tnode_t* make_parse_tree(char* str) {
    list_t*     stack   = new_list();
    tnode_t*    tree    = new_tree();
    
    char bla;
    while (*str || stack->size) {
        printf("ENTER\n");
        scanf("%c", &bla);
        
        if (has_oto(stack)) {
            printf("has oto\n");
            tree = push(stack, make_sub_tree(pop(stack), pop(stack), pop(stack)));
        }
        
        if (*str) {
            printf("push '%c'\n", *str);
            push(stack, new_tnode(*str++));
        }
        print_list(stack);
        
        if (has_oto(stack)) {
            printf("has oto\n");
            tree = push(stack, make_sub_tree(pop(stack), pop(stack), pop(stack)));
        }
        
        if (has_C(stack)) {
            printf("has c\n");
            pop(stack);
            
            if (has_oto(stack)) {
                printf("has oto\n");
                tree = push(stack, make_sub_tree(pop(stack), pop(stack), pop(stack)));
            }
            tree = pop(stack);
            pop(stack);
            tree = push(stack, tree);
        }
        
        if (!*str && (stack->size == 1)) {
            tree = pop(stack);
            break;
        }
        print_in(tree);
    }
    
    del_list(stack);
    
    return tree;
}


void print_in(tnode_t* node) {
    _print_in(node, 0);
}

void _print_in(tnode_t* node, int level) {
    if (node) {
        _print_in(node->left, level + 1);
        _print_node(node, level);
        _print_in(node->right, level + 1);
    }
}

void _print_pre(tnode_t* node, int level) {
    if (node) {
        _print_node(node, level);
        _print_pre(node->left, level + 1);
        _print_pre(node->right, level + 1);
    }
}

void _print_pos(tnode_t* node, int level) {
    if (node) {
        _print_pos(node->left, level + 1);
        _print_pos(node->right, level + 1);
        _print_node(node, level);
    }
}


void _print_node(tnode_t* node, int level) {
    int i;
    
    printf("{N:%10p L:%10p R:%10p}: (%c)",
            node, node->left, node->right, node->type);
    for (i = 0; i <= level; i++) printf(".");
    printf("%c\n", node->key);
}
