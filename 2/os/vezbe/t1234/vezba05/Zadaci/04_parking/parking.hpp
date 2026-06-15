#ifndef PARKING_HPP_INCLUDED
#define PARKING_HPP_INCLUDED

#include "automobil.hpp"

#include <condition_variable>

using namespace std;


mutex m;


class Parking {
private:
    enum Stanje {SLOBODAN, ZAUZET};
    Stanje stanje;
    Automobil& automobil;
    condition_variable slobodan;
public:
    Parking(Automobil& a) : automobil(a), stanje(SLOBODAN) {
        // Proširiti po potrebi ...
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kako bi automobil pokušao da se parkira.
    // Ako je parking zauzet, izvršenje ove metode će trajati dok se parking ne oslobodi i auto se parkira.
    //
    // rbr - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.ceka kada je parking zauzet i auto mora da čeka.
    // Potrebno je pozvati metodu automobil.parkira kada auto uspe da se parkira.
    void udji(int rbr=0) {
        // Implementirati ...
        /*
        while(true){
            unique_lock<mutex> lock(m);
            if(stanje ==SLOBODAN){
                stanje = ZAUZET;
                break;
            }
        }
            */
        unique_lock<mutex> l(m);
        while(stanje != SLOBODAN){
            slobodan.wait(l);
        }
        stanje = ZAUZET;
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kada auto izlazi sa parkinga (nakon što je bio parkiran).
    //
    // rbr - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.napusta kada auto napušta parking mesto.
    void izadji(int rbr=0) {
        // Implementirati ...
        unique_lock<mutex> l(m);
        stanje = SLOBODAN;
        slobodan.notify_one();
    }
};

#endif // PARKING_HPP_INCLUDED
