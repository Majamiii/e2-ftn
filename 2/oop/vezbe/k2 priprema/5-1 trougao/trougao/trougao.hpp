#ifndef TROUGAO_HPP_INCLUDED
#define TROUGAO_HPP_INCLUDED

#include <iostream>
using namespace std;

class Trougao{

protected:
    int a,b,c;
public:
    Trougao() : a(1), b(2), c(3) {}
    Trougao(int aa, int bb, int cc) : a(aa), b(bb), c(cc) {}
    Trougao(const Trougao& t) : a(t.a), b(t.b), c(t.c) {}

    int getA() const {return a;}
    int getB() const {return b;}
    int getC() const {return c;}

    void setA(int aa) {a=aa;}
    void setB(int bb) {b=bb;}
    void setC(int cc) {c=cc;}

    void ispisi() {
        cout<<endl<<"a="<<a<<", b="<<b<<", c="<<c<<endl<<endl;
    }

};

#endif // TROUGAO_HPP_INCLUDED
