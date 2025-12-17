#ifndef RERNA_HPP_INCLUDED
#define RERNA_HPP_INCLUDED

#include <iostream>
using namespace std;

enum StanjeRerne {UKLJUCENA, ISKLJUCENA, POKVARENA};

class Rerna{
private:
    int temperatura;
    StanjeRerne trenutnoStanje;

public:
    Rerna();
    Rerna(int i);
    Rerna(const Rerna&);

    int getTemperatura() const;
    StanjeRerne getTrenutnoStanje() const;

    bool ukljuci();
    bool iskljuci();
    bool pokvari();
    bool popravi();

    bool pojacajTemperaturu();
    bool smanjiTemperaturu();
};

#endif // RERNA_HPP_INCLUDED
