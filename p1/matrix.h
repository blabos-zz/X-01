/*
 * matrix.h
 *
 *  Created on: Oct 11, 2009
 *      Author: wesley
 */

#ifndef MATRIX_H_
#define MATRIX_H_


class Matrix {
public:
	Matrix();
	
	void mostra();
	void le();
	Matrix& soma(Matrix);
	Matrix& subtrai(Matrix);
	
private:
	void inicializa();
	
private:
	//int	_matrix[2][2];
	int a, b, c, d;
};


#endif /* MATRIX_H_ */
