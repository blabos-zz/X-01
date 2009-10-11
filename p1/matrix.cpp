/*
 * matrix.cpp
 *
 *  Created on: Oct 11, 2009
 *      Author: wesley
 */
#include "matrix.h"
#include <iostream>

using namespace std;

Matrix::Matrix() {
	inicializa();
}


void Matrix::mostra() {
	cout << a << "\t";
	cout << b << endl;
	cout << c << "\t";
	cout << d << endl;
	
	cout << endl;
	
	/*for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << _matrix[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;*/
}

void Matrix::le() {
	cout << "m[0][0] = "; cin >> a;
	cout << "m[0][1] = "; cin >> b;
	cout << endl;
	cout << "m[1][0] = "; cin >> c;
	cout << "m[1][1] = "; cin >> d;
	cout << endl;
	/*
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << "m[" << i << "][" << j << "] = ";
			cin >> _matrix[i][j];
		}
		cout << endl;
	} 
	cout << endl;*/
}

Matrix& Matrix::soma(Matrix m) {
	a += m.a;
	b += m.b;
	c += m.c;
	d += m.d;
	/*
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			_matrix[i][j] += m._matrix[i][j];
		}
	}*/
	
	return *this;
}

Matrix& Matrix::subtrai(Matrix m) {
	a -= m.a;
	b -= m.b;
	c -= m.c;
	d -= m.d;
	
	/*
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			_matrix[i][j] -= m._matrix[i][j];
		}
	}*/
	
	return *this;
}




void Matrix::inicializa() {
	a = 0;
	b = 0;
	c = 0;
	d = 0;
	
	/*
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			_matrix[i][j] = 0;
		}
	}*/
}
