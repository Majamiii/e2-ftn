#ifndef PHDSTUDENT_DEF
#define PHDSTUDENT_DEF

#include "student.hpp"

class PhDStudent : public Student
{
    protected:
        double prosecnaOcena;
    //konstruktori
    public:
        PhDStudent(const char* s1 = "", const char* s2 = "", int i = 0, double po = 0) : Student(s1, s2, i), prosecnaOcena(po) { }
    // nacin kojim saljemo sve podatke pojedinacno - konstruisemo od dna - ima podrazumevane vrednosti
        PhDStudent(const DinString& ds1, const DinString& ds2, int i, double po) : Student(ds1, ds2, i), prosecnaOcena(po) { }
    // koristimo podklasu dinstring za manipulisanje stringovima
        PhDStudent(const Osoba& os, int i, double po) : Student(os, i), prosecnaOcena(po) { }
    // za definisanje phd koristimo osobu as dodacima ocene i broja indeksa
        PhDStudent(const Student& s, double po) : Student(s), prosecnaOcena(po) { }
    // pdh stud je stud sa prosecnom ocenom
        PhDStudent(const PhDStudent& phds) : Student((Student)phds), prosecnaOcena(phds.prosecnaOcena) { }
    // konstrukrtor kopije
        void predstaviSe() const      //redefinicija metode
        {
            Student::predstaviSe();  //metoda iz nadklase
            cout << "Diplomirao sam sa prosecnom ocenom " << prosecnaOcena; //dodaje jos
            cout << ", a sada sam student doktorskih studija" << endl;
        }
};

#endif