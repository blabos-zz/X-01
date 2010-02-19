/*
 * exe-02.cpp
 *
 *  Created on: 23/05/2009
 *      Author: wesley
 *      
 *  2. Faça um algoritmo capaz de ler n matrizes (n é fornecido pelo usuário)
 *  e determinar qual delas possui determinante de maior valor, imprimindo
 *  este valor e identificando a matriz associada. Use procedimentos e funções
 *  onde for conveniente.
 */
#include <iostream>

#include "matrix.h"

using namespace std;

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	
	int			n;
	float		det,  max_det;
	
	matrix_t	mat1, mat2;
	matrix_t* 	ptr_tmp;
	
	matrix_t* 	ptr_max_mat	= &mat1;
	matrix_t* 	ptr_mat		= &mat2;
	
	
	cout << "Digite a quantidade e matrizes "
		<< ORD << " X " << ORD << " desejadas: ";
	cin >> n;
	
	if (n > 0) {
		read_matrix(*ptr_max_mat);
		max_det = laplace_det(*ptr_max_mat);
		
		cout << "Det = " << max_det << endl;
		
		for (int i = 1; i < n; i++) {
			read_matrix(*ptr_mat);
			det = laplace_det(*ptr_mat);
			
			cout << "Det = " << det << endl;
			
			if (det > max_det) {
				max_det 	= det;
				ptr_tmp 	= ptr_max_mat;
				ptr_max_mat	= ptr_mat;
				ptr_mat		= ptr_tmp;
			}
		}
		
		cout << endl << "Maior determinante e sua matriz" << endl;
		cout << "Max Det = " << max_det << endl;
		show_matrix(*ptr_max_mat);
	}
	else {
		cout << "Tente com uma ou mais..." << endl;
	}
	
	return 0;
}
