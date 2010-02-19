/*
 * exe-04.cpp
 *
 *  Created on: 23/05/2009
 *      Author: wesley
 *      
 *  4. Escreva as declarações em linguagem C e um procedimento para iniciar
 *  (preenchendo com zeros e brancos):
 *  a)      Uma matriz de nXm inteiros
 *  b)      Um registro R com Nome, Endereço, Telefone e Idade
 *  c)      Uma lista linear L com Nome, Endereço, Telefone e Idade, e 80
 *  		alunos
 *  d)      Um vetor de n números reais
 */
#include <iostream>

#include "../include/string.h"
#include "../include/vector.h"
#include "matrix.h"
#include "register.h"
#include "list.h"

using namespace std;

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	
	matrix_t		m;
	register_t		r;
	student_list_t	l;
	vector_t		v;
	
	cout << "Inicializando uma matriz " << MAX_ROW
		<< " X " << MAX_COL << endl;
	clear_matrix(m);
	show_matrix(m);
	cout << endl;
	
	cout << "Inicializando um registro" << endl;
	clear_register(r);
	show_register(r);
	cout << endl;
	
	cout << "Inicializando uma lista linear com "
		<< LIST_LEN << " elementos" << endl;
	clear_list(l);
	show_list(l);
	cout << endl;
	
	cout << "Inicializando um vetor de " << VEC_LEN
		<< " elementos" << endl;
	clear_vector(v);
	show_vector(v);
	cout << endl;
	
	return 0;
}
