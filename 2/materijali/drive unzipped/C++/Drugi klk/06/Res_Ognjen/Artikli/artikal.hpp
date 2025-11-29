#ifndef ARTIKAL_HPP_INCLUDED
#define ARTIKAL_HPP_INCLUDED

#include "dinstring.hpp"
#include <iomanip>

class Artikal {
private:
    DinString naziv;
    double cena;
    static int instanci;
public:
     Artikal(const char[], const double);
     Artikal(const DinString&, const double);
     Artikal(const Artikal&);
     ~Artikal();

     friend ostream& operator<<(ostream&, const Artikal&);
/*  preklapanje operatora ispisa se radi friend funkcijom, 1. ostream je povratni tip
    operator koji preklapamo navodimo, prvi parametar je adresa buffera, druga je string
    koji ispisujemo, realizaciju dobijamo u fajlu, i implementacija je vec uradjena
*/
};

#endif // ARTIKAL_HPP_INCLUDED
