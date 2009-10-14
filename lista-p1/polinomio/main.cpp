#include <iostream>
#include <cstdlib>

#include "monomio.h"

int main(int argc, char** argv) {

    Monomio m1, m2, m3;
    
    m1.read();
    m2.read();
    
    m1.show();
    m2.show();
    
    m1.add(m2);
    m1.show();
    
    m1.sub(m2);
    m1.show();
    
    m1.mul(m2);
    m1.show();
    
    m1.div(m2);
    m1.show();
    
    m3 = m1.derivative();
    m3.show();
    
    m3 = m1.integrate();
    m3.show();
    
    return EXIT_SUCCESS;
}

