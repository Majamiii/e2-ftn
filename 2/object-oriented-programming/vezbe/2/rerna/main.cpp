#include <iostream>
#include "rerna.hpp"

using namespace std;

#define RERNA_KRAJ 7

void ispisiRernu(const Rerna& r){
    cout << "Stanje: ";
    StanjeRerne stanje = r.getTrenutnoStanje();
    switch(stanje){
        case UKLJUCENA:
            cout << "ukljucena";
            break;
        case ISKLJUCENA:
            cout<<"iskljucena";
            break;
        case POKVARENA:
            cout << "pokvarena";
            break;
    }
    cout<<endl<<endl;
    cout << "Temperatura: "<<r.getTemperatura()<<endl<<endl<<endl;
}

int meni(){
    cout<<"0 za stanje, 1 za paljenje, 2 za gasenje. 3 za popravljanje, 4 za kvarenje"<<endl;
    cout<<"5 za povecavanje temp, 6 za smanjenje temp, 7 za kraj"<<endl<<endl;
    int n;
    cin>>n;
    return n;
};

int main()
{
    Rerna r;
    int n;
    bool uspesno = 0;

    do{
        n = meni();

        switch(n){
            case 0:
                ispisiRernu(r);
                break;
            case 1:
                uspesno = r.ukljuci();
                break;
            case 2:
                uspesno = r.iskljuci();
                break;
            case 3:
                uspesno = r.popravi();
                break;
            case 4:
                uspesno = r.pokvari();
                break;
            case 5:
                uspesno = r.pojacajTemperaturu();
                break;
            case 6:
                uspesno = r.smanjiTemperaturu();
                break;
            case 7:
                cout<<"Kraaaajjj!!!"<<endl<<endl;
                break;
            default:
                cout<<"Ne postoji ta opcija"<<endl<<endl;
                break;
        }
        if (!(uspesno)){
            cout<<"Probaj opet."<<endl;
        }
    }while(n != RERNA_KRAJ);

    return 0;
}
