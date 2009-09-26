/*
 * double_linked_list.h
 *
 *  Created on: Sep 19, 2009
 *      Author: blabos
 */

#ifndef DOUBLE_LINKED_LIST_H_
#define DOUBLE_LINKED_LIST_H_


struct node_st {
	void* data;
	struct node_st* next;
	struct node_st* prev;
};

typedef struct node_st node_t;

typedef struct {
	node_t* head;
	node_t* tail;
} list_t;


list_t* new_list();
void del_list(list_t* list);

void print_list(list_t* list);

node_t* push(list_t* list, void* value);
void pop(list_t* list);

#endif /* DOUBLE_LINKED_LIST_H_ */
