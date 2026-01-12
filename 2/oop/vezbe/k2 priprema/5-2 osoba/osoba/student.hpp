#ifndef STUDENT_HPP_INCLUDED
#define STUDENT_HPP_INCLUDED

#include "osoba.hpp"

/*
Napisati klasu Student koja nasleđuje klasu Osoba. Klasa sadrži dodatno polje
brojIndeksa (int). U klasi implementirati:
- Student()
- Student(const char*, const char*, int)
- Student(const DinString&, const DinString&, int)
- Student(const Osoba&, int)
- Student(const Student&)
- Redefinisan metod predstaviSe() - dopisuje i broj indeksa
*/

class Student : public Osoba {

protected:
    int brIdx;

public:
    Student() : Osoba(), brIdx(0) {}
    Student(const char* ime, const char* prezime, int br) : Osoba(ime, prezime), brIdx(br) {}
    Student(DinString& ime, DinString& prezime, int br) : Osoba(ime, prezime), brIdx(br) {}
    Student(const Osoba& o, int br) : Osoba(o), brIdx(br) {}
    Student (const Student& s) : Osoba((Osoba)s), brIdx(s.brIdx) {}
/*
    void predstaviSe() const {
        cout<<endl<<"Ja sam "<<ime<<" "<<prezime<<endl;
        cout<<"Broj mog indeksa je "<<brIdx<<endl;
    }
*/
    void predstaviSe() const{
        Osoba::predstaviSe();
        cout<<"Broj mog indeksa je "<<brIdx<<endl;
    }
};

#endif // STUDENT_HPP_INCLUDED
