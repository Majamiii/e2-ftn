#ifndef PRAVOUGAONIK_HPP_INCLUDED
#define PRAVOUGAONIK_HPP_INCLUDED

#include "figura.hpp"

class pravougaonik : public Figura {
protected:
    double a,b;
public:
    pravougaonik(){a=1;b=2;}
    pravougaonik(double aa, double bb){a=aa;b=bb;}
    pravougaonik(const pravougaonik& p){a=p.a;b=p.b;}

    double getA(){return a;}
    double getB(){return b;}
    double getO()const{
        return 2*(a+b);
    }
    double getP()const{
        return a*b;
    }
};

#endif // PRAVOUGAONIK_HPP_INCLUDED
