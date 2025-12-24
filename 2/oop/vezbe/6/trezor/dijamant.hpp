#ifndef DIJAMANT_HPP_INCLUDED
#define DIJAMANT_HPP_INCLUDED

#include <iostream>
using namespace std;

class Dijamant {
private:
    double vrednost;
    double br_karata;
public:
    Dijamant() : vrednost(10000), br_karata(10) {}
    Dijamant(double vr, double br) : vrednost(vr), br_karata(br) {}
    Dijamant(const Dijamant& d) : vrednost(d.vrednost), br_karata(d.br_karata) {}

    // ---------------------

    friend ostream& operator<<(ostream& out, const Dijamant& d){
        out<<endl<<"Vrednost dijamanta je "<<d.vrednost<<" a broj karata je "<<d.br_karata<<endl;
        return out;
    }

};

#endif // DIJAMANT_HPP_INCLUDED
