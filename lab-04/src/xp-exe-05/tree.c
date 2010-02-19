/*
 * tree.c
 *
 *  Created on: 19/11/2009
 *      Author: wesley
 */
#include "tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
        
        switch (key) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': node->type = operand;             break;
            case '+':
            case '-': node->type = low_operator;        break;
            case '*':
            case '/': node->type = high_operator;       break;
            case '(': node->type = open_parentesis;     break;
            case ')': node->type = close_parentesis;    break;
            case '\0':node->type = end_of_expression;   break;
            default:  node->type = unknown_token;
        }
        
        node->left = node->right = NULL;
    }
    return node;
}

tnode_t* make_sub_tree(tnode_t* op1, tnode_t* opr, tnode_t* op2) {
    op1->type = op2->type = leaf;
    
    opr->left   = op1;
    opr->right  = op2;
    opr->type   = operand;
    
    return opr;
}

tnode_t* make_parse_tree(char* str) {
    list_t*     stack   = new_list();
    tnode_t*    tree    = new_tree();
    
    tnode_t* curr = NULL;
    int slen = strlen(str);
    int level = 0;
    int error = 1;
    do {
        if (slen-- > 0) {
            char c = *str++;
            if (c == ' ') continue;
            
            curr = new_tnode(c);
            if (curr->type != close_parentesis) {
                push(stack, curr);
            }
            
            if (curr->type == open_parentesis)  level++;
            if (curr->type == close_parentesis) level--;
            
            if (level < 0) {
                error = 1; break;
            }
        }
        else {
            curr->type = end_of_expression;
            if (!tree || (level > 0)) {
                error = 1; break;
            }
            
            lnode_t* h = head(stack);
            if ((stack->size == 1) && (tree == h->data)) {
                error = 0;
                break;
            }
        }
        
        if (has_oto(stack)) {
            if (curr->type != high_operator) {
                // Desempilha um operando
                // Desempilha o operador
                // Desempilha outro operando
                // Cria sub-árvore com os três elementos anteriores
                // Coloca a sub-árvore na pilha
                tree = push(
                    stack,
                    make_sub_tree(
                        pop(stack),
                        pop(stack),
                        pop(stack)
                    )
                );
            }
        }
        
        if (curr->type == close_parentesis) {
            // Retire o único elemento que estará acima do abre parentêsis
            tree = pop(stack);
            
            // Elimine o abre parêntesis
            pop(stack);
            
            // Devolva a sub-árvore para a pilha
            tree = push(stack, tree);
            
            if (has_oto(stack)) {
                // Desempilha um operando
                // Desempilha o operador
                // Desempilha outro operando
                // Cria sub-árvore com os três elementos anteriores
                // Coloca a sub-árvore na pilha
                tree = push(
                    stack,
                    make_sub_tree(
                        pop(stack),
                        pop(stack),
                        pop(stack)
                    )
                );
            }
        }
    } while (has_oto(stack) || (curr->type != end_of_expression));
    
    del_list(stack);
    
    if (error) {
        return NULL;
    }
    else {
        return tree;
    }
}

void print_expr(tnode_t* node) {
    if (node) {
        if (node->left && (node->key == '*' || node->key == '/') && (node->left->key == '+' || node->left->key == '-')) {
            printf("(");
            print_expr(node->left);
            printf(")");
        }
        else {
            print_expr(node->left);
        }
        
        printf(" %c ", node->key);
        
        if (node->right && (node->key == '*' || node->key == '/') && (node->right->key == '+' || node->right->key == '-')) {
            printf("(");
            print_expr(node->right);
            printf(")");
        }
        else {
            print_expr(node->right);
        }
    }
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
    
    printf("{N:%10p L:%10p R:%10p}: (%d)",
            node, node->left, node->right, node->type);
    for (i = 0; i <= level; i++) printf(".");
    printf("%c\n", node->key);
}
