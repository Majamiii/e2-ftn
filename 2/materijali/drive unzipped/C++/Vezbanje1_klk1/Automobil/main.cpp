#include <iostream>
#include "Auto.hpp"
#include "Menjac.hpp"
#include "Skoljka.hpp"

using namespace std;

void ispisiMenjac(const Menjac& MNJ)  // u klasi Menjac proglasena za prijateljsku
{

    cout << "Menjac: " << endl;
    cout << "\tBrzina = " << MNJ.BrojBrzina << endl;  // Kad nije prijateljska mora MNJ.getBrojBrzina()
    cout << "\tTip = " <<  (MNJ.Tip == AUTOMATIK ? "Automatik" : " Manuelni") << endl;
}


void ispisiSkoljku(const Skoljka& SK)  // u klasi Skoljka proglasena za prijateljsku
{
    cout << "Skoljka: " << endl;
    cout << "\tBoja = ";

    switch(SK.getBoja())  // Kad nije prijateljska mora SK.getBoja()
    {
    case PLAVA:
        cout << "Plava" << endl;
        break;
    case ZELENA:
        cout << "Zelena" << endl;
        break;
    case CRVENA:
        cout << "Crvena" << endl;
        break;
    }
}

void ispisiAutomobil(const Automobil& a)  // u klasi Automobila proglasena za prijateljsku
{
    cout << "Automobil" << endl;
    cout << "*******************" << endl;
    ispisiMenjac(a.MNJ);
    ispisiSkoljku(a.SK);
    cout<< a.Atm_speed << endl;
    cout<< a.Stanje_auta << endl;
    cout << endl;
}


int main()
{
    Menjac m1, m2(MANUELNI, 5), m3(m1);
    ispisiMenjac(m1);
    ispisiMenjac(m2);
    ispisiMenjac(m3);

    cout << endl;

    Skoljka s1, s2(CRVENA), s3(s2);
    ispisiSkoljku(s1);
    ispisiSkoljku(s2);
    ispisiSkoljku(s3);

    cout << endl;

    Automobil a1, a2(AUTOMATIK, 6, PLAVA, UGASEN, 6), a3(a2);
    a1.upali();
    a1.pokvari();
    a1.popravi();
    a1.upali();
    ispisiAutomobil(a1);
    ispisiAutomobil(a2);
    ispisiAutomobil(a3);

    a2.setBrojBrzina(4);
    ispisiAutomobil(a2);

    a2.setBrojBrzina(5);
    ispisiAutomobil(a2);

    return 0;
}
