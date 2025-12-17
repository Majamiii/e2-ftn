#include "machine.hpp"

void printInfo(const Machine& m){
    MachineState stanje = m.getCurrentState();
    int v = m.getValue();
    cout << endl << "Vrednost na masini je " << v <<endl;
    cout << "Trenutno stanje je ";
    switch(stanje){
        case sA:
            cout << "sA";
            break;
        case sB:
            cout << "sB";
            break;
        case sC:
            cout<<"sC";
            break;
        case sD:
            cout <<"sD";
            break;
        default:
            cout << "Nedefinisano";
            break;
    }
    cout<<endl<<endl;
}

int meni(){
    int n;
    cout << endl << "Meni:"<<endl;
    cout << "1. Metoda X" << endl;
    cout << "2. Metoda Y"<<endl;
    cout << "3. Metoda Z" << endl;
    cout << "4. Metoda W"<<endl;
    cout << "5. Trenutno stanje"<<endl;
    cout << "6. Plus"<<endl;
    cout << "7. Minus"<<endl;
    cout << "8. Kraj"<<endl;
    cout << endl;
    cin>>n;
    return n;
};

int main()
{
    int n;
    Machine m;
    bool uspesno;
    do{
        n = meni();
        switch(n){
            case 1:
                uspesno = m.MetodaX();
                break;
            case 2:
                uspesno = m.MetodaY();
                break;
            case 3:
                uspesno = m.MetodaZ();
                break;
            case 4:
                uspesno = m.MetodaW();
                break;
            case 5:
                printInfo(m);
                break;
            case 6:
                uspesno = m.plus();
                break;
            case 7:
                uspesno = m.minus();
                break;
            default:
                cout << "Ne postoji ta opcija"<<endl;
                cin.clear();
                break;
        }
    }while(n != 8);

    return 0;
}
