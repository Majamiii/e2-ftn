#ifndef PHD_HPP_INCLUDED
#define PHD_HPP_INCLUDED

#include "student.hpp"

class Phd : public Student{

protected:
    double prosek;
public:
    Phd() : Student(), prosek(0) {}
    Phd(const char* i, const char* p, int br, double pr) : Student(i,p,br), prosek(pr) {}
    Phd(DinString& i, DinString& p, int br, double pr) : Student(i,p,br), prosek(pr) {}
    Phd(const Osoba& o, int i, double pr) : Student(o,i), prosek(pr) {}
    Phd(const Student& s, double pr) : Student(s), prosek(pr) {}
    Phd(const Phd& p) : Student((Student)p), prosek(p.prosek) {}
    void predstaviSe() const{
        Student::predstaviSe();
        cout<<"Moja prosecna ocena je "<<prosek<<endl;
    }
};

#endif // PHD_HPP_INCLUDED
