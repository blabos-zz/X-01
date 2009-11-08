/*
 * list.h
 *
 *  Created on: 08/11/2009
 *      Author: blabos
 */

#ifndef LIST_H_
#define LIST_H_

struct node_st {
	int				data;
	struct node_st*	next;
	struct node_st*	prev;
};

typedef struct node_st node_t;

typedef struct {
	node_t*			nil;
} list_t;


list_t*		new_list();
void		del_list(list_t*);
void		print_list(list_t*);

node_t*		head(list_t*);
node_t*		tail(list_t*);

node_t*		find(list_t*, int);
node_t*		insert(list_t*, int);
void		delete(list_t*, node_t*);


#endif /* LIST_H_ */
