#ifndef LEK_HPP_INCLUDED
#define LEK_HPP_INCLUDED

#include "artikal.hpp"
#include "dinstring.hpp"
#include "list.hpp"

class Lek:public Artikal{
private:
    long jkl;
    DinString naziv;
    double jedinicnaCena;
    int kolicina;

public:
    Lek() : jkl(0), naziv(""), jedinicnaCena(0), kolicina(0) {}
    Lek(long j, const DinString& n, double jc, int k) : jkl(j), naziv(n), jedinicnaCena(jc), kolicina(k) {}
    Lek(long j, const char* n, double jc, int k) : jkl(j), naziv(n), jedinicnaCena(jc), kolicina(k) {}
    Lek(const Lek& l) : jkl(l.jkl), naziv(l.naziv), jedinicnaCena(l.jedinicnaCena), kolicina(l.kolicina) {}

    double getVrednost() const{
        return jedinicnaCena*kolicina;
    }

    friend ostream& operator<<(ostream& os, const Lek& l){
        os<<"---- lek ----"<<endl;
        os<<"Jkl: "<<l.jkl<<endl;
        os<<"Naziv: "<<l.naziv<<endl;
        os<<"Jedinicna cena: "<<l.jedinicnaCena<<endl;
        os<<"Kolicina: "<<l.kolicina<<endl;
        return os;
    }

};

#endif // LEK_HPP_INCLUDED
