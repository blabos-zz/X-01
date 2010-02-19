/*
 * exe-01.cpp
 *
 *  Created on: 23/05/2009
 *      Author: wesley
 *      
 *  1. Faça um algoritmo capaz de ler uma matriz e calcular a média de cada
 *  linha e de cada coluna, imprimindo estes resultados. Use procedimentos e
 *  funções onde for conveniente.
 */
#include <iostream>

#include "matrix.h"

using namespace std;

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	
	matrix_t mat;
	
	cout << endl;
	read_matrix(mat);
	
	cout << endl;
	show_matrix(mat);
	
	cout << endl;
	for (int i = 0; i < MAX_ROW; i++) {
		cout << "avg_row[" << i << "] = " << avg_row(mat, i) << endl;
	}
	
	cout << endl;
	for (int i = 0; i < MAX_COL; i++) {
		cout << "avg_col[" << i << "] = " << avg_col(mat, i) << endl;
	}
	
	return 0;
}
