#ifndef FIGURA_HPP_INCLUDED
#define FIGURA_HPP_INCLUDED

#include <cmath>

// apstraktna klasa
// jedina njena poenta je da se nasledi


class Figura{
public:
    virtual double getO()const=0;
    virtual double getP()const=0;
};

#endif // FIGURA_HPP_INCLUDED
