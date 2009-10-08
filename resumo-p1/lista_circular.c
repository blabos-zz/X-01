/*
 * lista_circular.c
 *
 *  Created on: Oct 8, 2009
 *      Author: wesley
 */
#include <stdlib.h>
#include <stdio.h>

struct st_node {
	int num;
	struct st_node* next;
	struct st_node* prev;
};

typedef struct st_node node_t;

typedef struct {
	node_t* ini;
	node_t* end;
} list_t;


void init(list_t* list) {
	list->ini = list->end = NULL;
}

void print(list_t* list) {
	node_t* i;
	
	printf("List:\n");
	printf("Ini: %10p\n", list->ini);
	printf("End: %10p\n", list->end);
	
	if (list->ini != NULL) {
		int count = 5;
		i = list->ini;
		do {
			printf("%10p <- %10p -> %10p : %d\n", i->prev, i, i->next, i->num);
			i = i->next;
		} while ((i) && (i->next != list->ini->next));
	}
	else {
		printf("No elements\n");
	}
	
	printf("\n");
}

void insert_item(list_t* list, int num) {
	node_t* node = (node_t*)malloc(sizeof(node_t));
	
	node->num = num;
	node->next = node->prev = node;
	
	if (list->ini == NULL) {
		// Lista vazia
		list->ini = list->end = node;
	}
	else {
		list->end->next = node;
		list->ini->prev = node;
		
		node->prev = list->end;
		node->next = list->ini;
		
		list->end = node;
	}
}

void remove_item(list_t* list) {
	if (list->ini != NULL) {
		node_t* temp = list->ini;
		
		if (list->ini == list->ini->next) {
			// Só sobrou eu
			list->ini = list->end = NULL;
		}
		else {
			// Dois ou mais elementos
			list->ini = list->ini->next;
			list->ini->prev = list->end;
			list->end->next = list->ini;
		}
		
		free(temp);
	}
	else {
		printf("Não posso remover. Lista vazia\n");
	}
}

int main(void) {
	list_t list;
	
	init(&list);
	
	print(&list);
	
	insert_item(&list, 10);
	print(&list);
	
	insert_item(&list, 20);
	print(&list);
	
	insert_item(&list, 30);
	print(&list);
	
	insert_item(&list, 40);
	print(&list);
	
	insert_item(&list, 50);
	print(&list);
	
	remove_item(&list);
	print(&list);
	
	remove_item(&list);
	print(&list);
	
	remove_item(&list);
	print(&list);
	
	remove_item(&list);
	print(&list);
	
	remove_item(&list);
	print(&list);
	
	remove_item(&list);
	print(&list);
	
	return EXIT_SUCCESS;
}
