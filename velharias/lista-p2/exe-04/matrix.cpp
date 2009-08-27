/*
 * matrix.cpp
 *
 *  Created on: 31/05/2009
 *      Author: wesley
 */
#include "matrix.h"

/**
 * Lê da entrada padrão uma matriz m x n de números reais.
 * 
 * @param matrix_t& Referência para a matriz a ser lida.
 */
void read_matrix(matrix_t& m) {
	cout << "Insira uma matriz " << MAX_ROW << " X " << MAX_COL << endl;
	
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			cout << "m[" << i << "][" << j << "] = ";
			cin >> m[i][j];
		}
	}
}

/**
 * Mostra na saída padrão os valores da matriz.
 * 
 * @param const matrix_t& Referência constante para a matriz a ser mostrada.
 */
void show_matrix(const matrix_t& m) {
	cout << "Valores da matriz:" << endl;
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			cout << m[i][j] << "\t";
		}
		cout << endl;
	}
}

/**
 * Inicializa com zero cada elemento da matriz.
 * 
 * @param matrix_t& Referência para a matriz.
 */
void clear_matrix(matrix_t& m) {
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			m[i][j] = 0;
		}
	}
}
