#include <iostream>
#include <cstdlib>

#include "monomial.h"
#include "polynomial.h"

using namespace std;

int main(int argc, char** argv) {

    Monomial m1(5, 2), m2(-5, 5), m3;
    
    Polynomial p1(m1), p2(m2), p3;
    
    cout << "P1: ";
    p1.show();
    cout << "P2: ";
    p2.show();
    
    p1.add(p2);
    cout << "P1: ";
    p1.show();
    
    p1.derivative();
    cout << "P1: ";
    p1.show();
    p1.derivative();
    cout << "P1: ";
    p1.show();
    p1.derivative();
    cout << "P1: ";
    p1.show();
    p1.derivative();
    cout << "P1: ";
    p1.show();
    
    p1.integrate();
    cout << "P1: ";
    p1.show();
    
    
    
    return EXIT_SUCCESS;
}

