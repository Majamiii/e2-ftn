#ifndef OSOBA_HPP_INCLUDED
#define OSOBA_HPP_INCLUDED

#include <iostream>
#include "dinstring.hpp"

class Osoba {

protected:
    DinString ime, prezime;
public:
    Osoba() : ime(""), prezime("") {}
    Osoba(const DinString& i, const DinString& p) : ime(i),prezime(p) {}
    Osoba(const Osoba& o) : ime(o.ime),prezime(o.prezime) {}

    virtual void ispisi() {
        cout<<endl<<"ime: "<<ime<<endl<<"prezime: "<<prezime<<endl<<endl;
    }

};

#endif // OSOBA_HPP_INCLUDED
