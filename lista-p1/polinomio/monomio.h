#ifndef MONOMIO_H
#define MONOMIO_H


// k * x ^ g
class Monomio {
public:
    void read();
    void show();
    
    void add(const Monomio&);
    void sub(const Monomio&);
    void mul(const Monomio&);
    void div(const Monomio&);
    
    Monomio derivative();
    Monomio integrate();
    
private:
    float   k;
    int     g;
};


#endif

