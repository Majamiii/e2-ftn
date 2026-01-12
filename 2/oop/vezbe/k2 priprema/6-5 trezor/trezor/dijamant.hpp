#ifndef DIJAMANT_HPP_INCLUDED
#define DIJAMANT_HPP_INCLUDED

#include "trezor.hpp"
using namespace std;

class Dijamant{

private:
    double vrednost;
    double brKarata;
public:
    Dijamant() : vrednost(0), brKarata(0) {}
    Dijamant(double v, double b) : vrednost(v), brKarata(b) {}
    Dijamant(const Dijamant& d) : vrednost(d.vrednost), brKarata(d.brKarata) {}

    friend ostream& operator<<(ostream& os, const Dijamant& d){
        os<<endl<<"--- dijamant ---"<<endl;
        os<<"Vrednost: "<<d.vrednost<<endl;
        os<<"Broj karata: "<<d.brKarata<<endl<<endl;
        return os;
    }

};

#endif // DIJAMANT_HPP_INCLUDED
