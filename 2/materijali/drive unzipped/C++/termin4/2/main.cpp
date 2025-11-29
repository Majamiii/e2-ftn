#include "phdstudent.hpp"



void predstavljanje1(Osoba o) {   //ovakav poziv ne radi virtuelno
    o.predstaviSe();
}
void predstavljanje2(const Osoba o) { //ako je fja definsana kao virtuelna onda
    o.predstaviSe();    //se poziva metoda nad onim koja je prosledjena 
}    //ako metoda nije virtuelna automatski se izvrsava ta metoda
    //   radi samo kada se radi slanje po referenci ne objekat
   //   virtualnost se nasledjuje - predstavlja mogucnost da hodamo po nasledjenim
  //   meotdama i to ih koristimo po potrebi. Zbog toga skracujemo kucanje
int main() {

    const char *s1 = "Petar";
    const char *s2 = "Petrovic";
    const char *s3 = "Jovan";
    const char *s4 = "Jovanovic";

    DinString ds1(s1), ds2(s2), ds3(s3), ds4(s4);

    Osoba os1(s1,s2), os2(ds3,ds4), os3(os2);
    Student st1(s1, s2, 1234), st2(ds1, ds2, 1234), st3(os2, 1234), st4(st2);
    PhDStudent phds1(s1, s2, 1234, 8.56), phds2(ds1, ds2, 1234, 8.56), phds3(os3, 1234, 8.77), phds4(st3, 8.77);


    cout << "Direktno predstavljanje objekata" << endl;
    cout << endl;
    cout << "Osoba: " << endl;
    os1.predstaviSe();

    cout << endl;
    cout << "Student: " << endl;
    st1.predstaviSe();

    cout << endl;
    cout << "PhDStudent: " << endl;
    phds1.predstaviSe();

    return 0;

}



/*
Apstraktne klase 
*/