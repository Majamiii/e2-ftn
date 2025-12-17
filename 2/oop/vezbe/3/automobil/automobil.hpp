#ifndef AUTOMOBIL_HPP_INCLUDED
#define AUTOMOBIL_HPP_INCLUDED

#include "menjac.hpp"
#include "skoljka.hpp"

class Automobil{

private:
    Menjac m;
    Skoljka s;
public:
    Automobil() : m(), s() {}
    Automobil(int br, TipMenjaca tm, bojaSkoljke bs) : m(br,tm),s(bs){}
    Automobil(const Automobil& a) : m(a.m), s(a.s) {}

    bool setBrojBrzina(int br){
        return m.setBrojBrzina(br);
    }
    void setBoja(bojaSkoljke bs){
        s.setBoja(bs);
    }
    void setTipMenjaca(TipMenjaca tipp){
        m.setTip(tipp);
    }
    int getBrojBrzina() const{
        return m.getBrojBrzina();
    }
    TipMenjaca getTip() const{
        return m.getTip();
    }
    bojaSkoljke getBoja() const{
        return s.getBoja();
    }

    friend void ispisiAutomobil(const Automobil&);

};

#endif // AUTOMOBIL_HPP_INCLUDED
