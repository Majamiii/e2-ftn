#include <iostream>

using namespace std;

#include "osoba.hpp"
#include "Student.hpp"
#include "PhDStudent.hpp"

void predstavljanje1(Osoba o){
    o.predstaviSe();
}

void predstavljanje2(const Osoba& o){
    o.predstaviSe();
}

int main()
{
    DinString i3("Mara");
    DinString p3("Maric");
    Osoba o1, o2("Pera", "Peric"), o3(i3, p3), o4(o3);
    cout<<"OSOBA: "<<endl;
    o4.predstaviSe();

    Student s1, s2("Pera","Mitic",45), s3(o4,7);
    cout<<endl<<"STUDENT: "<<endl;
    s3.predstaviSe();

    PhDStudent ph1, ph2("doktor", "doktoric", 11, 9), ph3(s2, 123, 9.89);
    cout<<endl<<"DOKTORANT: "<<endl;
    ph3.predstaviSe();cout<<endl;

    cout<<"******************"<<endl;
    predstavljanje1(o4);
    predstavljanje1(s3);
    predstavljanje1(ph3);
    // ispisuje samo ime i prezime, i to je jer se pravi preko osobe
    // pravi se kopija osobe i u nju se pokusava staviti objekat velicine studenta
    // on trazi vise mesta a toga nema tkd ostaje mesta samo za ime i prezime

    // za prosledjivanje po ref zauzece se toliko mesta koliko objekat ima polja
    // tako je ,,kao sa adresama''


    cout<<"******************"<<endl<<endl;
    predstavljanje2(o4);
    cout<<endl;
    predstavljanje2(s3);
    cout<<endl;
    predstavljanje2(ph3);

    return 0;
}
