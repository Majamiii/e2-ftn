#include "rerna.hpp"

Rerna::Rerna(){
    trenutnoStanje = ISKLJUCENA;
    temperatura = 0;
};

Rerna::Rerna(const Rerna& r){
    temperatura = r.temperatura;
    trenutnoStanje = r.trenutnoStanje;
}

int Rerna::getTemperatura() const{
    return temperatura;
};
StanjeRerne Rerna::getTrenutnoStanje() const{
    return trenutnoStanje;
};

bool Rerna::ukljuci(){
    if (trenutnoStanje == ISKLJUCENA){
        trenutnoStanje = UKLJUCENA;
        cout << "Rerna je ukljucena"<<endl;
        return 1;
    }
    else if(trenutnoStanje == POKVARENA){
        cout<<"Rerna je pokvarena i ne moze da se ukljuci"<<endl;
        return 0;
    }
    else{
        cout << "Rerna je vec ukljucena"<<endl;
        return 0;
    }
};
bool Rerna::iskljuci(){
    if (trenutnoStanje != ISKLJUCENA){
        trenutnoStanje = ISKLJUCENA;
        cout << "Rerna je iskljucena"<<endl;
        return 1;
    }
    else if(trenutnoStanje == POKVARENA){
        cout<<"Rerna je pokvarena i ne moze da se iskljuci"<<endl;
        return 0;
    }
    else{
        cout << "Rerna je vec bila iskljucena"<<endl;
        return 0;
    }
    };
bool Rerna::pokvari(){
    if (trenutnoStanje != POKVARENA){
        trenutnoStanje = POKVARENA;
        cout<<"Rerna je sada pokvarena"<<endl;
        return 1;
    }
    else{
        cout << "Rerna je vec bila pokvarena"<<endl;
        return 0;
    }
};
bool Rerna::popravi(){
    if(trenutnoStanje == POKVARENA){
        trenutnoStanje = ISKLJUCENA;
        cout << "Rerna je sada pokvarena i iskljucena."<<endl;
        return 1;
    }
    else{
        cout << "Rerna ni nije bila pokvarena."<<endl;
        return 0;
    }
};

bool Rerna::pojacajTemperaturu(){
    if (trenutnoStanje != UKLJUCENA){
        cout<<"Rerna nije ukljucena."<<endl;
        return 0;
    }
    if(temperatura == 240){
        cout<<"Nemoguce je jos povecati temperaturu."<<endl;
        return 0;
    }
    else{
        temperatura += 20;
        cout <<"Temperatura je povecana"<<endl;
        return false;
    }
};
bool Rerna::smanjiTemperaturu(){
    if (trenutnoStanje != UKLJUCENA){
        cout<<"Rerna nije ukljucena."<<endl;
        return 0;
    }
    if (temperatura == 0){
        cout << "Nemoguce je jos smanjiti temperaturu"<<endl;
        return 0;
    }
    else{
        temperatura -= 20;
        cout << "Temperatura je smanjena"<<endl;
        return 1;
    }
};
