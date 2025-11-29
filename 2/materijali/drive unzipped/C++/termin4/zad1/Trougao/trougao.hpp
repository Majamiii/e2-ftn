#ifndef TROUGAO_HPP_INCLUDED
#define TROUGAO_HPP_INCLUDED
#include <iostream>
#include <cmath>

using namespace std;


class Trougao {
private:
    double a, b, c;
public:
    Trougao(){
        a = 3;
        b = 4;
        c = 5;
    }

    Trougao(double aa, double bb, double cc) {
        a = aa;
        b = bb;
        c = cc;
    }

    Trougao(const Trougao& t) {
        a = t.a;
        b = t.b;
        c = t.c;
    }


    int getA() const {
        return a;
    }
    int getB() const {
        return b;
    }
    int getC() const {
        return c;
    }
    double getP() const {
        double s = (a+b+c)/2;
        return sqrt(s*(s-a)*(s-b)*(s-c));
    }
    double getO() const {
        double s = (a+b+c);
        return s;
    }
};


#endif // TROUGAO_HPP_INCLUDED
