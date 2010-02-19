/*
 * list.h
 *
 *  Created on: 01/06/2009
 *      Author: wesley
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>

using namespace std;

const int MAX_LIST_SIZE = 20;
typedef struct {
	int num;
} element_t;

typedef struct {
	element_t data[MAX_LIST_SIZE];
	int length;
	int first;
	int last;
} list_t;

void clear_list(list_t& l);
void read_list(list_t& l);
void show_list(const list_t& l);
bool insert(list_t& l, int pos, const element_t& e);
bool remove(list_t& l, int pos);

#endif /* LIST_H_ */
