#include "machine.hpp"

#define KORAK 20

Machine::Machine(){
    currentState = sC;
    vrednost = 80;
};

bool Machine::MetodaX(){
    if ((currentState == sB)||(currentState == sC)){
        currentState = sA;
        cout << "Izvrsena je MetodaX"<<endl;
        return 1;
    }
    else {
        cout << "Metoda X ne moze da se izvrsi"<<endl;
        return 0;
    }
};
bool Machine::MetodaY(){
    if ((currentState == sB)||(currentState == sD)){
        currentState = sC;
        cout << "Izvrsena je Metoda Y"<<endl;
        return 1;
    }
    else {
        cout << "Metoda Y ne moze da se izvrsi"<<endl;
        return 0;
    }
}
bool Machine::MetodaZ(){
    if (currentState == sA){
        currentState = sB;
        vrednost = 0;
        cout << "Izvrsena je Metoda Z"<<endl;
        return 1;
    }
    else{
        cout << "Metoda Z ne moze da se izvrsi"<<endl;
        return 0;
    }
};
bool Machine::MetodaW(){
    if (currentState == sA){
        currentState = sD;
        vrednost = 0;
        cout << "Izvrsena je Metoda W"<<endl;
        return 1;
    }
    else{
        cout << "Metoda W ne moze da se izvrsi"<<endl;
        return 0;
    }
};

bool Machine::plus(){
    if (currentState == sA){
            if(vrednost+KORAK > 80){
                cout << "Masina ne moze vise da poveca vrednost."<<endl;
                return 0;
            }
            else{
                vrednost += KORAK;
                cout << "Vrednost je povecana za 1 korak"<<endl;
                return 1;
            }
    }
    else {
        cout <<"Masina nije u stanju sA i ne moze da menja vrednost."<<endl;
        return 0;
    }
};
bool Machine::minus()    {
    if (currentState == sA){
            if(vrednost-KORAK < 0){
                cout << "Masina ne moze vise da smanji vrednost."<<endl;
                return 0;
            }
            else{
                vrednost -= KORAK;
                cout << "Vrednost je povecana za 1 korak"<<endl;
                return 1;
            }
    }
    else {
        cout <<"Masina nije u stanju sA i ne moze da menja vrednost."<<endl;
        return 0;
    }
};
MachineState Machine::getCurrentState() const{
    return currentState;
}

int Machine::getValue() const{
    return vrednost;
}
