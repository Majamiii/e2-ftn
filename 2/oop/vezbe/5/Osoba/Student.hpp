#ifndef STUDENT_HPP_INCLUDED
#define STUDENT_HPP_INCLUDED

class Student: public Osoba{
private:
    int brojIndeksa;
public:
    Student():Osoba(), brojIndeksa(0) {}
    Student(const char* i, const char* p, int bi):Osoba(i,p),brojIndeksa(bi) {}
    Student(const DinString& i, const DinString& p, int bi):Osoba(i,p),brojIndeksa(bi) {}
    ///
    Student(const Osoba& o, int bi): Osoba(o), brojIndeksa(bi) {}
    Student(const Student& s):Osoba((Osoba)s), brojIndeksa() {} //castovanje - uzeli smo samo osoba deo studenta

    void predstaviSe()const{
        //cout<<"Ja sam student "<<ime<<" "<<prezime<<" i broj mog indeksa je: "<<brojIndeksa<<endl<<endl;
        Osoba::predstaviSe();
        cout<<"Broj mog indeksa je "<<brojIndeksa<<endl;
    }
};

#endif // STUDENT_HPP_INCLUDED
