#ifndef IGRAC_HPP_INCLUDED
#define IGRAC_HPP_INCLUDED

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Igrac{
private:
    int poeni;
    int brojPartija;
public:
    Igrac(){
        poeni=0;
        brojPartija=0;
    }
    Igrac(const Igrac& i){
        poeni=i.poeni;
        brojPartija=i.brojPartija;
    }

    void dodajPoene(int p){
        poeni += p;
    }
    void odigrajPartiju(){
        brojPartija+=1;
    }
    void resetuj(){
        brojPartija=0;
        poeni=0;
    }
    void ispis() const{
        cout<<"----- IGRAC ------"<<endl;
        cout<<"Broj poena: "<<poeni<<endl;
        cout<<"Broj partija: "<<brojPartija<<endl;
        cout<<"--------------"<<endl<<endl;
    }
    int getPoeni() const {
        return poeni;
    }
    int getBrojPartija() const {
        return brojPartija;
    }
    void setPoeni(int p) {
        poeni=p;
    }
    void setBrojPartija(int br) {
        brojPartija=br;
    }

};

#endif // IGRAC_HPP_INCLUDED
