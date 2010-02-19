/*
 * list.cpp
 *
 *  Created on: 01/06/2009
 *      Author: wesley
 */
#include "list.h"

/**
 * Mostra o conteúdo de uma lista linear.
 * 
 * @param const student_list_t& Referência conatante para a lista.
 */
void show_list(const student_list_t& l) {
	for (int i = 0; i < LIST_LEN; i++) {
		cout << "Elemento " << i << ":" << endl;
		show_register(l[i]);
		cout << endl;
	}
}

/**
 * Inicializa uma lista linear com LIST_LEN elementos.
 * 
 * @param student_list_t& Referência para a lista a ser inicializada.
 */
void clear_list(student_list_t& l) {
	for (int i = 0; i < LIST_LEN; i++) {
		clear_register(l[i]);
	}
}
