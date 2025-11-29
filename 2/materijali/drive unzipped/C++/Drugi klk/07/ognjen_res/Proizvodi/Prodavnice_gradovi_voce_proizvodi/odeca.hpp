#ifndef ODECA_HPP_INCLUDED
#define ODECA_HPP_INCLUDED
#include "proizvod.hpp"


enum Tip {
    MAJICE,
    PANTALONE
};

enum Velicina {
    XS,
    S,
    M,
    L,
    XL
};

class Odeca : public Proizvod{
private:
    Tip tip;
    Velicina velicina;

    static int velika_odeca;

public:
    Odeca(Tip tt, Velicina vv, const DinString& n, int c): Proizvod(n, c), tip(tt), velicina(vv){
       if (velicina == XL || velicina == L) velika_odeca ++;
    };

    ~Odeca(){
        if (velicina == XL || velicina == L) velika_odeca --;
    }

    void izracunajPopust(){
       double popust = 0.6;
       if (velicina != XS && tip == MAJICE) {
            popust = 0.5;
       } else if (tip == PANTALONE) {
            popust = 0.33;
       }
       cena -= cena*popust;
    }

    void ispisi(){
        Proizvod::ispisi();
        cout << "Velicina:";
        switch(velicina) {
        case XS:
            cout<<"XS"<<endl; break;
        case S:
            cout<<"S"<<endl; break;
        case M:
            cout<<"M"<<endl; break;
        case L:
            cout<<"L"<<endl; break;
        case XL:
            cout<<"XL"<<endl; break;
        }
        cout << "Tip:";
        switch(tip) {
        case MAJICE:
            cout<<"Majica"<<endl; break;
        case PANTALONE:
            cout<<"Pantalone"<<endl; break;
        }
    }
};

#endif // ODECA_HPP_INCLUDED
