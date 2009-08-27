/*
 * matrix.cpp
 *
 *  Created on: 31/05/2009
 *      Author: wesley
 */
#include "matrix.h"

/** Declara a função _minor visível somente dentro deste arquivo */
void _minor(matrix_t& min, const matrix_t& mat, int ord, int row, int col);

/**
 * Lê da entrada padrão uma matriz m x n de números reais.
 * 
 * @param matrix_t& Referência para a matriz a ser lida.
 * @param int Ordem da matriz. Opcional. Default é ORD.
 */
void read_matrix(matrix_t& m, int ord) {
	cout << "Insira uma matriz de ordem " << ord << endl;
	
	for (int i = 0; i < ord; i++) {
		for (int j = 0; j < ord; j++) {
			cout << "m[" << i << "][" << j << "] = ";
			cin >> m[i][j];
		}
	}
}

/**
 * Mostra na saída padrão os valores da matriz.
 * 
 * @param const matrix_t& Referência constante para a matriz a ser mostrada.
 * @param int Ordem da matriz. Opcional. Default é ORD.
 */
void show_matrix(const matrix_t& m, int ord) {
	cout << "Valores da matriz:" << endl;
	for (int i = 0; i < ord; i++) {
		for (int j = 0; j < ord; j++) {
			cout << m[i][j] << "\t";
		}
		cout << endl;
	}
}

/**
 * Calcula o determinante de uma matriz segundo o algoritmo de Laplace.
 * 
 * @param const matrix_t& Referência constante para uma matriz.
 * @param int Ordem da matriz. Opcional. Default é ORD.
 * 
 * @return float O determinante da matriz passada como parâmetro.
 */
float laplace_det(const matrix_t& m, int ord) {
	
	if (ord <= 1) return m[0][0];
	
	int signal = 1;
	float det = 0;
	matrix_t minor;
	
	for (int i = 0; i < ord; i++) {
		_minor(minor, m, ord - 1, 0, i);
		det += signal * m[0][i] * laplace_det(minor, ord - 1);
		signal = -signal;
	}
	
	return det;
}

/**
 * Extrai a sub-matriz referente a determinadas linha e coluna.
 * 
 * @param matrix_t& Referência para a sub-matriz destinho
 * @param const matrix_t& Referência constante para a matriz original.
 * @param int Ordem da sub-matriz.
 * @param int Linha.
 * @param int Coluna.
 */
void _minor(matrix_t& min, const matrix_t& mat, int ord, int row, int col) {
	int i, j, a, b;
	
	for (i = a = 0; a < ord; i++,a++) {
		if (i == row) i++;
		for (j = b = 0; b < ord; j++, b++) {
			if (j == col) j++;
			min[a][b] = mat[i][j];
		}
	}
}
