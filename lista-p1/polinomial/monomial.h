#ifndef MONOMIAL_H
#define MONOMIAL_H


class Monomial {
public:
	Monomial();
	Monomial(float, int);
	Monomial(const Monomial&);
	~Monomial();
	
	void show();
    
    Monomial& add(Monomial&);
    Monomial& sub(Monomial&);
    Monomial& mul(Monomial&);
    Monomial& div(Monomial&);
    
    void derivative();
    void integrate();
    
    float evaluate(float);
    void assign(Monomial&);
    
    float coefficient();
    int exponent();
    
private:
    float	_coefficient;
    int     _exponent;
};


#endif

