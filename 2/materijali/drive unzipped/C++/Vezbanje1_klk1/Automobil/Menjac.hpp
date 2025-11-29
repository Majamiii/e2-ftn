#ifndef MENJAC_HPP_INCLUDED
#define MENJAC_HPP_INCLUDED
#include <iostream>

using namespace std;
enum TipMenjaca {
    AUTOMATIK,
    MANUELNI
};

class Menjac{
private:
    int BrojBrzina;
    TipMenjaca Tip;
public:
    Menjac(){
        Tip = AUTOMATIK;
        BrojBrzina = 5;
    }
    Menjac(TipMenjaca Tip1, int Brzina){
        BrojBrzina = Brzina;
        Tip = Tip1;
    }
    Menjac(const Menjac& m){
        BrojBrzina = m.BrojBrzina;
        Tip = m.Tip;
    }
    bool setBrojBrzina (int a){
        if (a != 5 && a != 6){
            return false;
        }
        BrojBrzina = a;
        return true;
    }
    bool setTip(TipMenjaca tip){
        if (tip != AUTOMATIK && tip != MANUELNI) {
            return false;
        }
        Tip = tip;
        return true;
    }
    TipMenjaca getTip() const {
        return Tip;
    }
    int getBrojBrzina() const {
        return BrojBrzina;
    }
    friend void ispisiMenjac(const Menjac&);
};

#endif // MEJAC_HPP_INCLUDED
