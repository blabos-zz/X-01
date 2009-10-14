#include "monomio.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void Monomio::read() {
    cout << "k: ";
    cin >> this->k;
    
    cout << "g: ";
    cin >> this->g;
}

void Monomio::show() {
    cout << this->k << "*x^" << this->g << endl;
}

void Monomio::add(const Monomio& m) {
    if (this->g == m.g) {
        this->k += m.k;
    }
    else {
        cout << "Cannot add" << endl;
    }
}

void Monomio::sub(const Monomio& m) {
    if (this->g == m.g) {
        this->k -= m.k;
    }
    else {
        cout << "Cannot sub" << endl;
    }
}

void Monomio::mul(const Monomio& m) {
    this->k *= m.k;
    this->g += m.g;
}

void Monomio::div(const Monomio& m) {
    if (m.k != 0) {
        this->k /= m.k;
        this->g -= m.g;
    }
    else {
        cout << "Cannot div by zero" << endl;
    }
}

// g * k * x ^ (g - 1)
Monomio Monomio::derivative() {
    Monomio m;
    
    m.k = this->k * this->g;
    m.g = this->g - 1;
    
    return m;
}

// k * (1/(g+1)) * x ^ (g + 1)
Monomio Monomio::integrate() {
    Monomio m;
    
    if (this->g != -1) {
        m.g = this->g + 1;
        m.k = this->k / (this->g + 1);
    }
    else {
        cout << "Cannot integrate" << endl;
        m = *this;
    }
    
    return m;
}

