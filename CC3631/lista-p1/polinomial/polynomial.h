#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "monomial.h"


class Polynomial {
public:
	Polynomial();
	Polynomial(const Polynomial&);
	Polynomial(Monomial&);
	Polynomial(int degree);
	~Polynomial();
	
	void show();
	
	void add(const Polynomial&);
	
	void derivative();
	void integrate();
	
private:
	int			_degree;
	Monomial*	_terms;
};

#endif

