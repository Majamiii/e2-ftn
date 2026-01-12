#ifndef KOMPJUTER_HPP_INCLUDED
#define KOMPJUTER_HPP_INCLUDED

#include <iostream>
#include "dinstring.hpp"

/*
Napisati klasu Computer. Klasa sadrži polja: hddGB (double), ramGB (double),
gCard (DinString), os (DinString). U klasi implementirati:
- Konstruktor bez parametara
- Konstruktor sa parametrima (double, double, const char*, const char*)
- Konstruktor kopije
- Operator << za ispis vrednosti svih polja
*/

class Kompjuter{
private:
    double hddGB, ramGB;
    DinString gCard,os;
public:
    Kompjuter() : hddGB(0),ramGB(0),gCard(""),os(""){}
    Kompjuter(double a, double b, const char* c, const char* d) : hddGB(a),ramGB(b),gCard(c),os(d){}
    Kompjuter(const Kompjuter& k) : hddGB(k.hddGB),ramGB(k.ramGB),gCard(k.gCard),os(k.os){}

    friend ostream& operator<<(ostream& o, const Kompjuter& k){
        o<<endl<<"--- Kompjuter --- "<<endl;
        o<<"Hdd: "<<k.hddGB<<"          Ram: "<<k.ramGB<<endl;
        o<<"Graficka: "<<k.gCard<<"   OS: "<<k.os<<endl;
        return o;
    }

};

#endif // KOMPJUTER_HPP_INCLUDED
