/*
 * list.c
 *
 *  Created on: Oct 24, 2009
 *      Author: wesley
 */
#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


node_t*		_new_node();
void		_del_node(node_t*);

void		_set_prod(product_t*, const product_t*);


list_t* new_list() {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	
	return list;
}

void del_list(list_t* list) {
	free(list);
}

int push_front(list_t* list, product_t* p) {
    int retval = 0;
    
	node_t* node = _new_node();
	_set_prod(&(node->prod), p);
	
	if (node) {
		if (list->tail == NULL) {
			// Cauda não inicializada
			list->tail = node;
		}
		
		if (list->head == NULL) {
			// Lista vazia
			list->head = node;
		}
		else {
			// Há outros elementos
			node->next = list->head;
			list->head->prev = node;
			list->head = node;
		}
		list->size++;
		retval = node->prod.code;
	}
	
	return retval;
}

int push_back(list_t* list, product_t* p) {
    int retval = 0;
    
	node_t* node = _new_node();
	_set_prod(&(node->prod), p);
	
	if (node) {
		if (list->head == NULL) {
			// Cabeça não inicializada
			list->head = node;
		}
		
		if (list->tail == NULL) {
			// Lista vazia
			list->tail = node;
		}
		else {
			// Há outros elementos
			node->prev = list->tail;
			list->tail->next = node;
			list->tail = node;
		}
		list->size++;
		retval = node->prod.code;
	}
	
	return retval;
}

int pop_back(list_t* list, product_t* p) {
	node_t*		tmp		= list->tail;
	int			retval	= 0;
	
	if (list->size) {
		_set_prod(p, &(tmp->prod));
		
		list->size--;
		retval = 1;
		
		if (tmp == list->head) {
			list->tail = list->head = NULL;
			list->size = 0;
		}
		else {
			list->tail = list->tail->prev;
			list->tail->next = NULL;
		}
		
		_del_node(tmp);
	}
	
	return retval;
}
int pop_front(list_t* list, product_t* p) {
	node_t*		tmp		= list->head;
	int			retval	= 0;
	
	if (list->size) {
		_set_prod(p, &(tmp->prod));
		
		list->size--;
		retval = 1;
		
		if (tmp == list->tail) {
			list->head = list->tail = NULL;
			list->size = 0;
		}
		else {
			list->head = list->head->next;
			list->head->prev = NULL;
		}
		
		_del_node(tmp);
	}
	
	return retval;
}

void print_list(const list_t* list) {
	printf("Head: %10p\n", list->head);
	printf("Tail: %10p\n", list->tail);
	printf("Size: %10d\n", list->size);
	
	node_t* it = begin(list);
	
	if (it) {
		printf("Data: \n\n");
	}
	
	for (it = begin(list); it != end(list); it = it->next) {
		print_node(it);
	}
}

void print_node(const node_t* node) {
	printf("%10p <- %10p -> %10p: {%10d, %20s}\n",
				node->prev, node, node->next,
				node->prod.code,
				node->prod.name);
}

node_t*	begin(const list_t* list) {
	return list->head;
}

node_t* end(const list_t* list) {
	return NULL;
}


node_t*	_new_node() {
	node_t* node = (node_t*)malloc(sizeof(node_t));
	
	if (node != NULL) {
		node->next = node->prev = NULL;
	}
	
	return node;
}

void _del_node(node_t* node) {
	free(node);
}

void _set_prod(product_t* dest, const product_t* orig) {
	dest->code = orig->code;
	strncpy(dest->name, orig->name, MAX_STR);
}
