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
 * Calcula a média de uma determinada linha.
 * 
 * @param const matrix_t& Referência constante para uma matriz.
 * @param const int A linha a ser calculada (0 a m-1).
 * 
 * @return float A média da linha passada como parâmetro.
 */
float avg_row(const matrix_t& m, const int row) {
	float avg = 0.0;
	
	for (int i = 0; i < MAX_COL; i++) {
		avg += m[row][i];
	}
	
	avg /= MAX_COL;
	
	return avg;
}

/**
 * Calcula a média de uma determinada coluna.
 * 
 * @param const matrix_t& Referência constante para uma matriz.
 * @param const int A coluna a ser calculada (0 a n-1).
 * 
 * @return float A média da coluna passada como parâmetro.
 */
float avg_col(const matrix_t& m, const int col) {
	float avg = 0.0;
	
	for (int i = 0; i < MAX_ROW; i++) {
		avg += m[i][col];
	}
	
	avg /= MAX_ROW;
	
	return avg;
}
