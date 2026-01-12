#ifndef PUTNIK_HPP_INCLUDED
#define PUTNIK_HPP_INCLUDED

#include "karta.hpp"

class Putnik{
protected:
    Karta karta;
    DinString mb,ime;
public:
    Putnik() : karta(), mb(""),ime("") {}
    Putnik(int broj, VrstaKarte vr, const DinString& maticni, const DinString& i) :
        karta(broj,vr),mb(maticni),ime(i) {}
    DinString getMb() {return mb;}
    VrstaKarte getVrsta() {return karta.getVrsta();}

    virtual DinString toString() const {
        return mb+" "+ime;
    }

    friend ostream& operator<<(ostream& o, const Putnik& p){

        o<<endl<<"************ PUTNIK ************"<<endl;
        o<<p.karta;
        o<<"Putnik: "<<p.toString()<<endl;
        o<<"********************************"<<endl;
        return o;
    }
};

#endif // PUTNIK_HPP_INCLUDED
