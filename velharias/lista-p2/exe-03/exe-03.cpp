/*
 * exe-03.cpp
 *
 *  Created on: 23/05/2009
 *      Author: wesley
 *      
 *  3. Escreva a subrotina chamada “retira”, a qual recebe um vetor (e seu
 *  tamanho) e retira elementos duplicados neste vetor, deixando apenas uma
 *  ocorrência de cada valor. (Não esqueça de atualizar o valor do tamanho do
 *  vetor.) Admita que “retira” receberá um vetor que já se encontra ordenado.
 *  O procedimento “retira” não pode mudar a ordem dos números do vetor.
 */
#include <iostream>

#include "../include/vector.h"

using namespace std;

void retira(vector_t& v, int& len);
int _next_diferent(const vector_t& v, int len, int first, int next);

/**
 * Retira elementos repetidos do vetor.
 * 
 * @param vector_t& Referência para o vetor.
 * @param int& Referência para o comprimento do vetor.
 */
void retira(vector_t& v, int& len) {
	int first = 0;
	int next = 1;
	while(next < len){       
		next = _next_diferent(v, len, first, next);   
		if (next > 0) {  
			v[first + 1] = v[next];
			next++;
			first++;
		}
		else {
			next = len;
		}
	}
	
	len = first + 1;
}

/**
 * Procura o próximo elemento diferente do elemento vector[first], começando
 * a partir do elemento vector[next].
 * 
 * @param const vector_t& Referência constante para o vetor.
 * @param int O comprimento atual do vetor.
 * @param int Posição da primeira ocorrência do elemento.
 * @param int Posição a partir da qual começa a procurar.
 * 
 * @return int Posição do elemento procurado.
 */
int _next_diferent(const vector_t& v, int len, int first, int next) {
	int ret	= -1;
    int i	= next;
    
    while ((v[i] == v[first]) && (i < len)) {
          i++;
    }
    
    if (i < len) ret = i;
    
    return ret;
}

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	
	vector_t v;
	int length = VEC_LEN;
	
	read_vector(v);
	
	cout << "Depois de retira" << endl;
	show_vector(v, length);
	
	retira(v, length);
	
	cout << "Depois de retira" << endl;
	show_vector(v, length);
	
	return 0;
}
