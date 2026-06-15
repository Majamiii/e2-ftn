#ifndef PARKING_HPP_INCLUDED
#define PARKING_HPP_INCLUDED

#include <mutex>
#include <condition_variable>

#include "automobil.hpp"

using namespace std;

class Parking {
private:
    Automobil& automobil;
    const int cap;
    int broj_slobodnih;
    condition_variable slobodan;
    mutex m;
public:
    Parking(Automobil& a, int kapacitet) : automobil(a), cap(kapacitet), broj_slobodnih(kapacitet) {
        // Proširiti po potrebi ...
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kako bi automobil pokušao da se parkira.
    // Ako je parking zauzet, izvršenje ove metode će trajati dok se parking ne oslobodi i auto se parkira.
    //
    // rbr - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.ceka kada je parking zauzet i auto ne može da se parkira.
    // Potrebno je pozvati metodu automobil.parkira kada auto uspe da se parkira.
    void udji(int rbr) {
        // Implementirati ...
        unique_lock<mutex> l(m);

        while(broj_slobodnih <= 0){
            automobil.ceka(rbr);
            slobodan.wait(l);
        }
        broj_slobodnih -= 1;

        automobil.parkira(rbr);
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kada auto izlazi sa parkinga (nakon što je bio parkiran).
    //
    // rbr - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.napusta kada auto napušta parking mesto.
    void izadji(int rbr) {
        // Implementirati ...
        unique_lock<mutex> l(m);
        automobil.napusta(rbr);

        broj_slobodnih += 1;

        slobodan.notify_one();
    }
};

#endif // PARKING_HPP_INCLUDED
