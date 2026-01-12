#ifndef JEDNAKOKRAKI_HPP_INCLUDED
#define JEDNAKOKRAKI_HPP_INCLUDED

#include "trougao.hpp"

class Jednakokraki : public Trougao{
public:
    Jednakokraki() : Trougao(1,2,2) {}
    Jednakokraki(int a, int b) : Trougao(a,a,b) {}
    Jednakokraki(const Jednakokraki& t) :  Trougao(t.a, t.a, t.c) {}
};

#endif // JEDNAKOKRAKI_HPP_INCLUDED
