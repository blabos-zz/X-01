/*
 * double_linked_list.c
 *
 *  Created on: Sep 19, 2009
 *      Author: blabos
 */
#include "double_linked_list.h"

#include <stdlib.h>
#include <stdio.h>

list_t* new_list() {
	list_t* list	= (list_t*)malloc(sizeof(list_t));
	
	list->head = NULL;
	list->tail = NULL;
	
	return list;
}

void del_list(list_t* list) {
	free(list);
}

void print_list(list_t* list) {
	node_t* curr = list->head;
	
	while (curr) {
		printf("%10p <- %10p -> %10p: %10p\n",
				curr->prev, curr, curr->next, curr->data);
		curr = curr->next;
	}
}

node_t* push(list_t* list, void* value) {
	node_t* node = (node_t*)malloc(sizeof(node_t));
	
	if (node) {
		if (list->tail == NULL) {
			// cauda não inicializada
			list->tail = node;
		}
		
		if (list->head == NULL) {
			// lista vazia
			list->head = node;
		}
		else {
			// lista com elementos
			node->next = list->head;
			list->head->prev = node;
			list->head = node;
		}
		
		node->data = value;
	}
	
	return node;
}

void pop(list_t* list) {
	node_t* node;
	
	if (list->tail) {
		node = list->tail;
		
		if (node->prev == NULL) {
			// Foi-se o último elemento
			list->head = list->tail = NULL;
		}
		else {
			// Ainda há outros elementos.
			list->tail = node->prev;
			list->tail->next = NULL;
		}
		
		free(node);
	}
}
