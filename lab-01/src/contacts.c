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
 * Private functions.
 */
int _find_first_greater(const contacts_t* list, string_t name);
void _inflate(contacts_t* list, int pos);
void _deflate(contacts_t* list, int pos);


/**
 * Initializes a contact list. Sets _length and all positions of array
 * _contacts to zero bytes.
 * 
 * @param contatcts_t* Pointer to a list.
 */
void init(contacts_t* list) {
	memset(list, 0, sizeof(contacts_t));
}

/**
 * Prints a contact on a given position.
 * 
 * @param const contacts_t* A pointer to a list.
 * @param contacts_t* A given position.
 */
void print_one(const contacts_t* list, int position) {
	printf("Pos:      %02d\n", position);
	printf("Nome:     %s\n",   list->_contacts[position]._name);
	printf("Lugar:    %s\n",   list->_contacts[position]._place);
	printf("Tel:      %s\n\n", list->_contacts[position]._phone);
}

/**
 * Prints all contacts.
 * 
 * @param const contacts_t* A pointer to a list.
 */
void print_all(const contacts_t* list) {
	int i;
	
	for (i = 0; i < list->_length; i++) {
		print_one(list, i);
	}
}

/**
 * Reads one contact from the standard input.
 * 
 * @param contact_t* A pointer to return a contact.
 */
void read_one(contact_t* contact) {
	setbuf(stdin, 0);
	char* ret;			// Only to suppress warnings.
	
	printf("Nome:  ");
	ret = fgets(contact->_name,  MAX_STR_SIZE, stdin);
	chomp(contact->_name);
	
	printf("Lugar: ");
	ret = fgets(contact->_place, MAX_STR_SIZE, stdin);
	chomp(contact->_place);
	
	printf("Tel:   ");
	ret = fgets(contact->_phone, MAX_STR_SIZE, stdin);
	chomp(contact->_phone);
}


/**
 * Inserts a contact into a list.
 * 
 * All contacts will be placed in alphabetical order.
 * 
 * @param contacts_t* A poiter to a list.
 * @param contact_t  A contact.
 * 
 * @return int The element's position into the list or -1 if cannot insert.
 */
int insert(contacts_t* list, contact_t contact) {
	int pos = -1;
	
	if (list->_length < MAX_LIST_SIZE) {
		pos = _find_first_greater(list, contact._name);
		
		_inflate(list, pos);
		
		list->_contacts[pos] = contact;
	}
	
	return pos;
}

/**
 * Finds a contact by name.
 * 
 * @param const contacts_t* A pointer to a list.
 * @param string_t A name to find.
 * @param int Initial element's position within the list.
 * @param int Final element's position within the list.
 * 
 * @return int The element's position or -1 if cannot find.
 */
int find_by_name(const contacts_t* list, string_t name, int ini, int end) {
	int cmp, half;
	if (ini > end) return -1;
	
	half = (ini + end) / 2;
	cmp = strcmp(list->_contacts[half]._name, name);
	
	if (cmp == 0) {
		return half;
	}
	else if (cmp < 0) {
		return find_by_name(list, name, half + 1, end);
	}
	else {
		return find_by_name(list, name, ini, half - 1);
	}
}

/**
 * Finds a contact by place.
 * 
 * @param const contacts_t* A pointer to a list.
 * @param string_t A place to find.
 * @param int Initial element's position within the list.
 * @param int Final element's position within the list.
 * 
 * @return int The element's position or -1 if cannot find.
 */
int find_by_place(const contacts_t* list, string_t place, int ini, int end) {
	int cmp, half;
	if (ini > end) return -1;
	
	half = (ini + end) / 2;
	cmp = strcmp(list->_contacts[half]._place, place);
	
	if (cmp == 0) {
		return half;
	}
	else if (cmp < 0) {
		return find_by_place(list, place, half + 1, end);
	}
	else {
		return find_by_place(list, place, ini, half - 1);
	}
}

/**
 * Deletes a contact from a list.
 * 
 * @param contacts_t* A pointer to a list.
 * @param string_t The name of contact to delete.
 * 
 * @return int The element's position or -1 if cannot delete.
 */
int delete(contacts_t* list, string_t name) {
	int pos;
	pos = find_by_name(list, name, 0, list->_length);
	
	_deflate(list, pos);
	
	return pos;
}

/**
 * Find the first element whose it name is alphabetically greater than the
 * given name.
 * 
 * @param const contacts_t* A pointer to a list.
 * @param string_t The given name.
 * 
 * @return int The element's position.
 */
int _find_first_greater(const contacts_t* list, string_t name ) {
	int index = 0;

	if (list->_length <= 0) {
		index = 0;
	}
	else {
		while ((index < list->_length)
				&& (strcmp(list->_contacts[index]._name, name) <= 0)) {
			index++;
		}
	}
	
	return index;
}

/**
 * Returns the count of items into the list.
 * 
 * @param const contacts_t* A pointer to a list.
 * 
 * @return int Count of elements.
 */
int count(const contacts_t* list) {
	return list->_length;
}

/**
 * Returns the number of elements not used yet.
 * 
 * @param const contacts_t* A pointer to a list.
 * 
 * @return int The number of elements not used yet.
 */
int elements_left(const contacts_t* list) {
	return MAX_LIST_SIZE - list->_length;
}

/**
 * Shift ahead all elements since the given position.
 * 
 * @param contacts_t* A pointer to a list.
 * @param int The given position.
 */
void _inflate(contacts_t* list, int pos) {
	int i;
	
	if ((pos >= 0) && (pos <= list->_length)) {
		if (list->_length > 0) {
			for (i = list->_length; i > pos; i--) {
				list->_contacts[i] = list->_contacts[i - 1];
			}
		}
		
		list->_length++;
	}
}

/**
 * Shift backwards all elements after the given position.
 * 
 * @param contacts_t* A pointer to a list.
 * @param int The given position.
 */
void _deflate(contacts_t* list, int pos) {
	int i;
	
	if ((pos >= 0) && (pos < list->_length)) {
		list->_length--;
		
		for (i = pos; i < list->_length; i++) {
			list->_contacts[i] = list->_contacts[i+1];
		}
	}
}

/**
 * Removes the last character of a given string.
 * 
 * @param char* A pointer of the first character of the string.
 */
void chomp(char* str) {
	str[strlen(str) - 1] = '\0';
}
