#ifndef STUDENT_HPP_INCLUDED
#define STUDENT_HPP_INCLUDED

#include "osoba.hpp"

class Student:public Osoba{
private:
    int broj;
public:
    Student() : Osoba(), broj(0) {}
    Student(const DinString& i, const DinString& p, int br) : Osoba(i,p),broj(br){}
    Student(const Student& o) : Osoba((Osoba)o), broj(o.broj) {}

    void ispis() {
        cout<<endl<<"ime: "<<ime<<endl<<"prezime: "<<prezime<<endl<<"Broj indeksa: "<<broj<<endl<<endl;
    }
};

#endif // STUDENT_HPP_INCLUDED
