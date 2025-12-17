#include "televizor.hpp"

#define KORAK 1

Televizor::Televizor(){
    stanje = ISKLJUCEN;
    zvuk = 0;
    kanal = 1;
};
bool Televizor::ukljuci(){
    if(stanje == ISKLJUCEN){
        stanje = UKLJUCEN;
        cout<<"TV je ukljucen."<<endl;
        return 1;
    }
    else if (stanje == POKVAREN){
        cout<<"TV je pokvaren i ne moze da se ukljuci."<<endl;
        return 0;
    }
    else{
        cout<<"TV je vec ukljucen."<<endl;
        return 0;
    }
};
bool Televizor::iskljuci(){
    if(stanje == UKLJUCEN){
        stanje = ISKLJUCEN;
        cout << "TV je iskljucen"<<endl;
        zvuk = 0;
        kanal = 1;
        return 1;
    }
    else if (stanje == POKVAREN){
        cout<<"TV je pokvaren i ne moze da se iskljuci."<<endl;
        return 0;
    }
    else{
        cout<<"TV je vec iskljucen."<<endl;
        return 0;
    }
};
bool Televizor::pokvari(){
    if(stanje == POKVAREN){
        cout <<"TV je vec pokvaren."<<endl;
        return 0;
    }
    else{
        stanje = POKVAREN;
        zvuk = 0;
        kanal = 1;
        cout<<"TV je pokvaren"<<endl;
        return 0;
    }
};
bool Televizor::popravi(){
    if(stanje = POKVAREN){
        stanje = ISKLJUCEN;
        cout<<"TV je popravljen."<<endl;
        return 1;
    }
    else{
        cout<<"TV nije bio pokvaren."<<endl;
        return 0;
    }
}
bool Televizor::pojacajZvuk(){
    if(stanje != UKLJUCEN){
        cout << "TV nije ukljucen."<<endl;
        return 0;
    }
    if(zvuk + KORAK > 20) {
        cout << "TV ne moze vise da se pojaca."<<endl;
        return 0;
    }
    else{
        zvuk += KORAK;
        cout<<"TV je pojacan."<<endl;
        return 1;
    }

}
bool Televizor::smanjiZvuk(){
        if(stanje != UKLJUCEN){
        cout << "TV nije ukljucen."<<endl;
        return 0;
    }
    if(zvuk - KORAK <0) {
        cout << "TV ne moze vise da se smanji."<<endl;
        return 0;
    }
    else{
        zvuk += KORAK;
        cout<<"TV je smanjen za korak."<<endl;
        return 1;
    }
}

bool Televizor::sledeciKanal(){
    if(stanje != UKLJUCEN){
        cout << "TV nije ukljucen."<<endl;
        return 0;
    }
    if(kanal + KORAK > 5) {
        cout << "TV nema vise kanala."<<endl;
        return 0;
    }
    else{
        kanal += KORAK;
        cout<<"TV se prebacio na sledeci kanal."<<endl;
        return 1;
    }
};
bool Televizor::prethodniKanal(){
    if(stanje != UKLJUCEN){
        cout << "TV nije ukljucen."<<endl;
        return 0;
    }
    if(kanal - KORAK < 1) {
        cout << "TV nema vise kanala."<<endl;
        return 0;
    }
    else{
        kanal += KORAK;
        cout<<"TV se prebacio na prethodni kanal."<<endl;
        return 1;
    }
};

StanjeTelevizora Televizor::getStanje() const{
    return stanje;
};
int Televizor::getZvuk() const{
    return zvuk;
};
int Televizor::getKanal() const{
    return kanal;
};
