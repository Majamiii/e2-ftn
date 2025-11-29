#ifndef KARTA_HPP_INCLUDED
#define KARTA_HPP_INCLUDED
#include <iomanip>

using namespace std;

enum VrstaKarte {LETO,SKI,SKI_OPENING};

class Karta {
private:
    int brojKarte;
    VrstaKarte vrsta;
public:
    Karta(){};
    Karta(int brK, VrstaKarte vr) : brojKarte(brK), vrsta(vr) {};
    int getBrKarte() const {
        return brojKarte;
    }

    VrstaKarte getVrstaKarte() const {
        return vrsta;
    }

    friend ostream& operator<< (ostream& os, const Karta& k) {
        cout << "Broj karte   : " << k.brojKarte << endl;
        cout << "Vrsta karte  : ";
        switch(k.vrsta) {
        case(LETO): os << "LETO" << endl; break;
        case(SKI): os << "SKI" << endl; break;
        case(SKI_OPENING): os << "SKI OPENING" << endl; break;
        }
        return os;
    }
};

#endif // KARTA_HPP_INCLUDED
