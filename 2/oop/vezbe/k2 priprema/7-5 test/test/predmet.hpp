#ifndef PREDMET_HPP_INCLUDED
#define PREDMET_HPP_INCLUDED

#include "kolokvijum.hpp"

class Predmet{
protected:
    DinString naziv;
    List<Test*> testovi;
public:
    Predmet() : naziv("") {}
    Predmet(const DinString& ime, List<Test*> test) : naziv(ime),testovi(test) {}
    Predmet(const Predmet& p) : naziv(p.naziv),testovi(p.testovi) {}

    void dodajTest(Test* t){
        testovi.add(testovi.size()+1,t);
    }

    bool polozio(){
        int ukPoeni=0;
        Test* t1;
        for(int i=1;i<=testovi.size();i++){
            testovi.read(i, t1);
            if( t1->polozio() ){
                ukPoeni += t1->getPoeni();
            }else{
            return false;}
        }
        if(ukPoeni > 55){
            return true;
        }else{return false;}
    }

    int getUkupniPoeni(){
        int ukPoeni=0;
        Test* t1;
        for(int i=1;i<=testovi.size();i++){
            testovi.read(i, t1);
            ukPoeni += t1->getPoeni();
        }
        return ukPoeni;
    }

    DinString getNaziv(){
        return naziv;}
    /*
        void ispis() - ispisuje ime predmeta i informacije o svim testovima (naziv i
broj osvojenih poena).*/
    void ispis(){
        cout<<"Ime predmeta: "<<naziv<<endl;
        cout<<"Informacije o predmetu: "<<endl;
        Test* t1;
        for(int i=1;i<=testovi.size();i++){
            testovi.read(i, t1);
            t1 ->ispis();
        }
    }

};

#endif // PREDMET_HPP_INCLUDED
