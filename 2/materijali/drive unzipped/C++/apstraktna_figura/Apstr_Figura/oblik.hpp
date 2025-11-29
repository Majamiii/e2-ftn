#ifndef OBLIK_HPP_INCLUDED
#define OBLIK_HPP_INCLUDED

#include "krug.hpp"
#include "kvadrat.hpp"

class Oblik {
public:
    Kvadrat A;
    Krug B;
private:
    Oblik(): A(2), B(1) {};
    Oblik(double aa): A(aa), B(aa/2) {};
    Oblik(const Oblik& o): A(o.A), B(o.B) {};
    double getP()const{
        return A.getP() - B.getP();
    }
    double getO()const{
        return A.getO() + B.getO();
    }

};


#endif // OBLIK_HPP_INCLUDED
