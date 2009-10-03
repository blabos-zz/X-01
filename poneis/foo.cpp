#include "foo.h"

Foo::Foo() {

}

int Foo::getNum() {
    return this->num;
}

void Foo::setNum(int a) {
    this->num = a + 42;
}

