/*
 * list.c
 *
 *  Created on: 08/11/2009
 *      Author: blabos
 */
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

lnode_t*    _new_node();
void        _del_node(lnode_t*);


list_t* new_list() {
    list_t* list = (list_t*)malloc(sizeof(list_t));
    lnode_t* lnode = _new_node();
    
    if (list && lnode) {
        lnode->next = lnode->prev = lnode;
        lnode->data = new_tnode('X');
        list->nil = lnode;
    }
    
    return list;
}

void del_list(list_t* list) {
    lnode_t* it;
    
    for (it = list->nil->next; it != list->nil; it = it->next) {
        delete(list, it);
    }
    
    _del_node(list->nil);
    free(list);
}

void print_list(list_t* list) {
    lnode_t* it;
    
    for (it = list->nil->next; it != list->nil; it = it->next) {
        print_lnode(it);
    }
}

void print_lnode(lnode_t* lnode) {
    printf("{%8p <- %8p -> %8p} => [%8p <- %8p -> %8p]: (%c - %c)\n",
            lnode->prev, lnode, lnode->next,
            lnode->data->left, lnode->data, lnode->data->right,
            lnode->data->type, lnode->data->key);
}

void print_tnode(tnode_t* tnode) {
    printf("[%8p <- %8p -> %8p]: (%c - %c)\n",
            tnode->left, tnode, tnode->right, tnode->type, tnode->key);
}

lnode_t* head(list_t* list) {
    return list->nil->next;
}

lnode_t* tail(list_t* list) {
    return list->nil->prev;
}

lnode_t* find(list_t* list, tnode_t* data) {
    lnode_t* lnode = head(list);
    
    while ((lnode != list->nil) && (lnode->data != data)) {
        lnode = lnode->next;
    }
    
    return lnode;
}

lnode_t* insert(list_t* list, tnode_t* data) {
    lnode_t* lnode = _new_node();
    
    if (lnode) {
        lnode->data = data;
        
        lnode->next = list->nil->next;
        list->nil->next->prev = lnode;
        list->nil->next = lnode;
        lnode->prev = list->nil;
        list->size++;
    }
    
    return lnode;
}

void delete(list_t* list, lnode_t* lnode) {
    lnode->next->prev = lnode->prev;
    lnode->prev->next = lnode->next;
    list->size--;
    _del_node(lnode);
}

tnode_t* push(list_t* list, tnode_t* tnode) {
    return insert(list, tnode)->data;
}

tnode_t* pop(list_t* list) {
    tnode_t* retval = head(list)->data;
    
    delete(list, head(list));
    
    return retval;
}

int has_oto(list_t* list) {
    lnode_t* h1 = head(list);
    lnode_t* h2 = h1->next;
    lnode_t* h3 = h2->next;
    
    return ((h1->data->type == 'O') &&
            (h2->data->type == 'T') &&
            (h3->data->type == 'O'));
}

int has_C(list_t* list) {
    return head(list)->data->type == 'C';
}


lnode_t* _new_node() {
    return (lnode_t*)malloc(sizeof(lnode_t));
}

void _del_node(lnode_t* node) {
    free(node);
}
