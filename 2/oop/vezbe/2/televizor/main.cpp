#include "televizor.hpp"

void ispis(const Televizor& tv){
    int zvuk = tv.getZvuk();
    int kanal = tv.getKanal();
    StanjeTelevizora stanje = tv.getStanje();

    cout << endl << "Jacina zvuka: "<<zvuk;
    cout << endl << "Kanal: "<<kanal<<endl;
    cout << "Stanje televizora: ";
    switch(stanje){
        case UKLJUCEN:
            cout<<"ukljucen"<<endl;
            break;
        case ISKLJUCEN:
            cout<<"iskljucen"<<endl;
            break;
        case POKVAREN:
            cout<<"pokvaren"<<endl;
            break;
        default:
            cout<<"nedefinisano"<<endl;
            break;
    }
}

int main()
{
    Televizor tv;
    ispis(tv);
    tv.smanjiZvuk();
    ispis(tv);
    tv.ukljuci();
    tv.smanjiZvuk();
    ispis(tv);
    tv.pojacajZvuk();
    tv.pojacajZvuk();
    ispis(tv);
    tv.pokvari();
    ispis(tv);
    tv.sledeciKanal();
    ispis(tv);
    tv.popravi();
    ispis(tv);
    return 0;
}
