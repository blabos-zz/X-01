#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
    void read();
    void show();
    
    void add(const Matrix& m);
    void sub(const Matrix& m);
    
    
private:
    float _matrix[2][2];
};


#endif

