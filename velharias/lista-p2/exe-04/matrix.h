/*
 * matrix.h
 *
 *  Created on: 31/05/2009
 *      Author: wesley
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>

using namespace std;

const int MAX_ROW	= 3;
const int MAX_COL	= 3;

typedef int matrix_t[MAX_ROW][MAX_COL];

void read_matrix(matrix_t& m);
void show_matrix(const matrix_t& m);
void clear_matrix(matrix_t& m);

#endif /* MATRIX_H_ */
