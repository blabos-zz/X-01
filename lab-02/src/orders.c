/*
 * orders.c
 *
 *  Created on: Sep 19, 2009
 *      Author: blabos
 */
#include "orders.h"

#include <stdlib.h>
#include <stdio.h>


order_t*	_new_order(const order_t* order);
void		_del_order(order_t* order);

unsigned*   _internal_code();
unsigned    _next_code();

void		_remove_order(order_list_t* list, order_t* order);
order_t*	_find_attendable_order(order_list_t* list);
int			_can_attend(const order_t* order);


/**
 * Cria uma nova lista de pedidos.
 * 
 * @return order_list_t* Um ponteiro para a nova lista de pedidos.
 */
order_list_t* new_order_list() {
	order_list_t* list = (order_list_t*)malloc(sizeof(order_list_t));
	
	list->head = list->tail = (void*)(list->size = 0);
	
	return list;
}

/**
 * Destrói uma lista de pedidos. Primeiro remove todos os elementos restantes,
 * depois libera a memória ocupada pala própria lista.
 * 
 * @param order_list_t* Um ponteiro para a lista a ser destruída.
 */
void del_order_list(order_list_t* list) {
	order_t* it;
	for (it = orders_begin(list); it != orders_end(list); it = it->next) {
		_remove_order(list, it);
	}
	
	free(list);
}

/**
 * Imprime a lista de pedidos em formato de debug.
 * 
 * @param const order_list_t* Um ponteiro para a lista de pedidos.
 */
void print_order_list(const order_list_t* list) {
	printf("Head: %10p\n", list->head);
	printf("Tail: %10p\n", list->tail);
	printf("Size: %10d\n", list->size);
	
	order_t* it = orders_begin(list);
	
	if (it) {
		printf("Data: \n\n");
	}
	
	for (it = orders_begin(list); it != orders_end(list); it = it->next) {
		print_order(it);
	}
}

/**
 * Armazena um pedido com uma dada quantidade de itens na fila de pedidos.
 * 
 * @param order_list_t* Um ponteiro para a lista de pedidos.
 * @param order_t O pedido a ser enfileirado.
 * 
 * @return int 1 se conseguiu inserir com sucesso ou zero se falhou.
 */
int request_order(order_list_t* list, order_t order) {
    int retval = 0;
    
	order_t* node = _new_order(&order);
	
	if (node) {
		if (list->tail == NULL) {
			// Cauda não inicializada
			list->tail = node;
		}
		
		if (list->head == NULL) {
			// Lista vazia
			list->head = node;
		}
		else {
			// Há outros elementos
			node->next = list->head;
			list->head->prev = node;
			list->head = node;
		}
		list->size++;
		retval = node->code;
	}
	
	return retval;
}

/**
 * Tenta atender a um pedido.
 * 
 * @param order_list_t* Um ponteiro para a lista de pedidos.
 * @param order_t* Um ponteiro para retornar o pedido atendido, se aplicável.
 * 
 * @return int 1 se conseguiu atender ou 0 caso contrário.
 */
int attend_order(order_list_t* list, order_t* order) {
	int retval = 0;
	order_t* node;
	
	if ((node = _find_attendable_order(list)) != NULL) {
		stock_request_bean(node->data.bean);
		stock_request_corn(node->data.corn);
		stock_request_milk(node->data.milk);
		stock_request_rice(node->data.rice);
		stock_request_wine(node->data.wine);
		
		*order = *node;
		order->next = order->prev = NULL;
		
		_remove_order(list, node);
		list->size--;
		
		retval = 1;
	}
	
	return retval;
}

order_t* find(const order_list_t* list, unsigned code) {
    order_t* it = NULL;
	for (it = orders_begin(list); it != orders_end(list); it = it->next) {
		if (it->code == code) break;
	}
	
	return it;
}

/**
 * Retorna o primeiro elemento da lista.
 * 
 * @param const order_list_t* Um ponteiro para a lista de pedidos.
 * 
 * @return order_t* Um ponteiro para o primeiro elemento. Caso a lista esteja
 * vazia, retorna NULL.
 */
