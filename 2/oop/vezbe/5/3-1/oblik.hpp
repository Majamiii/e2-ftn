#ifndef OBLIK_HPP_INCLUDED
#define OBLIK_HPP_INCLUDED

#include "elipsa.hpp"
#include "pravougaonik.hpp"

class Oblik{
protected:
    Elipsa e;
    Pravougaonik p;
public:
    Oblik() : e(2,1),p(4,2) {}
    Oblik(double a, double b) : e(a,b), p(2*a,2*b) {}
    Oblik(const Oblik& o) {
        p=o.p;
        e=o.e;
    }
    double getO() const{
        return e.getO()+p.getO();
    }
    double getP() const{
        return p.getP()-e.getP();
    }


};

#endif // OBLIK_HPP_INCLUDED
