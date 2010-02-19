#include "matrix.h"

int main(int argc, char** argv) {
    
    Matrix m1, m2;
    
    m1.read();
    m2.read();
    
    m1.add(m2);
    m1.sub(m2);
    
    m1.show();
    
    
    return 0;
}

