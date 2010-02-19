#include "monomial.h"

#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::pow;


Monomial::Monomial()
	:	_coefficient(0.0), _exponent(0) {
	
}

Monomial::Monomial(float c, int e)
	:_coefficient(c), _exponent(e) {
	
}

Monomial::Monomial(const Monomial& original) {
	this->_coefficient	= original._coefficient;
	this->_exponent		= original._exponent;
}

Monomial::~Monomial() {
	
}

void Monomial::show() {
    cout << this->_coefficient << "*x^" << this->_exponent << endl;
}

Monomial& Monomial::add(Monomial& m) {
	if ((m.coefficient() != 0) && ((this->_coefficient == 0) || (this->_exponent == m._exponent))) {
		this->_coefficient	+= m._coefficient;
		this->_exponent		 = m._exponent;
	}
    
    return *this;
}

Monomial& Monomial::sub(Monomial& m) {
    if ((m.coefficient() != 0) && ((this->_coefficient == 0) || (this->_exponent == m._exponent))) {
		this->_coefficient	-= m._coefficient;
		this->_exponent		 = m._exponent;
	}
    
    return *this;
}

Monomial& Monomial::mul(Monomial& m) {
    this->_coefficient *= m._coefficient;
    this->_exponent += m._exponent;
    
    return *this;
}

Monomial& Monomial::div(Monomial& m) {
    if (m._coefficient != 0) {
        this->_coefficient /= m._coefficient;
        this->_exponent -= m._exponent;
    }
    
    return *this;
}

// g * k * x ^ (g - 1)
void Monomial::derivative() {
    this->_coefficient *= this->_exponent;
    if (this->_exponent > 0) this->_exponent--;
}

// k * (1/(g+1)) * x ^ (g + 1)
void Monomial::integrate() {
    if (this->_exponent != -1) {
        this->_exponent++;
        this->_coefficient /= this->_exponent;
    }
    else {
        cout << "Cannot integrate" << endl;
    }
}

float Monomial::evaluate(float x) {
	return this->_coefficient * pow(x, this->_exponent);
}

void Monomial::assign(Monomial& val) {
	this->_coefficient	= val._coefficient;
	this->_exponent		= val._exponent;
}

float Monomial::coefficient() {
	return this->_coefficient;
}

int Monomial::exponent() {
	return this->_exponent;
}
