/*
 * exe-05-06.cpp
 *
 *  Created on: 01/06/2009
 *      Author: wesley
 *      
 *  5. Refaça a remoção em uma lista linear: suponha que a parte relevante da
 *  lista l é l[ini..fim-1]; para remover v[k], puxe l[k+1..fim-1] para a
 *  esquerda ou empurre l[ini..k-1] para a direita, dependendo de qual das
 *  alternativas seja mais "rápida". Escreva uma função que remova de
 *  l[ini..fim-1] todas as ocorrências de um determinado valor dado como
 *  entrada.
 *  
 *  6. Refaça a inserção em uma lista linear: suponha que a parte relevante da
 *  lista l é l[ini..fim-1]; para inserir x entre l[k-1] e l[k] você tem duas
 *  opções: empurrar l[k..fim-1] para a direita ou puxar l[ini..k-1] para a
 *  esquerda; escolha a opção mais apropriada. Escreva uma função que insira
 *  x entre l[k] e l[k+1].
 */
#include <iostream>

#include "list.h"

using namespace std;

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	
	list_t l;
	element_t e;
	int n;
	bool ret;
	
	clear_list(l);
	
	cout << "Inserção" << endl;
	
	do {
		cout << "Digite separados por espaço, um inteiro a ser inserido e a "
			<< "posição desejada. As posições válidas vão de 0 a "
			<< MAX_LIST_SIZE << ". Uma posição inválida ou preenchimento "
			<< "completo da lista encerram a inserção." << endl;
		cin >> e.num >> n;
		ret = insert(l, n, e);
		show_list(l);
	} while(ret);
	
	cout << endl;
	
	cout << "Remoção" << endl;
	
	do {
		cout << "Digite a posição do elemento que você desejada remover. "
		<< "As posições válidas vão de " << l.first << " a "
			<< l.last << ". Uma posição inválida ou esvaziamento "
			<< "completo da lista encerram a remoção." << endl;
		cin >> n;
		ret = remove(l, n);
		show_list(l);
	} while(ret);
	
	return 0;
}
