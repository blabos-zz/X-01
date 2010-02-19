/*
 * contacts.h
 *
 *  Created on: Aug 27, 2009
 *      Author: wesley
 */

#ifndef CONTACTS_H_
#define CONTACTS_H_


#define MAX_LIST_SIZE	10
#define MAX_STR_SIZE	40

typedef char string_t[MAX_STR_SIZE];

typedef struct {
	string_t 	_name;
	string_t 	_phone;
	string_t 	_place;
} contact_t;

typedef struct {
	int			_length;
	contact_t	_contacts[MAX_LIST_SIZE];
} contacts_t;


void init(contacts_t* list);
void print_one(const contacts_t* list, int position);
void print_all(const contacts_t* list);

void read_one(contact_t* contact);

int insert(contacts_t* list, contact_t contact);
int find_by_name(const contacts_t* list, string_t name, int ini, int end);
int find_by_place(const contacts_t* list, string_t place, int ini, int end);
int delete(contacts_t* list, string_t name);

int count(const contacts_t* list);
int elements_left(const contacts_t* list);

void chomp(char* str);


#endif /* CONTACTS_H_ */
