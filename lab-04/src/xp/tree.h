/*
 * tree.h
 *
 *  Created on: 19/11/2009
 *      Author: blabos
 */

#ifndef TREE_H_
#define TREE_H_


#include "data.h"


tnode_t*    new_tree();
void        del_tree(tnode_t**);

tnode_t*    new_tnode(char);
tnode_t*    make_sub_tree(tnode_t*, tnode_t*, tnode_t*);

tnode_t*    make_parse_tree(char*);

void        print_in(tnode_t*);


#endif /* TREE_H_ */
