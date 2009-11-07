/*
 * stock.h
 *
 *  Created on: Oct 29, 2009
 *      Author: wesley
 */

#ifndef STOCK_H_
#define STOCK_H_

#define MIN_WAKE	5
#define MAX_WAKE	10

#define MAX_PAN		10

#define TV			101
#define MO			102
#define PA			103

#define TYPE_OFFSET	1000

#include "list.h"

typedef list_t queue_t;
typedef list_t stack_t;

typedef struct {
	stack_t*	tv;
	stack_t*	mo;
	stack_t*	pa;
} stock_t;


void			init_stock();
void			view_stock();
void			view_wake();

void			reload_wake();
void			reload_stock();

node_t*			wk_begin();
node_t*			wk_end();
node_t*			tv_begin();
node_t*			tv_end();
node_t*			mo_begin();
node_t*			mo_end();
node_t*			pa_begin();
node_t*			pa_end();

int				wk_size();
int				tv_size();
int				mo_size();
int				pa_size();

int				attend_order(int, product_t*);


#endif /* STOCK_H_ */
