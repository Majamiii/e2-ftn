#ifndef ELIPSA_HPP_INCLUDED
#define ELIPSA_HPP_INCLUDED

#include "figura.hpp"
#include <cmath>

class Elipsa : public Figura
{
private:
    double a,b;
public:
    Elipsa() : a(1),b(1) {}
    Elipsa(double a1, double b1) : a(a1),b(b1) {}
    Elipsa(const Elipsa& e) {a=e.a; b=e.b;}

    double getO() const{
        return M_PI * ( 3*a+3*b-sqrt((3*a+b)*(a+3*b)) );
    }
    double getP() const{
        return a*b*M_PI;
    }
};

#endif // ELIPSA_HPP_INCLUDED
