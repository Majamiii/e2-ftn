#include "kocka.hpp"

Kocka::Kocka(){
    vrednost = 1;
}
Kocka::Kocka(int i){
    vrednost = i;
}
Kocka::Kocka(const Kocka& k){
    vrednost = k.vrednost;
}

void Kocka::baci(){
    vrednost = rand() % 6 + 1;
}

int Kocka::getVrednost() const {
    return vrednost;
}
