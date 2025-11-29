#ifndef AUTO_HPP_INCLUDED
#define AUTO_HPP_INCLUDED
#include "Menjac.hpp"
#include "Skoljka.hpp"
#include <iostream>

using namespace std;

enum STANJE {
    UGASEN,
    U_VOZNJI,
    POKVAREN
};

class Automobil{
private:
    Skoljka SK;
    Menjac MNJ;
    STANJE Stanje_auta;
    int Atm_speed;
public:
    Automobil() : SK(), MNJ() {
        Stanje_auta = UGASEN;
        Atm_speed = 0;
    }
    Automobil(TipMenjaca tm, int br, BojaSkoljke bs, STANJE st, int speed) : SK(bs), MNJ(tm, br) {
        Atm_speed = speed;
        Stanje_auta = st;
    }
    Automobil(const Automobil& AUTO): MNJ(AUTO.MNJ), SK(AUTO.SK){
        Atm_speed = AUTO.Atm_speed;
        Stanje_auta = AUTO.Stanje_auta;
    }
    bool setBrojBrzina(int br) {
        return MNJ.setBrojBrzina(br);
    }
    void setBoja(BojaSkoljke bs){
        SK.setBoja(bs);
    }
    void setTipMenjaca(TipMenjaca tm){
        MNJ.setTip(tm);
    }
    int getBrojBrzina() const{
        return MNJ.getBrojBrzina();
    }
    bool upali(){
        if (Stanje_auta == UGASEN){
                Stanje_auta = U_VOZNJI;
                return true;
        }
        return false;
    }
    bool ugasi(){
        if (Stanje_auta == U_VOZNJI){
                Stanje_auta = UGASEN;
                return true;
        }

        return false;
    }
    bool pokvari(){
        if (Stanje_auta == UGASEN || Stanje_auta == U_VOZNJI){
            Stanje_auta = POKVAREN;
            return true;
        }
        return false;
    }
    bool popravi(){
        if (Stanje_auta == POKVAREN){
            Stanje_auta = UGASEN;
            return true;
        }
        return false;
    }
    bool PovecajBrzinu(){
        if (Stanje_auta == U_VOZNJI){
            if (Atm_speed == getBrojBrzina()) {
                return false;
            }
            Atm_speed += 1;
            return true;
        }
        return false;
    }
    bool SmanjiBrzinu(){
        if (Stanje_auta == U_VOZNJI){
            if (Atm_speed == 1) {
                return false;
            }
            Atm_speed -= 1;
            return true;
        }
        return false;
    }
    TipMenjaca getTipMenjaca() const{
        return MNJ.getTip();
    }
    BojaSkoljke getBojaSkoljke() const{
        return SK.getBoja();
    }
    friend void ispisiAutomobil(const Automobil&);

};

#endif // AUTO_HPP_INCLUDED
