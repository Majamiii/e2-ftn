#include <iostream>
#include "Semaphore.hpp"

using namespace std;

void printSemaphore(const Semaphore& s) {
    cout<<"*** Stanje semafora: ";
    switch (s.getState()) {
    case sON:
        cout<<"sON"<<endl;
        break;
    case sOFF:
        cout<<"sOFF"<<endl;
        break;
    case sOUT:
        cout<<"sOUT"<<endl;
        break;
    case sBLINK:
        cout<<"sBLINK"<<endl;
        break;
    }

    cout<<"*** Boja: ";
    switch(s.getLight()) {
    case cNONE:
        cout<<"cNONE"<<endl;
        break;
    case cBLINK:
        cout<<"cBLINK"<<endl;
        break;
    case cRED:
        cout<<"cRED"<<endl;
        break;
    case cYELLOW:
        cout<<"cYELLOW"<<endl;
        break;
    case cYELLOWRED:
        cout<<"cYELLOWRED"<<endl;
        break;
    case cGREEN:
        cout<<"cGREEN"<<endl;
        break;
    }
}

char meni() {
    char odg;
    do{
        cout<<"Izaberite operaciju: "<<endl;
        cout<<"1. Ukljuci semafor"<<endl;
        cout<<"2. Iskljuci semafor"<<endl;
        cout<<"3. Ukljuci treptece zuto"<<endl;
        cout<<"4. Pokvari semafor"<<endl;
        cout<<"5. Popravi semafor"<<endl;
        cout<<"6. Promeni boju"<<endl;
        cout<<"7. Kraj rada"<<endl;
        cin>>odg;
    }
    while(odg<'1'||odg>'7');
    return odg;
}

int main() {
    Semaphore s;
    char ch;

    do {
        ch = meni();
        switch(ch){
        case '1':
            if(s.turnON()){
                cout<<"Operacija izvrsena"<<endl;
            }
            else {
                cout<<"Operacija nije izvrsena"<<endl;
            }
            printSemaphore(s);
            break;
        case '2':
            if(s.turnOFF()){
                cout<<"Operacija izvrsena"<<endl;
            }
            else {
                cout<<"Operacija nije izvrsena"<<endl;
            }
            printSemaphore(s);
            break;
        case '3':
            if(s.turnBLINK()){
                cout<<"Operacija izvrsena"<<endl;
            }
            else {
                cout<<"Operacija nije izvrsena"<<endl;
            }
            printSemaphore(s);
            break;
        case '4':
            if(s.turnOUT()) {
                cout<<"Operacija izvrsena"<<endl;
            }
            else {
                cout<<"Operacija nije izvrsena"<<endl;
            }
            printSemaphore(s);
            break;
        case '5':
            if(s.repair()){
                cout<<"Operacija izvrsena"<<endl;
            }
            else {
                cout<<"Operacija nije izvrsena"<<endl;
            }
            printSemaphore(s);
            break;
        case '6':
            if(s.changeCOLOUR()){
                cout<<"Operacija izvrsena"<<endl;
            }
            else {
                cout<<"Operacija nije izvrsena"<<endl;
            }
                printSemaphore(s);
                break;
        }
    } while(ch!='7');
    return 0;
}1
