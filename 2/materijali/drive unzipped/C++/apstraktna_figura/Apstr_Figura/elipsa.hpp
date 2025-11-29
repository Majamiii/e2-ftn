#ifndef ELIPSA_HPP_INCLUDED
#define ELIPSA_HPP_INCLUDED

#include "figura.hpp"

class Elipsa : public Figura {
protected:
    double x, y;
public:
    Elipsa() {
        x = 2;
        y = 4;
    }
    Elipsa(double aa, double bb) {
        x = aa;
        y = bb;
    }
    Elipsa(const Elipsa& e) {
        x = e.x;
        y = e.y;
    }

    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    double getO()const{
        return M_PI * (3 * (x + y) - sqrt((3 * x + y) * (x + 3 * y)));;
    }
    double getP()const{
        return M_PI * x * y;
    }

};

#endif // ELIPSA_HPP_INCLUDED
