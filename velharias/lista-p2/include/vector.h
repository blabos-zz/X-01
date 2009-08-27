/*
 * vector.h
 *
 *  Created on: 31/05/2009
 *      Author: wesley
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

using namespace std;

const int VEC_LEN = 5;
typedef int vector_t[VEC_LEN];

void read_vector(vector_t& v);
void show_vector(const vector_t& v, int len = VEC_LEN);
void clear_vector(vector_t& v, int len = VEC_LEN);

void sum(vector_t& res, const vector_t& v1, const vector_t& v2);
float dot(const vector_t& v1, const vector_t& v2);

#endif /* VECTOR_H_ */
