#ifndef PUTNIK_DETE_HPP_INCLUDED
#define PUTNIK_DETE_HPP_INCLUDED
#include "putnik.hpp"


class PutnikDete : public Putnik {
private:
    DinString mbRoditelja;
public:
    PutnikDete() : Putnik(), mbRoditelja() {};
    PutnikDete(const Putnik& p, const DinString& str) : Putnik(p), mbRoditelja(str) {};
    PutnikDete(int brK, VrstaKarte vrstaK, const DinString& mmbb, const DinString& name, const DinString& mbParent)
    : Putnik(brK, vrstaK, mmbb, name), mbRoditelja(mbParent) {};

    DinString toString() const {
        DinString ret = "Dete od: ";
        ret+=Putnik::toString();
        ret+="\t\nMaticni broj roditelja: ";
        ret+=mbRoditelja;
        return ret;
    }
};

#endif // PUTNIK_DETE_HPP_INCLUDED
