#ifndef STUDENT_HPP_INCLUDED
#define STUDENT_HPP_INCLUDED

#include "predmet.hpp"

class Student{
private:
    Predmet predmet1, predmet2;
public:
    Student(const DinString& ime1, List<Test*> test1, const DinString& ime2, List<Test*> test2) :
        predmet1(ime1,test1), predmet2(ime2,test2) {}
    void ispis(){
        cout<<endl<<"ispis studenta:"<<endl<<"--------------";
        predmet1.ispis();
        predmet2.ispis();
        cout<<"Student je osvojio vise poena na predmetu ";
        bool prvi = predmet1.getUkupniPoeni() > predmet2.getUkupniPoeni() ? true : false;
        if(prvi){cout<<predmet1.getNaziv();}else{cout<<predmet2.getNaziv();}
    }
};

#endif // STUDENT_HPP_INCLUDED
