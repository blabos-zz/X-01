/*
 * list.h
 *
 *  Created on: 08/11/2009
 *      Author: blabos
 */

#ifndef LIST_H_
#define LIST_H_

#include "data.h"


list_t*     new_list();
void        del_list(list_t*);
void        print_list(list_t*);
void        print_lnode(lnode_t*);
void        print_tnode(tnode_t*);

lnode_t*    head(list_t*);
lnode_t*    tail(list_t*);

lnode_t*    find(list_t*, tnode_t*);
lnode_t*    insert(list_t*, tnode_t*);
void        delete(list_t*, lnode_t*);

tnode_t*    push(list_t*, tnode_t*);
tnode_t*    pop(list_t*);

int         has_oto(list_t*);
int         has_C(list_t*);


#endif /* LIST_H_ */
