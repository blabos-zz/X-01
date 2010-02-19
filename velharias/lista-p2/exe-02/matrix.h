/*
 * matrix.h
 *
 *  Created on: 31/05/2009
 *      Author: wesley
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>

#include "string.h"

using namespace std;

const int ORD = 2;
typedef float matrix_t[ORD][ORD];

void read_matrix(matrix_t& m, int ord = ORD);
void show_matrix(const matrix_t& m, int ord = ORD);
float laplace_det(const matrix_t& m, int ord = ORD);

#endif /* MATRIX_H_ */