order_t* orders_begin(const order_list_t* list) {
	return list->head;
}

/**
 * Retorna o último elemento da lista.
 * 
 * @param const order_list_t* Um ponteiro para a lista de pedidos.
 * 
 * @return order_t* Um ponteiro para o último elemento. Caso a lista esteja
 * vazia, retorna NULL.
 */
order_t* orders_end(const order_list_t* list) {
	return list->tail ? list->tail->next : NULL;
}

unsigned get_curr_code() {
	return *(_internal_code());
}
void set_curr_code(unsigned code) {
	(*(_internal_code())) = code;
}

/****************************************************************************/
/****************************************************************************/

/**
 *
 */
unsigned* _internal_code() {
    static unsigned _code = 0;
    
    return &_code;
}

/**
 *
 */
unsigned _next_code() {
    return ++(*_internal_code());
}

/**
 * Tenta criar uma cópia de um pedido.
 * 
 * @param const order_t* O pedido original.
 * 
 * @return order_t* Um ponteiro para a cópia. Em caso de falha este ponteiro
 * será nulo.
 */
order_t* _new_order(const order_t* order) {
	order_t* node = (order_t*)malloc(sizeof(order_t));
	
	if (node) {
		(*node) = (*order);
		node->code = _next_code();
		node->next = node->prev = NULL;
	}
	
	return node;
}

/**
 * Destrói um pedido.
 * 
 * @param order_t* Um ponteiro para o pedido a ser destruído.
 */
void _del_order(order_t* order) {
	free(order);
}

/**
 * Imprime um pedido em formato de debug.
 * 
 * @param const order_t* Um ponteiro para o pedido a ser impresso.
 */
void print_order(const order_t* order) {
	printf("%10p <- %10p -> %10p: {%3d, %3d, %3d, %3d, %3d}\n",
				order->prev, order, order->next,
				order->data.bean,
				order->data.corn,
				order->data.milk,
				order->data.rice,
				order->data.wine);
}

/**
 * Remove um pedido da lista de pedidos e desaloca a memória ocupada por ele.
 * 
 * @param order_list_t* Um ponteiro para a lista de pedidos.
 * @param order_t* Um ponteiro para o pedido a ser removido da lista.
 */
void _remove_order(order_list_t* list, order_t* order) {
	if (list->head == list->tail) {
		list->head = list->tail = NULL;
	}
	else if (order == list->head) {
		list->head = order->next;
		if (list->head) list->head->prev = NULL;
	}
	else if (order == list->tail) {
		list->tail = order->prev;
		if (list->tail) list->tail->next = NULL;
	}
	else {
		order->prev->next = order->next;
		order->next->prev = order->prev;
	}
	
	_del_order(order);
}

/**
 * Procura na lista de pedidos o primeiro pedido que puder ser atendido pelo
 * atual estoque.
 * 
 * @param order_list_t* Um ponteiro para a lista de pedidos.
 * 
 * @return order_t* Um ponteiro para o pedido a ser atendido, ou NULL caso
 * nenhum pedido possa ser atendido no momento.
 */
order_t* _find_attendable_order(order_list_t* list) {
	order_t* it;
	
	for (it = orders_begin(list); it != orders_end(list); it = it->next) {
		if (_can_attend(it)) {
			return it;
		}
	}
	
	return NULL;
}

/**
 * Checa se dado pedido pose ser atendido pelo estoque atual.
 * 
 * @param const order_t* Um ponteiro para o pedido.
 * 
 * @return int 1 se o pedido possa ser atendido ou 0 caso contrário.
 */
int _can_attend(const order_t* order) {
	return (stock_has_bean(order->data.bean) &&
			stock_has_corn(order->data.corn) &&
			stock_has_milk(order->data.milk) &&
			stock_has_rice(order->data.rice) &&
			stock_has_wine(order->data.wine));
}

