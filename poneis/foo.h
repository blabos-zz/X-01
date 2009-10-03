#ifndef FOO_H
#define FOO_H

class Foo {
public:
    Foo();
    
    int     getNum();
    void    setNum(int a);
    
    int quad();
private:
    int num;
};

#endif

