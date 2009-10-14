#include "matrix.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void Matrix::read() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << "mat[" << i << "][" << j << "] = ";
            cin >> this->_matrix[i][j];
        }
    }
}

void Matrix::show() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << this->_matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void Matrix::add(const Matrix& m) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            this->_matrix[i][j] += m._matrix[i][j];
        }
    }
}

void Matrix::sub(const Matrix& m) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            this->_matrix[i][j] -= m._matrix[i][j];
        }
    }
}
