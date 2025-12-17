#ifndef AUTOMOBIL_HPP_INCLUDED
#define AUTOMOBIL_HPP_INCLUDED

#include <iostream>

#include "skoljka.hpp"
#include "menjac.hpp"

enum stanje {UGASEN, U_VOZNJI, POKVAREN};

class Automobil{

private:
    Menjac m;
    Skoljka s;
    stanje ts;
    int brzina;
public:
    Automobil() : m(), s() {
        ts=UGASEN;
        brzina=0;
    }
    Automobil(int bbr, TipMenjaca tipmm, bojaSkoljke bss, stanje tss, int bb) :
        m(bbr,tipmm), s(bss) {
             ts=tss;
             brzina=bb;
        }
    Automobil(const Automobil& a) : m(a.m), s(a.s) {
        ts=a.ts;
        brzina=a.brzina;
    }

    bool upali(){
        if(ts == UGASEN){
            ts = U_VOZNJI;
            cout<<"Automobil je sada upaljen."<<endl;
            return 1;
        }
        else if(ts==U_VOZNJI){
            cout<<"Automobil je vec bio u voznji."<<endl;
            return 0;
        }
        else {
            cout << "Automobil je pokvaren, nemoguce ga je upaliti."<<endl;
            return 0;
        }
    }

    bool ugasi(){
        if(ts == U_VOZNJI){
            ts = UGASEN;
            brzina = 0;
            cout<<"Automobil je sada ugasen."<<endl;
            return 1;
        }
        else if(ts==UGASEN){
            cout<<"Automobil je vec bio ugasen."<<endl;
            return 0;
        }
        else {
            cout << "Automobil je pokvaren, nemoguce ga je ugasiti."<<endl;
            return 0;
        }
    }
    bool pokvari(){
        if(ts != POKVAREN){
            ts = POKVAREN;
            brzina = 0;
            cout<<"Automobil je sada pokvaren."<<endl;
            return 1;
        }
        else{
            cout<<"Automobil je vec bio pokvaren."<<endl;
            return 0;
        }
    }
    bool popravi(){
        if(ts==POKVAREN){
            ugasi();
            cout<<"Automobil je sada popravljen"<<endl;
            return 1;
        }
        else{
            cout<<"Automobil ni nije bio pokvaren."<<endl;
            return 0;
        }
    }
    bool povecajBrzinu(){
        if(ts != U_VOZNJI){
            cout<<"Nemoguce povecati brzinu, automobil nije upaljen."<<endl;
            return 0;
        }
        else{
            if(brzina+1 <= m.getBrojBrzina()){
                cout<<"Brzina se povecava."<<endl;
                brzina++;
                return 1;
            }
            else{
                cout<<"Brzina ne moze vise da se poveca."<<endl;
                return 0;
            }
        }
    }
    bool smanjiBrzinu(){
        if(ts != U_VOZNJI){
            cout<<"Nemoguce smanjiti brzinu, automobil nije upaljen."<<endl;
            return 0;
        }
        else{
            if(brzina-1 > 0){
                cout<<"Brzina se smanjuje."<<endl;
                brzina--;
                return 1;
            }
            else{
                cout<<"Brzina ne moze vise da se smanji."<<endl;
                return 0;
            }
        }
    }

    friend void ispisiAutomobil(const Automobil&);

};

#endif // AUTOMOBIL_HPP_INCLUDED
