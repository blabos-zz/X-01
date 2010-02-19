/*
 * polynomial.cpp
 *
 *  Created on: Oct 14, 2009
 *      Author: wesley
 */
#include "polynomial.h"

#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::fabs;


Polynomial::Polynomial()
	:	_degree(0), _terms(0) {
	this->_terms = new Monomial[this->_degree + 1];
}

Polynomial::Polynomial(const Polynomial& original)
	: _degree(0), _terms(0) {
	this->_terms 	= new Monomial[original._degree + 1];
	this->_degree	= original._degree;
	
	for (int i = 0; i < this->_degree + 1; i++) {
		this->_terms[i] = original._terms[i];
	}
}

Polynomial::Polynomial(Monomial& m)
	: _degree(0), _terms(0) {
	this->_terms 				= new Monomial[m.exponent() + 1];
	this->_degree				= m.exponent();
	this->_terms[m.exponent()]	= m;
	
	for (int i = 0; i < this->_degree; i++) {
		this->_terms[i] = Monomial(0.0, i);
	}
}

Polynomial::Polynomial(int degree)
	: _degree(0), _terms(0) {
	this->_degree	= degree > 0 ? degree : 0;
	this->_terms	= new Monomial[this->_degree + 1];
}

Polynomial::~Polynomial() {
	if (this->_terms != 0) {
		delete[] this->_terms;
		this->_terms = 0;
	}
}


void Polynomial::show() {
	int c, e;
	
	for (int i = this->_degree; i >= 0; i--) {
		c = _terms[i].coefficient();
		e = _terms[i].exponent();
		
		if (c) {
			if (c >= 0) cout << " + ";
			else cout << " - ";
			
			cout <<  fabs(c);
			
			if (e == 1) cout << "*x";
			else if (e != 0) cout << "*x^" << _terms[i].exponent();
		}
	}
	
	cout << endl;
}

void Polynomial::add(const Polynomial& p) {
	if (p._degree > this->_degree) {
		Polynomial copy(*this);
		
		delete[] this->_terms;
		this->_terms = new Monomial[p._degree + 1];
		for (int i = copy._degree; i >= 0; i--) {
			this->_terms[i] = copy._terms[i];
		}
		this->_degree = p._degree;
	}
	
	int degree = 0;
	for (int i = 0; i < this->_degree + 1; i++) {
		this->_terms[i].add(p._terms[i]);
		if (this->_terms[i].coefficient() != 0) {
			degree = i;
		}
	}
	
	this->_degree = degree;
}

void Polynomial::derivative() {
	for (int i = 0; i < this->_degree; i++) {
		this->_terms[i + 1].derivative();
		this->_terms[i] = this->_terms[i + 1];
	}
	this->_degree--;
}

void Polynomial::integrate() {
	this->_degree++;
	
	Polynomial copy(*this);
	
	delete[] this->_terms;
	this->_terms = new Monomial[this->_degree + 1];
	
	for (int i = copy._degree; i >= 0; i--) {
		this->_terms[i] = copy._terms[i];
	}
	
	for (int i = this->_degree; i > 0; i--) {
		this->_terms[i - 1].integrate();
		this->_terms[i] = this->_terms[i - 1];
	}
}
