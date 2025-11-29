#include <iostream>
#include "voce.hpp"
#include "odeca.hpp"
#include "prodavnica.hpp"
using namespace std;

int Odeca::velika_odeca=0;

int main()
{

    Voce v1("banana", "equador", 4, 60);
    v1.ispisi();
    v1.izracunajPopust();
    cout<<"============================="<<endl<<endl;
    v1.ispisi();

    cout<<"============================="<<endl<<endl;
    Odeca m1(MAJICE, XS, "Naruto fanart Tee", 1500);
    m1.ispisi();
    m1.izracunajPopust();
    cout<<"============================="<<endl<<endl;
    m1.ispisi();

    Odeca majica1(MAJICE, XS, "Naruto FanArt", 1500), majica2(PANTALONE, XL, "MANIC TERGANIC", 1750);
    Prodavnica p1("Pull&Bear");
    p1.dodajProizvod(majica1);
    p1.dodajProizvod(majica2);
    cout<<p1<<endl;
    return 0;
}
