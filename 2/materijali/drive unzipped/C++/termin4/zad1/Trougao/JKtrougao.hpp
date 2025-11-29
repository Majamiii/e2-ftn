#ifndef JKTROUGAO_HPP_INCLUDED
#define JKTROUGAO_HPP_INCLUDED
#include "trougao.hpp"

class JKtrougao : public Trougao {
private:
    double a, b, c;

public:
    JKtrougao() : Trougao(3, 3, 5){}
    JKtrougao(double aa, double bb) : Trougao(aa, aa, bb){}
    JKtrougao(const JKtrougao& jkt) : Trougao(jkt){}


};

#endif // JKTROUGAO_HPP_INCLUDED
