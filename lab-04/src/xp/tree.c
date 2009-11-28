/*
 * tree.c
 *
 *  Created on: 19/11/2009
 *      Author: wesley
 */
#include "tree.h"

#include <stdlib.h>
#include <stdio.h>


node_t*     _del_node(node_t**, int key);

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

node_t* new_node(char key) {
    node_t* node = (node_t*)malloc(sizeof(node_t));
    if (node) {
        node->key = key;
        node->left = node->right = NULL;
    }
    return node;
}

node_t* ins_node(node_t** node, int key) {
    if (!(*node)) {
        (*node) = (node_t*)malloc(sizeof(node_t));
        if (*node) {
            (*node)->key = key;
            (*node)->left = (*node)->right = NULL;
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
    node_t* node = _del_node(root, key);
    if (node) {
        free(node);
    }
}

node_t* max_node(node_t* node) {
    if (node->right) return max_node(node->right);
    else return node;
}

node_t* min_node(node_t* node) {
    if (node && node->left) return min_node(node->left);
    else return node;
}

node_t* find_node(node_t* node, int key) {
    if (!node || (key == node->key)) return node;
    else if (key < node->key) return find_node(node->left, key);
    else return find_node(node->right, key);
}

void find_parent(node_t* root, int key, node_t** node, node_t** parent) {
    (*node) = (*parent) = NULL;
    
    if (root) {
        if (key == root->key) {
            (*node)     = root;
            (*parent)   = NULL;
            printf("%d: ===> %p -> %p\n", key, (*node), (*parent));
        }
        else if (key < root->key) {
            if (root->left && (key == root->left->key)) {
                (*node)     = root->left;
                (*parent)   = root;
            }
            else {
                find_parent(root->left, key, node, parent);
            }
        }
        else {
            if (root->right && (key == root->right->key)) {
                (*node)     = root->right;
                (*parent)   = root;
            }
            else {
                find_parent(root->right, key, node, parent);
            }
        }
    }
}

int count_nodes(node_t* node) {
    if (!node) {
        return 0;
    }
    else {
        return count_nodes(node->left) + 1 + count_nodes(node->right);
    }
}

int count_leaves(node_t* node) {
    if (!node) {
        return 0;
    }
    else if (!(node->left || node->right)) {
        return 1;
    }
    else {
        return count_leaves(node->left) + count_leaves(node->right);
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
    printf("%c\n", node->key);
}


node_t* _del_node(node_t** root, int key) {
    node_t* node;
    node_t* pnode;
    node_t* replacer;
    
    find_parent(*root, key, &node, &pnode);
    
    if (node) {
        if (node->left && node->right) {
            replacer = min_node(node->right);
        }
        else {
            replacer = node->left ? max_node(node->left) : min_node(node->right);
        }
        
        if (replacer) {
            _del_node(root, replacer->key);
            replacer->left  = node->left;
            replacer->right = node->right;
        }
                
        if (pnode) {
            if (node->key < pnode->key) {
                pnode->left = replacer;
            }
            else {
                pnode->right = replacer;
            }
        }
        else {
            (*root) = replacer;
        }
    }
    
    return node;
}
