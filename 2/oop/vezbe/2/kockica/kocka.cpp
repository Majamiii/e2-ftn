#include "kockica.hpp"


Kockica::Kockica(){
    vrednost = 1;
};
Kockica::Kockica(int i){
    vrednost = i;
};
Kockica::Kockica(const Kockica& k){
    vrednost = k.vrednost;
};


int Kockica::getVrednost() const{
    return vrednost;
};
void Kockica::baci(){
    vrednost = 1 + rand()%6;
};
