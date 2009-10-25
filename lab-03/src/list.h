/*
 * list.h
 *
 *  Created on: Oct 24, 2009
 *      Author: wesley
 */

#ifndef LIST_H_
#define LIST_H_


#define MAX_STR 20

typedef char string_t[MAX_STR];

struct node_st {
	int				code;
	string_t		name;
	struct node_st*	next;
	struct node_st*	prev;
};

typedef struct node_st node_t;

typedef struct {
	node_t*			head;
	node_t*			tail;
	int				size;
} list_t;


list_t* new_list();
void	del_list(list_t*);

int		push_front(list_t*, node_t*);
int		push_back(list_t*, node_t*);

int		pop_front(list_t*, node_t*);
int		pop_back(list_t*, node_t*);

void	print_list(const list_t*);
void	print_node(const node_t*);

node_t*	begin(const list_t*);
node_t* end(const list_t*);


#endif /* LIST_H_ */
