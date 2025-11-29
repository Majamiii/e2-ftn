#ifndef PUTNIK_HPP_INCLUDED
#define PUTNIK_HPP_INCLUDED
#include "karta.hpp"
#include "dinstring.hpp"

class Putnik {
protected:
    Karta Karta;
    DinString mb;
    DinString ime;
public:
    Putnik() : Karta(), mb(), ime() {};
    Putnik(int brK, VrstaKarte vrstaK, const DinString& mmbb, const DinString& name) : Karta(brK, vrstaK), mb(mmbb), ime(name){};

    DinString getMb() {
            return mb;
    }
    VrstaKarte getVrstaKarte() const {
            return Karta.getVrstaKarte();
    }

    virtual DinString toString() const {
        return ime + " ---> " + mb;
    }
    friend ostream& operator<<(ostream& os, const Putnik& p){
        os << "Ime i JMBG (za decu jmbg roditelja)  : " << p.toString() << endl;
        os << p.Karta << endl;

        return os;
    }
};

#endif // PUTNIK_HPP_INCLUDED
