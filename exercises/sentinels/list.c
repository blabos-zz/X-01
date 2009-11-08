/*
 * list.c
 *
 *  Created on: 08/11/2009
 *      Author: blabos
 */
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

node_t*     _new_node();
void        _del_node(node_t*);


list_t* new_list() {
    list_t* list = (list_t*)malloc(sizeof(list_t));
    node_t* node = _new_node();
    
    if (list && node) {
        node->next = node->prev = node;
        node->data = 0;
        list->nil = node;
    }
    
    return list;
}

void del_list(list_t* list) {
    node_t* it;
    
    for (it = list->nil->next; it != list->nil; it = it->next) {
        delete(list, it);
    }
    
    _del_node(list->nil);
    free(list);
}

void print_list(list_t* list) {
    node_t* it;
    
    for (it = list->nil->next; it != list->nil; it = it->next) {
        printf("{%8p <- %8p -> %8p}: %d\n", it->prev, it, it->next, it->data);
    }
}

node_t* head(list_t* list) {
    return list->nil->next;
}

node_t* tail(list_t* list) {
    return list->nil->prev;
}

node_t* find(list_t* list, int data) {
    node_t* node = head(list);
    
    while ((node != list->nil) && (node->data != data)) {
        node = node->next;
    }
    
    return node;
}

node_t* insert(list_t* list, int data) {
    node_t* node = _new_node();
    
    if (node) {
        node->data = data;
        
        node->next = list->nil->next;
        list->nil->next->prev = node;
        list->nil->next = node;
        node->prev = list->nil;
    }
    
    return node;
}

void delete(list_t* list, node_t* node) {
    node->next->prev = node->prev;
    node->prev->next = node->next;
    _del_node(node);
}


node_t* _new_node() {
    return (node_t*)malloc(sizeof(node_t));
}

void _del_node(node_t* node) {
    free(node);
}
