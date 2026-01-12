#ifndef PROIZVOD_HPP_INCLUDED
#define PROIZVOD_HPP_INCLUDED

#include <iostream>
#include "dinstring.hpp"
#include "list.hpp"

using namespace std;

class Proizvod{
protected:
    int cena;
    DinString naziv;
public:
    Proizvod(int c, DinString n) : cena(c),naziv(n) {}
    virtual void izracunajPopust() =0;
    virtual void ispisi(){
        cout<<"naziv: "<<naziv<<endl;
        cout<<"cena: "<<cena<<endl;
    }
    DinString getNaziv(){return naziv;}
};

#endif // PROIZVOD_HPP_INCLUDED
