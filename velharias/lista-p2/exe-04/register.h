/*
 * register.h
 *
 *  Created on: 01/06/2009
 *      Author: wesley
 */

#ifndef REGISTER_H_
#define REGISTER_H_

#include <iostream>

#include "../include/string.h"

using namespace std;

typedef struct {
	string_t nome;
	string_t endereco;
	string_t telefone;
	int idade;
} register_t;

void show_register(const register_t& r);
void clear_register(register_t& r);


#endif /* REGISTER_H_ */
