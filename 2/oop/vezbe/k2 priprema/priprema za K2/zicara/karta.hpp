#ifndef KARTA_HPP_INCLUDED
#define KARTA_HPP_INCLUDED

#include <iostream>
#include "dinstring.hpp"
#include "list.hpp"

enum VrstaKarte {LETO, SKI, SKI_OPENING};

class Karta{
private:
    int brojKarte;
    VrstaKarte vrsta;
public:
    Karta() : brojKarte(0) {}
    Karta(int br, VrstaKarte vr) : brojKarte(br), vrsta(vr) {}

    int getBrKarte(){return brojKarte;}
    VrstaKarte getVrsta(){return vrsta;}

    friend ostream& operator<<(ostream& o, const Karta& k){
        o<<"Broj karte: "<<k.brojKarte<<endl;
        o<<"Vrsta karte: ";
        switch (k.vrsta){
        case(LETO):cout<<"letnja"<<endl;break;
        case(SKI):cout<<"ski"<<endl;break;
        case(SKI_OPENING):cout<<"ski opening"<<endl;break;
        }
        return o;
    }
};

#endif // KARTA_HPP_INCLUDED
