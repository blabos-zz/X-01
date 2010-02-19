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

const int MAX_ROW	= 3;
const int MAX_COL	= 3;

typedef float matrix_t[MAX_ROW][MAX_COL];

void read_matrix(matrix_t& m);
void show_matrix(const matrix_t& m);
float avg_row(const matrix_t& m, const int row);
float avg_col(const matrix_t& m, const int col);

#endif /* MATRIX_H_ */
