/*
 * tree.h
 *
 *  Created on: 10/11/2009
 *      Author: blabos
 */

#ifndef TREE_H_
#define TREE_H_


struct node_st {
    int             data;
    struct node_st* parent;
    struct node_st* left;
    struct node_st* right;
};

typedef struct node_st node_t;


node_t* insert(node_t**, int);
void print_in(node_t*, int);
void print_pre(node_t*, int);
void print_pos(node_t*, int);


#endif /* TREE_H_ */
