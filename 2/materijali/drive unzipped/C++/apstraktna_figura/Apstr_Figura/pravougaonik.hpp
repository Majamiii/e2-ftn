#ifndef PRAVOUGAONIK_HPP_INCLUDED
#define PRAVOUGAONIK_HPP_INCLUDED

#include "figura.hpp"

class Pravougaonik: public Figura {
private:
    double a, b;
public:
    Pravougaonik() {
        a = 1;
        b = 2;
    }
    Pravougaonik(double aa, double bb) {
        a = aa;
        b = bb;
    }
    Pravougaonik(const Pravougaonik& p) {
        a = p.a;
        b = p.b;
    }
    double getA() {
        return a;
    }
    double getB() {
        return a;
    }
    double getO()const {
        return 2*a + 2*b;
    }
    double getP()const {
        return a*b;
    }
};

#endif // PRAVOUGAONIK_HPP_INCLUDED
