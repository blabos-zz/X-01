/*
 * rbtree.h
 *
 *  Created on: 04/12/2009
 *      Author: wesley
 */

#ifndef RBTREE_H_
#define RBTREE_H_

struct node_st {
    int             key;
    char			color;
    struct node_st* parent;
    struct node_st* left;
    struct node_st* right;
};

typedef struct node_st node_t;


static node_t* nil;

node_t*   	new_tree();
void        del_tree(node_t*);

void        print_in(node_t*);


#endif /* RBTREE_H_ */
