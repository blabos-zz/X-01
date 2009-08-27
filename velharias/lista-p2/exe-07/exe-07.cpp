/*
 * exe-08.cpp
 *
 *  Created on: 23/05/2009
 *      Author: wesley
 *      
 *  7. Usando strings como vetores de caracteres, escreva um programa que
 *  inverta o nome completo de uma pessoa para a notação inglesa, isto é
 *  "Sobrenome, Nome".
 */
#include <iostream>

#include "../include/string.h"

using namespace std;

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	
	string_t plain_name, english_name, tmp;
	int last_space, len;
	
	cout << "Digite um nome com sobrenomes: ";
	cin.getline(plain_name, STR_MAX_LEN);
	
	last_space = rfind(plain_name, ' ');
	if (last_space >= 0) {
		len = strlen(plain_name);
		substr(english_name, plain_name, last_space + 1, len - last_space);
		strcat(english_name, ", ");
		substr(tmp, plain_name, 0, last_space);
		strcat(english_name, tmp);
		
		cout << "Nome em notação inglesa:" << endl;
		cout << "[" << english_name << "]" << endl;
	}
	else {
		cout << "Você precisa digitar pelo menos duas palavras." << endl;
	}
	
	return 0;
}
