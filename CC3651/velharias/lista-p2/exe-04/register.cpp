/*
 * register.cpp
 *
 *  Created on: 01/06/2009
 *      Author: wesley
 */
#include "register.h"

/**
 * Mostra o conteúdo de determinado registro.
 * 
 * @param const register_t& Referência constante para o registro.
 */
void show_register(const register_t& r) {
	cout << "Nome:     [" << r.nome		<< "]" << endl;
	cout << "Endereço: [" << r.endereco << "]" << endl;
	cout << "Telefone: [" << r.telefone << "]" << endl;
	cout << "Idade:    [" << r.idade 	<< "]" << endl;
}

/**
 * Inicializa um registro com zero nos campos numéricos e espaços nos campos
 * literais.
 * 
 * @param register_t& Referência para o registro a ser inicializado.
 */
void clear_register(register_t& r) {
	strpad(r.nome);
	strpad(r.endereco);
	strpad(r.telefone);
	r.idade = 0;
}
