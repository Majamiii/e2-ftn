#ifndef PRODAVNICA_HPP_INCLUDED
#define PRODAVNICA_HPP_INCLUDED

#include "proizvod.hpp"

class Prodavnica{
private:
    DinString naziv;
    List<Proizvod*> proizvodi;
public:
    Prodavnica(const DinString& nnaziv) : naziv(nnaziv) {}

    bool dodajProizvod(Proizvod& p){
        Proizvod* temp;
        bool postoji=false;
        for(int i=1;i<=proizvodi.size();i++){
            proizvodi.read(i,temp);
            if(temp->getNaziv() == p.getNaziv()){
                return false;
            }
        }
        if(!postoji){
            return proizvodi.add(1,&p);
        }
        return false;
    }
    void obrisiProizvod(const DinString& ime){
        Proizvod* temp;
        for(int i=1;i<=proizvodi.size();i++){
            proizvodi.read(i,temp);
            if(temp->getNaziv() == ime){
                proizvodi.remove(i);
                break;
            }
        }
    }
    void obrisiProizvod(int i){
        proizvodi.remove(i);
    }
    void akcija(){
        Proizvod* temp;
        for(int i=1;i<=proizvodi.size();i++){
            proizvodi.read(i,temp);
            temp -> izracunajPopust();
        }
    }
    void ispisi(){
        cout<<endl<<"------------------------"<<endl<<"Ime prodavnice: "<<naziv<<endl<<"------------------------";
        Proizvod* temp;
        for(int i=1;i<=proizvodi.size();i++){
            cout<<endl;
            proizvodi.read(i,temp);
            temp -> ispisi();
        }
        cout<<"-------------------------"<<endl;
    }
};

#endif // PRODAVNICA_HPP_INCLUDED
