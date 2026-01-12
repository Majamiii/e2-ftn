#ifndef ARTIKAL_HPP_INCLUDED
#define ARTIKAL_HPP_INCLUDED

#include <iostream>
#include <iomanip>
#include "dinstring.hpp"

using namespace std;


class Artikal{
protected:
    DinString naziv;
    double cena;
    static int instanci;
public:
    Artikal(const char n[], const double c) : naziv(n), cena(c) {}
    Artikal(const DinString& n, const double c) : naziv(n), cena(c) {}
    Artikal(const Artikal& a) : naziv(a.naziv), cena(a.cena) {}

    friend ostream& operator<<(ostream& os, const Artikal& a){
        os<<endl<<"---- artikal ----"<<endl;
        os<<"naziv: "<<a.naziv<<endl;
        os<<"cena: "<<a.cena<<endl;
        os<<"instanci: "<<a.instanci<<endl;

        return os;
    }
};

#endif // ARTIKAL_HPP_INCLUDED
