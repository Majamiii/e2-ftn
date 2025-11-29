#include "artikal.hpp"

int Artikal::instanci = 0;

Artikal::Artikal(const char n[], const double c) : naziv(n), cena(c) {
    instanci ++;
}

Artikal::Artikal(const DinString& n, const double c) : naziv(n) , cena(c) {
    instanci ++;
}

Artikal::Artikal(const Artikal& a) : naziv(a.naziv), cena(a.cena) {
    instanci ++;
}

Artikal::~Artikal() {
    instanci--;
}

ostream& operator<<(ostream& os, const Artikal& a) {
    os << "--------- ARTIKAL -----------" << endl;
    os <<setw(10)<< "Naziv: " << a.naziv << endl;
    os << "Cena:_____ " << a.cena << endl;
    os << "Broj instanci:_____ " << a.instanci << endl;
    os << "--------- ************ -----------" << endl;

    return os;
}
