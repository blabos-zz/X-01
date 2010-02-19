/*
 * list.cpp
 *
 *  Created on: 01/06/2009
 *      Author: wesley
 */
#include "list.h"

/**
 * Declaração de funções auxiliares visíveis somente dentro deste arquivo.
 */
void _clear_element(element_t& e);
void _read_element(element_t& e);
void _show_element(const element_t& e);
void _shift_up(list_t& l, int from, int to);
void _shift_down(list_t& l, int from, int to);

/**
 * Inicializa a lista linear.
 * 
 * @param list_t& Referência para a lista a ser inicializada.
 */
void clear_list(list_t& l) {
	for (int i = 0; i < MAX_LIST_SIZE; i++) {
		_clear_element(l.data[i]);
	}
	
	l.first = l.last = l.length = 0;
}

/**
 * Lê elementos da entrada padrão.
 * 
 * @param list_t& Referência para a lsita a ser lida.
 */
void read_list(list_t& l) {
	for (int i = 0; i < MAX_LIST_SIZE; i++) {
		cout << "Insira o elemento " << i << endl;
		_read_element(l.data[i]);
	}
}

/**
 * Mostra os elementos da lista.
 * 
 * @param const list_t& Referência constante para a lista.
 */
void show_list(const list_t& l) {
	
	if (l.length <= 0) return;
	
	cout << "Mostrando lista, da posição " << l.first
		<< " até a " << l.last << endl;
	for (int i = l.first; i <= l.last; i++) {
		_show_element(l.data[i]);
	}
	cout << endl;
}

/**
 * Tenta iserir um elemento e na posição pos da lista l. Checa se a posição é
 * válida antes de tentar inserir. Tenta deslcar o menor número possível de
 * elementos para acomodar o novo elemento.
 * 
 * @param list_t& l Referência para a lista onse o elemento será inserido.
 * @param int Posição onde o elemento será inserido.
 * @param const element_t& Referência constante para o elemento.
 * 
 * @return bool Retorna true se conseguiu inserir ou false caso contrário.
 */
bool insert(list_t& l, int pos, const element_t& e) {
	bool retval = true;
	
	if ((pos >= 0) && (pos < MAX_LIST_SIZE) && (l.length < MAX_LIST_SIZE)) {
		
		if (l.length == 0) {
			/**
			 * Se o comprimento da lista é zero, então pode inserir em
			 * qualquer lugar dentro dos limites válidos.
			 */
			l.data[pos] = e;
			l.first = l.last = pos;
			l.length++;
		} else {
			/** Calcula onde fica o ponto médio da lista. */
			int middle = (l.first + l.last) / 2;
			
			if (pos <= middle) {
				// A posição é abaixo do meio.
				if (l.first > 0) {
					// Existe espaço vago abaixo do primeiro elemento.
					if (pos < l.first) {
						/** Se quero inserir abaixo do primeiro, então insiro
						 * logo antes para não deixar buraco.
						 */
						l.data[--l.first] = e;
						l.length++;
					}
					else {
						/**
						 * Se quero inserir entre o meio e o primeiro elemento,
						 * como sei que há espaço vago abaixo, desloco para
						 * baixo todos os elementos abaixo da posição que
						 * quero e insiro.
						 */
						_shift_down(l, l.first, pos);
						l.data[pos] = e;
						l.first--;
						l.length++;
					}
				}
				else {
					/**
					 * Não resta espaço vago abaixo do primeiro elemento, só
					 * resta deslocar os elementos daqui para cima.
					 */
					_shift_up(l, pos, l.last);
					l.data[pos] = e;
					l.last++;
					l.length++;
				}
			}
			else {
				// A posição é acima do meio.
				if (l.last < (MAX_LIST_SIZE - 1)) {
					// Existe espaço vago acima do último elemento.
					if (pos > l.last) {
						/**
						 * Se a posição é acima do último elemento, insiro
						 * logo acima dele para não deixar buracos.
						 */
						l.data[++l.last] = e;
						l.length++;
					}
					else {
						/**
						 * Se quero inserir entre o meio e o último elemento,
						 * como sei que há espaço vago acima, desloco para
						 * cima todos os elementos daqui até o último. 
						 */
						_shift_up(l, pos, l.last);
						l.data[pos] = e;
						l.last++;
						l.length++;
					}
				}
				else {
					/**
					 * Não existe espaço vago acima, só resta deslocar para
					 * baixo todos os elementos daqui para baixo..
					 */
					_shift_down(l, l.first, pos);
					l.data[pos] = e;
					l.first--;
					l.length++;
				}
			}
		}
	}
	else {
		retval = false;
	}
	
	return retval;
}

/**
 * Tenta remover o elemento na posição pos da lista l.
 * 
 * @param list_t& A lista de onde remover o elemento.
 * @param int A posição do elemento.
 * 
 * @return bool Retorna true se conseguiu remover ou false caso contrário.
 */
bool remove(list_t& l, int pos) {
	bool retval = true;
	
	if ((pos >= l.first) && (pos <= l.last) && (l.length > 0)) {
		int middle = (l.first + l.last) / 2;
		
		if (pos <= middle) {
			_shift_up(l, l.first, pos - 1);
			l.first++;
			l.length--;
		}
		else {
			_shift_down(l, pos + 1, l.last);
			l.last--;
			l.length--;
		}
	}
	else {
		retval = false;
	}
	
	return retval;
}


/**
 * Inicializa um elemento da lista.
 * 
 * @param element_t& O elemento a ser inicializado.
 */
void _clear_element(element_t& e) {
	e.num = 0;
}

/**
 * Lê da entrada padrão um elemento da lista.
 * 
 * @param element_t& O elemento onde o valor será armazenado.
 */
void _read_element(element_t& e) {
	cout << "Insira o número: ";
	cin >> e.num;
}

/**
 * Mostra na saída padrão um elemento da lista.
 * 
 * @param element_t& O elemento a ser mostrado.
 */
void _show_element(const element_t& e) {
	cout << e.num << " ";
}

/**
 * Desloca todos os elementos uma posição acima, desde from até to na lista l.
 * 
 * @param list_t& A lista.
 * @param int A posição mais baixa.
 * @param int A posição mais alta.
 */
void _shift_up(list_t& l, int from, int to) {
	for (int i = to; i >= from; i--) {
		l.data[i + 1] = l.data[i];
	}
}

/**
 * Desloca todos os elementos uma posição para baixo, de from a to na lista l.
 */
void _shift_down(list_t& l, int from, int to) {
	for (int i = from; i <= to; i++) {
		l.data[i - 1] = l.data[i];
	}
}
