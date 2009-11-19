/*
 * tree.c
 *
 *  Created on: 19/11/2009
 *      Author: wesley
 */
#include "tree.h"

#include <stdlib.h>
#include <stdio.h>



void        _del_node(node_t**, node_t*);
node_t*     _next_node(node_t*, int, int*);

void        _print_node(node_t*, int);
void        _print_in(node_t*, int);
void        _print_pre(node_t*, int);
void        _print_pos(node_t*, int);


node_t* new_tree() {
    return NULL;
}

void del_tree(node_t** root) {
    (void)root;
}

node_t* ins_node(node_t** node, int key) {
    if (!(*node)) {
        (*node) = (node_t*)malloc(sizeof(node_t));
        if (*node) {
            (*node)->key = key;
        }
        return (*node);
    }
    else if (key <= (*node)->key) {
        return ins_node(&((*node)->left), key);
    }
    else {
        return ins_node(&((*node)->right), key);
    }
}

void del_node(node_t** root, int key) {
    node_t* node = find_node(*root, key);
    
    if (node) {
        _del_node(root, node);
        free(node);
    }
}

node_t* next_node(node_t** root, int key) {
    node_t* node = find_node(*root, key);
    if (node) {
        if (node->right) return min_node(node->right);
        else {
            node_t* temp = find_parent(*root, node->key);
            while (temp && (temp->right == node)) {
                node = find_parent(*root, node->key);
                temp = find_parent(*root, temp->key);
            }
            return temp;
        }
    }
    else return node;
}

node_t* max_node(node_t* node) {
    if (node->right) return max_node(node->right);
    else return node;
}

node_t* min_node(node_t* node) {
    if (node->left) return min_node(node->left);
    else return node;
}

node_t* find_node(node_t* node, int key) {
    if (!node || (key == node->key)) return node;
    else if (key < node->key) return find_node(node->left, key);
    else return find_node(node->right, key);
}

node_t* find_parent(node_t* node, int key) {
    if (node) {
        if (key < node->key) {
            if (node->left && (key == node->left->key)) return node;
            else return find_parent(node->left, key);
        }
        else {
            if (node->right && (key == node->right->key)) return node;
            else return find_parent(node->right, key);
        }
    }
    else {
        return NULL;
    }
}

void print_in(node_t* node) {
    _print_in(node, 0);
}

void print_pre(node_t* node) {
    _print_pre(node, 0);
}

void print_pos(node_t* node) {
    _print_pos(node, 0);
}

void _print_in(node_t* node, int level) {
    if (node) {
        _print_in(node->left, level + 1);
        _print_node(node, level);
        _print_in(node->right, level + 1);
    }
}

void _print_pre(node_t* node, int level) {
    if (node) {
        _print_node(node, level);
        _print_pre(node->left, level + 1);
        _print_pre(node->right, level + 1);
    }
}

void _print_pos(node_t* node, int level) {
    if (node) {
        _print_pos(node->left, level + 1);
        _print_pos(node->right, level + 1);
        _print_node(node, level);
    }
}


void _print_node(node_t* node, int level) {
    int i;
    
    printf("{N:%10p L:%10p R:%10p}: ", node, node->left, node->right);
    for (i = 0; i <= level; i++) printf(".");
    printf("%d\n", node->key);
}

node_t* _next_node(node_t* node, int key, int* match) {
    if (node) {
        if (*match) return node;
        _next_node(node->left, key, match);
        if (key == node->key) (*match) = 1;
        _next_node(node->right, key, match);
    }
    else (*match) = 0;
    
    return NULL;
}


void _del_node(node_t** root, node_t* node) {
    node_t* parent = find_parent(*root, node->key);
    
    if (node->left && node->right) {
        // Dois filhos
        printf("Dois filhos\n");
        
        node_t* suc = next_node(root, node->key);
        _del_node(root, suc);
        
        if (parent) {
            if (parent->left == node)
                parent->left = suc;
            else
                parent->right = suc;
        }
        else {
            (*root) = suc;
        }
        
        suc->left   = node->left;
        suc->right  = node->right;
    }
    else if (!node->left && !node->right) {
        // Sem filhos
        printf("Sem filhos\n");
        
        if (parent) {
            if (parent->left == node) parent->left = NULL;
            else parent->right = NULL;
        }
    }
    else {
        // Um filho
        printf("Um filho\n");
        
        node_t* child = node->left ? node->left : node->right;
        
        if (parent->left == node) parent->left = child;
        else parent->right = child;
    }
}
