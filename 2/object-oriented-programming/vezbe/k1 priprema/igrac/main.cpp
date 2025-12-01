#include "igra.hpp"

void ispisiIgru(const Igra& i){
    cout<<"------ IGRA ------"<<endl;
    cout<<"Stanje: ";
    switch(i.stanje){
        case NEPOZNAT_IGRAC: cout<<"Nepoznat igrac";break;
        case PROFIL_IGRACA: cout<<"Profil igrac";break;
        case IGRA_RACUNAR: cout<<"Igra protiv racunara";break;
        default: cout<<"Igra online protiv protivnika";break;
    }
    cout<<endl;
    i.player.ispis();
}

int meni(){
    int n;
    cout<<endl<<"1. Pocetna stranica"<<endl;
    cout<<"2. Profil igraca"<<endl;
    cout<<"3. Igra protiv racunara"<<endl;
    cout<<"4. Igra protiv protivnika, online"<<endl;
    cout<<endl;
    cout<<"5. Pobedi!"<<endl;
    cout<<"6. Izgubi"<<endl;
    cout<<"7. Bonus"<<endl;
    cout<<endl;
    cout<<"8. Ispisi igru"<<endl;
    cout<<"0 - kraj"<<endl<<endl;
    cin>>n;
    return n;
}

void proveri(bool uspesno){
    if (uspesno==true){
        cout<<"OK"<<endl;
    }
    else{
        cout<<"Greska"<<endl;
    }
}

int main()
{
    srand(time(NULL));

    Igrac p1;
    Igrac p2(p1);

    Igra i;

    cout<<"Hajde da se igramo!"<<endl;
    int n;
    bool b;
    do{
        n = meni();
        switch(n){
            case 1: b=i.odjaviIgraca();proveri(b);break;
            case 2: b=i.prijaviIgraca();proveri(b);break;
            case 3: b=i.pocniIgruOnline();proveri(b);break;
            case 4: b=i.pocniIgruRacunar();proveri(b);break;
            case 5: b=i.pobedi();proveri(b);break;
            case 6: b=i.izgubi();proveri(b);break;
            case 7: b=i.ostvariBonus();proveri(b);break;
            case 8: ispisiIgru(i);proveri(b);break;
            case 0: return 0;
        }
    }while(n != 0);

    return 0;
}
