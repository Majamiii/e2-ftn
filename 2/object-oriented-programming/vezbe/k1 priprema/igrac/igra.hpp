#ifndef IGRA_HPP_INCLUDED
#define IGRA_HPP_INCLUDED

#include "igrac.hpp"

#define BROJ_MIN 0
#define BROJ_MAX 10

enum trenutnoStanje {NEPOZNAT_IGRAC, PROFIL_IGRACA, IGRA_RACUNAR, IGRA_PROTIVNIK};

class Igra{
private:
    Igrac player;
    trenutnoStanje stanje;
public:
    Igra() : player(), stanje(NEPOZNAT_IGRAC) {}
    Igra(int partije, int poen, trenutnoStanje s){
        player.setBrojPartija(partije);
        player.setPoeni(poen);
        stanje = s;
    }

    bool prijaviIgraca(){
        if(stanje == NEPOZNAT_IGRAC){
            stanje = PROFIL_IGRACA;
            return true;
        }
        else{
            return false;
        }
    }
    bool odjaviIgraca(){
        if(stanje==PROFIL_IGRACA){
            stanje = NEPOZNAT_IGRAC;
            return true;
        }
        else{
            return false;
        }
    }
    bool pocniIgruRacunar(){
        if((stanje==PROFIL_IGRACA)||(stanje==IGRA_PROTIVNIK)){
            stanje=IGRA_RACUNAR;
            player.odigrajPartiju();
            return true;
        }
        else{
            return false;
        }
    }
    bool pocniIgruOnline(){
        if((stanje==PROFIL_IGRACA)||(stanje==IGRA_RACUNAR)){
            stanje=IGRA_PROTIVNIK;
            player.odigrajPartiju();
            return true;
        }
        else{
            return false;
        }
    }
    bool pobedi(){
        int dodatni;
        if(stanje == IGRA_RACUNAR){
            dodatni=1;
        }
        else if(stanje==IGRA_PROTIVNIK){
            dodatni=2;
        }
        else{
            return false;
        }

        if(player.getPoeni()+dodatni>BROJ_MAX){
            return false;
        }else{
            player.setPoeni(player.getPoeni()+dodatni);
        }

        return true;
    }
    bool izgubi(){
        int dodatni;
        if(stanje == IGRA_RACUNAR){
            dodatni=1;
        }
        else if(stanje==IGRA_PROTIVNIK){
            dodatni=2;
        }
        else{
            return false;
        }

        if(player.getPoeni()-dodatni<BROJ_MIN){
            return false;
        }else{
            player.setPoeni(player.getPoeni()-dodatni);
        }

        return true;
    }
    bool ostvariBonus(){
        if(stanje != IGRA_PROTIVNIK){
            return false;
        }

        if(player.getPoeni()>5){
            int dodatni = rand()%3+1;
            cout<<"Dobili ste dodatnih "<<dodatni<<" poena."<<endl;

            if(player.getPoeni()+dodatni > BROJ_MAX){
                player.setPoeni(BROJ_MAX);
                return true;
            }
            player.setPoeni(player.getPoeni() + dodatni);
            return true;
        }

        return false;
    }

    friend void ispisiIgru(const Igra&);

};

#endif // IGRA_HPP_INCLUDED
