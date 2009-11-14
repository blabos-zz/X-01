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
node_t*     _ins_node(node_t**, node_t*, int);


node_t* new_tree() {
    return NULL;
}

void del_tree(node_t** root) {
    (void)root;
}

node_t* ins_node(node_t** node, int key) {
    return _ins_node(node, NULL, key);
}

node_t* _ins_node(node_t** node, node_t* parent, int key) {
    if (*node == NULL) {
        (*node) = (node_t*)malloc(sizeof(node_t));
        if (*node) {
            (*node)->key    = key;
            (*node)->parent = parent;
        }
        return (*node);
    }
    else if (key <= (*node)->key) {
        return _ins_node(&((*node)->left), (*node), key);
    }
    else {
        return _ins_node(&((*node)->right), (*node), key);
    }
}

void del_node(node_t** root, node_t* node) {
    if (node) {
        if (node->left && node->right) {
            // Dois filhos
            
            node_t* sucessor = next_node(node);
            
            if (node->parent) {
                if (node->parent->left == node) {
                    // Nó a deletar à esquerda do seu pai
                    node->parent->left = sucessor;
                    node->right->parent = sucessor;
                }
                else {
                    // Nó a deletar à direita do seu pai
                    node->parent->right = sucessor;
                }
            }
            else {
                (*root) = sucessor;
            }
            
            if (sucessor->parent->left == sucessor) {
                // Sucessor à esquerda do seu pai.
                sucessor->parent->left  = sucessor->right;
                sucessor->right         = node->right;
                sucessor->right->parent = sucessor;
            }
            
            sucessor->left      = node->left;
            sucessor->parent    = node->parent;
            node->left->parent  = sucessor;
        }
        else if (!(node->left
                || node->right)) {
            // Nenhum filho
            if(node->parent->left == node) node->parent->left = NULL;
            else node->parent->right = NULL;
        }
        else {
            // Somente um filho
            
            node_t* child = node->left ? node->left : node->right;
            
            if(node->parent->left == node) node->parent->left = child;
            else node->parent->right = child;
        }
        
        free(node);
    }
}

node_t* next_node(node_t* node) {
    if (node) {
        if (node->right) return min_node(node->right);
        else {
            node_t* temp = node->parent;
            while (temp && (temp->right == node)) {
                node = node->parent;
                temp = temp->parent;
            }
            return temp;
        }
    }
    else return node;
}

node_t* prev_node(node_t* node) {
    if (node) {
        if (node->left) return max_node(node->left);
        else {
            node_t* temp = node->parent;
            while (temp && (temp->left == node)) {
                node = node->parent;
                temp = temp->parent;
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
    
    printf("{P:%10p N:%10p L:%10p R:%10p}: ",
            node->parent, node, node->left, node->right);
    for (i = 0; i <= level; i++) printf(".");
    printf("%d\n", node->key);
}
