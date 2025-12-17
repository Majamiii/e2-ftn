#ifndef PRAVOUGAONIK_HPP_INCLUDED
#define PRAVOUGAONIK_HPP_INCLUDED

#include "figura.hpp"

class Pravougaonik : public Figura
{
private:
    double a,b;
public:
    Pravougaonik() : a(1), b(2) {}
    Pravougaonik(double an, double bn) : a(an), b(bn) {}
    Pravougaonik(const Pravougaonik& pn) {
        a = pn.a; b=pn.b;
    }
    double getA() const{
        return a;
    }
    double getB() const{
        return b;
    }
    double getO() const{
        return 2*(a+b);
    }
    double getP() const{
        return a*b;
    }
};

#endif // PRAVOUGAONIK_HPP_INCLUDED
