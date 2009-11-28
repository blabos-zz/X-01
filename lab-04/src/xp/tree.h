/*
 * tree.h
 *
 *  Created on: 19/11/2009
 *      Author: blabos
 */

#ifndef TREE_H_
#define TREE_H_


struct node_st {
    char            key;
    struct node_st* left;
    struct node_st* right;
};

typedef struct node_st node_t;


node_t*     new_tree();
void        del_tree(node_t**);

node_t*     new_node(char);

node_t*     ins_node(node_t**, int);
void        del_node(node_t**, int);

node_t*     max_node(node_t*);
node_t*     min_node(node_t*);

node_t*     find_node(node_t*, int);
void        find_parent(node_t*, int, node_t**, node_t**);

void        print_in(node_t*);
void        print_pre(node_t*);
void        print_pos(node_t*);

int         count_nodes(node_t*);
int         count_leaves(node_t*);


#endif /* TREE_H_ */
