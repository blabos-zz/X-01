/*
 * vector.cpp
 *
 *  Created on: 31/05/2009
 *      Author: wesley
 */
#include "../include/vector.h"

/**
 * Lê da entrada padrão um vetor de VEC_LEN elementos.
 * 
 * @param vector_t& Referência para o vetor a ser lido.
 */
void read_vector(vector_t& v) {
	cout << "Insira os " << VEC_LEN << " valores para o vetor:" << endl;
	for (int i = 0; i < VEC_LEN; i++) {
		cout << "v[" << i << "] = ";
		cin >> v[i];
	}
}

/**
 * Mostra na saída padrão os elementos de um vetor.
 * 
 * @param const vector_t& Referência constante para o vetor.
 * @param int Comprimento a ser mostrado. Opcional. Default VEC_LEN.
 */
void show_vector(const vector_t& v, int len) {
	cout << "Valores:" << endl;
	for (int i = 0; i < len; i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}

/**
 * Inicializa um vetor com zeros.
 * 
 * @param vector_t& Referência para o vetor a ser inicializado.
 * @param int Comprimento a ser mostrado. Opcional. Default VEC_LEN.
 */
void clear_vector(vector_t& v, int len) {
	for (int i = 0; i < len; i++) {
		v[i] = 0;
	}
}

/**
 * Soma dois vetores v1 e v2 e armazena o resultado em res.
 * 
 * @param vector_t& Vetor resultado.
 * @param const vector_t& Vetor parcela 1.
 * @param const vector_t& Vetor parcela 2.
 */
void sum(vector_t& res, const vector_t& v1, const vector_t& v2) {
	for (int i = 0; i < VEC_LEN; i++) {
		res[i] = v1[i] + v2[i];
	}
}

/**
 * Realiza a operação de produto escalar entre dois vetores v1 e v2.
 * 
 * @param const vector_t Vetor 1.
 * @param const vector_t Vetor 2.
 * 
 * @return int O valor do produto escalar entre os vetores.
 */
float dot(const vector_t& v1, const vector_t& v2) {
	float s = 0;
	
	for (int i = 0; i < VEC_LEN; i++) {
		s += v1[i] * v2[i];
	}
	
	return s;
}
