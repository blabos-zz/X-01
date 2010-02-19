/*
 * exe-10.cpp
 *
 *  Created on: 01/06/2009
 *      Author: wesley
 *      
 *  10. Descreva, em detalhes, a implementação de uma biblioteca. Dê um
 *  exemplo, construindo uma biblioteca com duas funções matemáticas para
 *  vetores: soma e multiplicação.
 *  
 *  Uma biblioteca é um conjunto de declarações, subrotinas e componentes que
 *  são utilizados como peças de software.
 *  
 *  Em C++, uma biblioteca é implementada por um conjunto de arquivos de
 *  declaração de símbolos e por um outro conjunto de arquivos
 *  de implementação dos componentes declarados. Embora ambos os arquivos
 *  contenham código fonte, normalmente os arquivos de declaração são chamados
 *  de headers e os de implementação de sources.
 *  
 *  Os arquivos de headers possuem todos os símbolos que o compilador precisa
 *  para compilar uma aplicação que utilize uma dada biblioteca.
 *  
 *  Já os sources possuem todos so comandos que serão transformados em código
 *  objeto para posteriormente serem linkados com com o restante da aplicação.
 *  
 *  Se a aplicação for linkada estaticamente, ela incorpora todo o código da
 *  biblioteca em seu executával. Já se ela for linkada dinamicamente,
 *  precisará ter acesso aos binários da biblioteca.
 *  
 *  Os headers são necessários somente em tempo de compilação.
 *  
 *  Segue abaixo o exemplo de implementação pedido, assim como nos outros
 *  exercícios seguem exemplos mais práticos.
 */
#include <iostream>

#include "../include/vector.h"

using namespace std;

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	
	vector_t v1, v2, res;
	float prod;
	
	cout << "V1" << endl;
	read_vector(v1);
	
	cout << "V2" << endl;
	read_vector(v2);
	
	sum(res, v1, v2);
	prod = dot(v1,v2);
	
	show_vector(v1);
	show_vector(v2);
	
	cout << "Resultado da soma:" << endl;
	show_vector(res);
	
	cout << "Resultado do produto:" << endl;
	cout << prod << endl;
	
	return 0;
}
