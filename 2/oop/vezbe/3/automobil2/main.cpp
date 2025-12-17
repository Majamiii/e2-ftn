#include "automobil.hpp"

void ispisiMenjac(const Menjac& m){
    cout<<endl;
    cout << "Broj brzina menjaca: "<<m.brojBrzina<<endl;
    cout << "Tip menjaca: "<<m.tip<<endl;
}

void ispisiSkoljku(const Skoljka& s){
    cout<<endl;
    cout<<"Boja skoljke: "<<s.boja<<endl;
}

void ispisiAutomobil(const Automobil& a){
    cout<<endl;
    ispisiMenjac(a.m);
    ispisiSkoljku(a.s);
    cout<<"Trenutna brzina: "<<a.brzina<<endl;
    cout<<"Stanje automobila: "<<a.ts<<endl;
}

int main()
{
    Menjac m1, m2(5,MANUELNI), m3(m1);
    ispisiMenjac(m1);
    ispisiMenjac(m2);
    ispisiMenjac(m3);
    cout<<endl;

    Skoljka s1, s2(CRVENA), s3(s2);
    ispisiSkoljku(s1);
    ispisiSkoljku(s2);
    ispisiSkoljku(s3);

    cout << endl;

    Automobil a1, a2(3, AUTOMATIK, CRVENA, U_VOZNJI, 2), a3(a2);
    ispisiAutomobil(a1);
    ispisiAutomobil(a2);
    ispisiAutomobil(a3);

    cout<<endl<<endl;
    cout << "*************" << endl;
    cout<<endl<<endl;

    if (a2.upali())
        cout << "OK";
    else
        cout << "greska";
    cout << endl ;
    ispisiAutomobil(a2);
    cout << endl << endl;

    cout << "*************" << endl;
    if (a2.ugasi())
        cout << "OK";
    else
        cout << "greska";
    cout << endl ;
    ispisiAutomobil(a2);
    cout << endl << endl;


    cout << "*************" << endl;
    a2.upali();
    a2.povecajBrzinu();
    a2.povecajBrzinu();
    a2.smanjiBrzinu();

    cout << endl ;
    ispisiAutomobil(a2);
    cout << endl << endl;

    // probamo da smanjimo ispod 0
    a2.smanjiBrzinu();
    if (a2.smanjiBrzinu())
        cout << "OK";
    else
        cout << "greska";
    cout << endl ;
    ispisiAutomobil(a2);
    cout << endl << endl;

    // probamo da povecamo iznad max (3)
    a2.povecajBrzinu();
    a2.povecajBrzinu();
    a2.povecajBrzinu();
    a2.povecajBrzinu();

    ispisiAutomobil(a2);
    cout << endl << endl;

    // probamo da popravimo ispravan
    if (a2.popravi())
        cout << "OK";
    else
        cout << "greska";
    cout << endl ;
    ispisiAutomobil(a2);
    cout << endl << endl;

    a2.pokvari();
    ispisiAutomobil(a2);

    a2.popravi();
    ispisiAutomobil(a2);

    return 0;
}
