/*
 * orders.c
 *
 *  Created on: Sep 19, 2009
 *      Author: blabos
 */
#include "orders.h"

#include <stdlib.h>
#include <stdio.h>

unsigned*   _internal_code();


order_t*	_new_order(const order_t* order);
void		_del_order(order_t* order);
void		_clear(order_list_t* list);


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
	_clear(list);
	
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

/**
 * Procura um pedido a partir do seu código.
 * 
 * @param const order_list_t* Um ponteiro para a lista.
 * @param unsigned O código a ser procurado.
 * 
 * @return order_t* Um ponteiro para o pedido encontrado ou NULL se não
 * encontrou o pedido.
 */
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
 * Retorna Um ponteiro para o elemento seguinte ao último elemento da lista,
 * usualmente u mponteiro nulo.
 * 
 * @param const order_list_t* Um ponteiro para a lista de pedidos.
 * 
 * @return order_t* O ponteiro para o elemento após o último.
 */
order_t* orders_end(const order_list_t* list) {
	return list->tail ? list->tail->next : NULL;
}

/**
 * Retorna o código do pedido atual.
 * 
 * @return unsigned O Código atual.
 */
unsigned get_curr_code() {
	return *(_internal_code());
}

/**
 * Seta o último código utilizado no sub-sistema prevedor de códigos.
 * 
 * @param unsigned O código atual.
 */
void set_last_code(unsigned code) {
	(*(_internal_code())) = code;
}

/**
 * Retorna o próximo código de pedido.
 * 
 * @return unsigned O próximo código disponível.
 */
unsigned get_next_code() {
    return ++(*_internal_code());
}

/**
 * Grava os dados do sistema em um arquivo.
 * 
 * @param const order_list_t* Um ponteiro para a lista.
 * @param char* O nome do arquivo.
 */
void save(const order_list_t* list, char* filename) {
	FILE* fp;
	
	if ((fp = fopen(filename, "wb")) != NULL) {
		
		/**
		 * Gravando estoque.
		 */
		{
			int value = 0;
			
			value = stock_bean();
			fwrite((const void*)&(value), sizeof(int), 1, fp);
			
			value = stock_corn();
			fwrite((const void*)&(value), sizeof(int), 1, fp);
			
			value = stock_milk();
			fwrite((const void*)&(value), sizeof(int), 1, fp);
			
			value = stock_rice();
			fwrite((const void*)&(value), sizeof(int), 1, fp);
			
			value = stock_wine();
			fwrite((const void*)&(value), sizeof(int), 1, fp);
			
			printf("Salvando estoque.\n");
			stock_show();
		}
		
		/**
		 * Gravando dados da lista.
		 */
		{
			unsigned value;
			order_t* it;
			
			value = get_curr_code();
			fwrite((const void*)&(value), sizeof(unsigned), 1, fp);
			
			printf("Último código de pedido: %03d.\n", get_curr_code());
			
			for (it = list->tail; it && (it != list->head->prev);
					it = it->prev) {
				fwrite((const void*)&(it->data), sizeof(order_item_t), 1, fp);
				fwrite((const void*)&(it->code), sizeof(unsigned), 1, fp);
			}
			
			printf("\nCarregando %03d pedidos.\n", list->size);
		}
		
		fclose(fp);
	}
}

/**
 * Recupera os dados do sistema de um arquivo.
 * 
 * @param order_list_t* Um ponteiro para a lista.
 * @param char* O nome do arquivo.
 */
void load(order_list_t* list, char* filename) {
	FILE* fp;
	
	int value = 0;
	
	if ((fp = fopen(filename, "rb")) != NULL) {
		
		/**
		 * Carregando estoque.
		 */
		{
			int bean = 0;
			int corn = 0;
			int milk = 0;
			int rice = 0;
			int wine = 0;
			
			fread(&bean, sizeof(int), 1, fp);
			fread(&corn, sizeof(int), 1, fp);
			fread(&milk, sizeof(int), 1, fp);
			fread(&rice, sizeof(int), 1, fp);
			fread(&wine, sizeof(int), 1, fp);
			
			stock_load(bean, corn, milk, rice, wine);
			printf("Carregando estoque.\n");
			stock_show();
		}
		
		/**
		 * Carregando dados da lista.
		 */
		{
			unsigned last_code, item_code, count;
			order_t order;
			
			last_code = 0;
			fread(&last_code, sizeof(unsigned), 1, fp);
			
			_clear(list);
			
			count = 0;
			while (fread(&(order.data), sizeof(order_item_t), 1, fp)) {
				if (!fread(&(item_code), sizeof(unsigned), 1, fp)) {
					item_code = 0;
				}
				
				++count;
				order.code = item_code;
				request_order(list, order);
			}
			
			printf("\nCarregando %03d pedidos.\n", count);
			
			
			set_last_code(last_code);
			printf("Último código de pedido: %03d.\n", get_curr_code());
			
			printf("Dados carregados com sucesso.\n");
		}
		
		fclose(fp);
	}
}

/****************************************************************************/
/****************************************************************************/

/**
 * Sub-sistema de códigos de pedidos.
 * Mantém um proto-singleton para fornecer os códigos de pedidos.
 * 
 * @return unsigned* Um ponteiro para o sub-sistema interno de códigos.
 */
unsigned* _internal_code() {
    static unsigned _code = 0;
    
    return &_code;
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
	
	for (it = list->tail; it && (it != list->head->prev); it = it->prev) {
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

/**
 * Esvazia a lista de pedidos. Não tenta atender pedidos, somente esvazia a
 * lista.
 * 
 * order_list_t* um ponteriro para lista.
 */
void _clear(order_list_t* list) {
	order_t* it;
	for (it = orders_begin(list); it != orders_end(list); it = it->next) {
		_remove_order(list, it);
	}
}
