#include <iostream>
#ifndef KVADRAT_HPP_INCLUDED
#define KVADRAT_HPP_INCLUDED

#include "pravougaonik.hpp"
using namespace std;

class Kvadrat: public Pravougaonik {
public:
    Kvadrat():Pravougaonik(1, 1) {}
    Kvadrat(double aa):Pravougaonik(aa, aa) {}
    Kvadrat(const Kvadrat& kv):Pravougaonik((Pravougaonik)kv) {}
};

#endif // KVADRAT_HPP_INCLUDED
