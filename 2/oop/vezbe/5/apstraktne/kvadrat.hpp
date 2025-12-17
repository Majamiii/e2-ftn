#ifndef KVADRAT_HPP_INCLUDED
#define KVADRAT_HPP_INCLUDED

#include "pravougaonik.hpp"

class Kvadrat: public pravougaonik{

public:
    Kvadrat():pravougaonik(1,2){}
    Kvadrat(double a):pravougaonik(a,a){}
    Kvadrat(const Kvadrat& kv):pravougaonik(kv.a,kv.a){}
};

#endif // KVADRAT_HPP_INCLUDED
