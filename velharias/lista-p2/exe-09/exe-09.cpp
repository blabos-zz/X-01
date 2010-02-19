/*
 * exe-09.cpp
 *
 *  Created on: 01/06/2009
 *      Author: wesley
 *      
 *  9. Dados dois strings (um contendo uma frase e outro contendo uma palavra),
 *  remove a palavra da string, sem deixar espaços em branco desnecessários.
 */
#include <iostream>

#include "../include/string.h"

using namespace std;

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	
	string_t phrase, backup;
	string_t word;
	
	cout << "Digite uma frase: ";
	cin.getline(phrase, STR_MAX_LEN);
	
	strcpy(backup, phrase);
	
	cout << "Digite um texto para apagar: ";
	cin.getline(word, STR_MAX_LEN);
	
	int pos = findstr(phrase, word);
	if (pos >= 0) {
		int wlen = strlen(word);
		int plen = strlen(phrase);
		int count = wlen + 1;
		
		if (pos == (plen - wlen)) pos--;
		
		erase(phrase, pos, count);
		
		cout << "Depois de apagar a palavra '" << word << "' da frase '"
			<< backup << "', obtemos '" << phrase << "'." << endl;
	}
	else {
		cout << "A palavra '" << word << "' não foi encontrada na frase '"
			<< phrase << "'." << endl;
	}
	
	return 0;
}
