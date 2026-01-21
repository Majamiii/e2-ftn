#ifndef DIJAMANT_HPP_INCLUDED
#define DIJAMANT_HPP_INCLUDED

#include "trezor.hpp"
using namespace std;

class Dijamant{
private:
    double vrednost, brKarata;
public:
    Dijamant() : vrednost(0),brKarata(0){}
    Dijamant(double vr, double brk) : vrednost(vr),brKarata(brk) {}
    Dijamant(const Dijamant& d) : vrednost(d.vrednost),brKarata(d.brKarata) {}

    friend ostream& operator<<(ostream& os, const Dijamant& d){
        os<<endl<<"Dijamant"<<endl;
        os<<"vrednost: "<<d.vrednost<<endl;
        os<<"Br karata: "<<d.brKarata<<endl;
        return os;
    }

};

#endif // DIJAMANT_HPP_INCLUDED
