#include <iostream>
#include "automobil.hpp"

using namespace std;


void ispisiMenjac(const Menjac& m){
    cout << endl;
    cout << "Broj brzina menjaca: "<< m.brojBrzina<<endl;
}

int main()
{
    Menjac m;
    cout << m.getBrojBrzina() << endl;
    cout << m.setBrojBrzina(8)<<endl;
    cout<<"*****************************"<<endl;
    Skoljka s;
    switch (s.getBoja()) {
        case PLAVA:  cout<< "PLAVA";break;
        case CRVENA: cout<< "CRVENA";break;
        case ZELENA: cout<< "ZELENA";break;
    }
    cout <<endl;

    cout<<"*****************************"<<endl<<endl;

    Automobil a;
    Automobil a2(3, MANUELNI, ZELENA);
    switch (a2.getBoja()) {
        case PLAVA:  cout<< "PLAVA";break;
        case CRVENA: cout<< "CRVENA";break;
        case ZELENA: cout<< "ZELENA";break;
    }
    cout<<endl;
    cout<<"Broj brzina automobila: "<<a2.getBrojBrzina()<<endl;

    cout<<a2.setBrojBrzina(3)<<endl<<endl;

    ispisiMenjac(m);

    return 0;
}
