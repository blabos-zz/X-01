/*
 * contacts.c
 *
 *  Created on: Aug 27, 2009
 *      Author: wesley
 */

#include "contacts.h"

#include <string.h>
#include <stdio.h>


/**
 * Initializes a contact list.
 */
void init(contacts_t* list) {
	memset(list, 0, sizeof(contacts_t));
}

/**
 * Prints a contact on a given position.
 */
void print_one(contacts_t* list, int position) {
	printf("Position: %02d\n", position);
	printf("Name:     %s\n",   list->_contacts[position]._name);
	printf("Phone:    %s\n",   list->_contacts[position]._phone);
	printf("Place:    %s\n\n", list->_contacts[position]._place);
}

/**
 * Prints all contacts.
 */
void print_all(contacts_t* list) {
	int i;
	
	for (i = 0; i < list->_length; i++) {
		print_one(list, i);
	}
}


/**
 * Inserts a contact into a list.
 */
int insert(contacts_t* list, string_t name, string_t phone, string_t place) {
	if (list->_length < MAX_LIST_SIZE) {
		strncpy(list->_contacts[list->_length]._name,  name,  MAX_STR_SIZE);
		strncpy(list->_contacts[list->_length]._phone, phone, MAX_STR_SIZE);
		strncpy(list->_contacts[list->_length]._place, place, MAX_STR_SIZE);
		list->_length++;
	}
	return list->_length;
}

/**
 * Finds a contact by name. Returns the position if found or -1 if not found.
 */
int find_by_name(contacts_t* list, string_t name) {
	int i, pos;
	
	for (i = 0; i < list->_length; i++) {
		if (strcmp(list->_contacts[i]._name, name) == 0) break;
	}
	
	pos = i < list->_length ? i : -1;
	
	return pos;
}

/**
 * Finds a contact by place. Returns the position if found or -1 if not found.
 */
int find_by_place(contacts_t* list, string_t place) {
	int i, pos;
	
	for (i = 0; i < list->_length; i++) {
		if (strcmp(list->_contacts[i]._place, place) == 0) break;
	}
	
	pos = i < list->_length ? i : -1;
	
	return pos;
}

/**
 * Removes a contact from a list.
 */
int delete(contacts_t* list, string_t name) {
	int i, pos;
	
	pos = find_by_name(list, name);
	
	if ((pos >= 0) && (pos < list->_length)) {
		for (i = pos; i < list->_length - 1; i++) {
			list->_contacts[i] = list->_contacts[i+1];
		}
		
		list->_length--;
	}
	
	return list->_length;
}
