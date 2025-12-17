#ifndef OSOBA_HPP_INCLUDED
#define OSOBA_HPP_INCLUDED

#include "dinstring.hpp"

class Osoba{

protected:
    DinString ime,prezime;
public:
    Osoba():ime("x"),prezime("y"){}
    Osoba(const char* i, const char* p): ime(i), prezime(p) {}
    Osoba(const DinString& i, const DinString& p): ime(i), prezime(p) {}
    Osoba(const Osoba& o):ime(o.ime), prezime(o.prezime) {}
    virtual void predstaviSe()const{
        cout<<"Ja sam "<<ime<<" "<<prezime<<endl;
    }
};

#endif // OSOBA_HPP_INCLUDED
