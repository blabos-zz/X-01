/*
 * exe-08.cpp
 *
 *  Created on: 01/06/2009
 *      Author: wesley
 *      
 *  8. Dados dois strings (um contendo uma frase e outro contendo uma palavra),
 *  determine o número de vezes que a palavra dada ocorre na frase.
 */
#include <iostream>

#include "../include/string.h"

using namespace std;

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	
	string_t phrase;
	string_t word;
	
	cout << "Digite uma frase: ";
	cin.getline(phrase, STR_MAX_LEN);
	
	cout << "Digite um texto para procurar: ";
	cin.getline(word, STR_MAX_LEN);
	
	int pos = 0;
	char* ptr = phrase;
	int count = 0;
	while (ptr && pos >= 0) {
		pos = findstr(ptr, word);
		if (pos >= 0) {
			count++;
			ptr += pos + 1;
		}
	}
	
	cout << "A string '" << word << "' aparece " << count
		<< " veze(s) na string '" << phrase << "'." << endl;
	
	return 0;
}
