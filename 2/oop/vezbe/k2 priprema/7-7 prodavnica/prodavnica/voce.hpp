#ifndef VOCE_HPP_INCLUDED
#define VOCE_HPP_INCLUDED

#include "proizvod.hpp"

class Voce:public Proizvod {

protected:
    DinString zemljaPorekla;
    int rokTrajanja;
public:
    Voce(const DinString& naziv, int cena, const DinString& zemlja, int rok) :
        Proizvod(cena,naziv),zemljaPorekla(zemlja),rokTrajanja(rok) {}
    void izracunajPopust(){
        if(rokTrajanja>5){
            this->cena=(100-33.3)*0.01*(this->cena);
        }
        else if(rokTrajanja>=1){
            this->cena=(100-66.6)*0.01*(this->cena);
        }else{
            this->cena = 0;
        }
    }
    void ispisi(){
        Proizvod::ispisi();
        cout<<"Zemlja porekla: "<<zemljaPorekla<<endl;
        cout<<"Rok trajanja: jos "<<rokTrajanja<<" dana"<<endl;
    }

};

#endif // VOCE_HPP_INCLUDED
