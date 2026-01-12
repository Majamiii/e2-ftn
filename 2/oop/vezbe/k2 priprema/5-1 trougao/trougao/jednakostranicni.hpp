#ifndef JEDNAKOSTRANICNI_HPP_INCLUDED
#define JEDNAKOSTRANICNI_HPP_INCLUDED

#include "jednakokraki.hpp"

class Jednakostranicni : public Jednakokraki{

public:
    Jednakostranicni() : Jednakokraki(1,1) {}
    Jednakostranicni(int a) : Jednakokraki(a,a) {}
    Jednakostranicni(const Jednakostranicni& j) : Jednakokraki(j.a, j.a) {}

};

#endif // JEDNAKOSTRANICNI_HPP_INCLUDED
