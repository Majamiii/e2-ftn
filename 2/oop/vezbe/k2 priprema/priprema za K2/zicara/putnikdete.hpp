#ifndef PUTNIKDETE_HPP_INCLUDED
#define PUTNIKDETE_HPP_INCLUDED

#include "putnik.hpp"

class PutnikDete:public Putnik{

private:
    DinString mbRoditelja;
public:
    PutnikDete() : Putnik(), mbRoditelja("") {}
    PutnikDete(int brk, VrstaKarte vrk, const DinString& mb, const DinString& i, const DinString& mbr):
        Putnik(brk,vrk,mb,i),mbRoditelja(mbr) {}
    PutnikDete(const Putnik& roditelj, const DinString& mb) :
        Putnik((Putnik)roditelj), mbRoditelja(mb) {}

    DinString toString() const {
        return "Dete: "+this->ime+" "+this->mb+" "+mbRoditelja;
    }

};

#endif // PUTNIKDETE_HPP_INCLUDED
