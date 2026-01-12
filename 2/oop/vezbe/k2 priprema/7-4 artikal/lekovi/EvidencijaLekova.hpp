#ifndef EVIDENCIJALEKOVA_HPP_INCLUDED
#define EVIDENCIJALEKOVA_HPP_INCLUDED

#include "lek.hpp"
#include "list.hpp"

class EvidencijaLekova{
private:
    DinString nazivApoteke, datum;
    List<Lek> listaLekova;
public:
    EvidencijaLekova() : nazivApoteke("Majateka"),datum("11.1.2026.") {}

    bool dodajLek(double jjkl, const DinString& nnaziv, double jCena, int kol){
        Lek l(jjkl, nnaziv, jCena, kol);
        return listaLekova.add(listaLekova.size()+1, l);
    }

    bool dodajLek(const Lek& l){
        return listaLekova.add(1, l);
    }

    bool ukloniLek(int indeks){
        return listaLekova.remove(indeks);
    }

    void sortirajLekove(){

        Lek l1,l2;

        for(int i=1; i<=listaLekova.size(); i++){
            for(int j=i+1;j<=listaLekova.size(); j++){
                listaLekova.read(i,l1);
                listaLekova.read(j,l2);

                if( l1.getVrednost() > l2.getVrednost() ){
                    listaLekova.remove(i);
                    listaLekova.add(i,l2);
                    listaLekova.remove(j);
                    listaLekova.add(j,l1);
                }
            }
        }
    }

    friend ostream& operator<<(ostream& o, const EvidencijaLekova& evidencija){
        o<<endl<<"*****************************"<<endl;
        o<<endl<<"Apoteka: "<<evidencija.nazivApoteke;
        o<<endl<<"Datum: "<<evidencija.datum<<endl;

        if(evidencija.listaLekova.size() < 1){
            o<<endl<<"U apoteci trenutno nema lekova."<<endl;
        }
        else{
            o<<endl<<evidencija.listaLekova<<endl;
        }
        return o;
    }

};

#endif // EVIDENCIJALEKOVA_HPP_INCLUDED
