#ifndef ODECA_HPP_INCLUDED
#define ODECA_HPP_INCLUDED

#include "proizvod.hpp"

enum velicina{XS,S,M,L,XL};
enum tip{MAJICA, PANTALONE};

class Odeca:public Proizvod{
private:
    velicina vel;
    tip garderoba;
    static int brojVelike;
public:
    Odeca(int c, const DinString& n, velicina v, tip g) : Proizvod(c,n), vel(v),garderoba(g) {
        if ((vel==L)or(vel==XL)) {brojVelike++;}
    }
    void izracunajPopust(){
        if(garderoba == MAJICA){
            switch (vel) {
                case XS:
                    this->cena=(100-60)*0.01*(this->cena);break;
                default:
                    this->cena=(100-50)*0.01*(this->cena);break;
            }
        }else{
            this->cena=0.666* (this->cena);     // pantalone
        }
    }
    void ispisi(){
        Proizvod::ispisi();
        cout<<"Velicina: ";
        switch(vel){
        case XS:
            cout<<"XS";break;
        case S:
            cout<<"S";break;
        case M:
            cout<<"M";break;
        case L:
            cout<<"L";break;
        case XL:
            cout<<"XL";break;
        }
        cout<<endl<<"Tip: ";
        if(garderoba==MAJICA){
            cout<<"majica"<<endl;
        }else{
            cout<<"pantalone"<<endl;
        }
    }
};

#endif // ODECA_HPP_INCLUDED
