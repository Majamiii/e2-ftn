#ifndef OSOBA_HPP_INCLUDED
#define OSOBA_HPP_INCLUDED

#include <iostream>
#include "dinstring.hpp"

/*
Napisati klasu Osoba koja sadrži polja: ime (DinString) i prezime (DinString). U
klasi implementirati:
- Osoba()
- Osoba(const char*, const char*)
- Osoba(const DinString&, const DinString&)
- Osoba(const Osoba&)
- metod predstaviSe() - ispisuje (na konzolu) ime i prezime osobe.
*/

class Osoba{

protected:
    DinString ime, prezime;

public:
    Osoba() : ime("Imenko"), prezime("Prezimenic") {}
    Osoba (const char* i, const char* p) : ime(i), prezime(p) {}
    Osoba (const DinString& i, const DinString& p) : ime(i), prezime(p) {}
    Osoba(const Osoba& o) : ime(o.ime), prezime(o.prezime) {}
    virtual void predstaviSe() const {
        cout<<endl<<"Ja sam "<<ime<<" "<<prezime<<endl;
    }
};

#endif // OSOBA_HPP_INCLUDED
