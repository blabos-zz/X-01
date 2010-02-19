/*
 * list.h
 *
 *  Created on: 01/06/2009
 *      Author: wesley
 */

#ifndef LIST_H_
#define LIST_H_

#include "register.h"

const int LIST_LEN = 2;
typedef register_t student_list_t[LIST_LEN];

void show_list(const student_list_t& l);
void clear_list(student_list_t& l);

#endif /* LIST_H_ */
