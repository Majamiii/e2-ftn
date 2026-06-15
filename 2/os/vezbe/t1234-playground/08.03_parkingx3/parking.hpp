#ifndef PARKING_HPP_INCLUDED
#define PARKING_HPP_INCLUDED

#include "automobil.hpp"
#include <mutex>
#include <condition_variable>

using namespace std;

class Parking {

    Automobil& automobil;
    int rbr;
    int entryPoint;
    int naredni_ulaz;
    mutex m1;
    condition_variable spot;
    bool first = true, second = true, third = true;

public:
    static int freeSpot;
    Parking(Automobil& a) : automobil(a) {
        first = true, second = true, third = true;
        naredni_ulaz = 0;
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kada on pokusava da udje na parking.
    // Metoda je blokirajuca - ukoliko nema slobodnog mesta, izvrsenje je u blokadi dok se ono ne oslobodi.
    //
    // rbr  - Redni broj automobila
    // ulaz - Ulaz na koji automobil pokusava da udje
    //
    // Potrebno je pozvati metodu automobil.ceka kada automobil ne moze da pridje parkingu i mora da ceka.
    // Potrebno je pozvati metodu automobil.zauzima kada automobil zauzme parking mesto.
    void udji(int rbr, int ulaz) {
        // Implementirati ...

        unique_lock<mutex> parking_lock(m1);

        while (true) {
            if (first && naredni_ulaz == 0 && freeSpot == 0) {
                break;
            }
            else if (second && naredni_ulaz == 1 && freeSpot == 0) {
                break;
            }
            else if (third && naredni_ulaz == 2 && freeSpot == 0) {
                break;
            }
            spot.wait(parking_lock);
        }

        if (first && ulaz == 0 && naredni_ulaz == 0) {
            automobil.zauzima(rbr);
            freeSpot--;
            first = false;
            second = true;
            third = false;
        }
        else if (second && ulaz == 1 && naredni_ulaz == 1) {
            automobil.zauzima(rbr);
            first = false;
            second = false;
            third = true;
            freeSpot--;
        }
        else if (first && ulaz == 2 && naredni_ulaz == 2) {
            automobil.zauzima(rbr);
            first = true;
            second = false;
            third = false;
            freeSpot--;
        }
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kada on napusta parking na koji je prethodno usao.
    //
    // rbr  - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.napusta kada automobil napusti parking mesto.
    void izadji(int rbr) {
        // Implementirati ...
        automobil.napusta(rbr);
        int ulaz = rbr % 3;
        int naredni_ulaz = ulaz + 1;

        if (naredni_ulaz == 3) {
            naredni_ulaz = 0;
        }

        if (naredni_ulaz == 0) {
            first = true;
            freeSpot++;
            park
            spot.notify_one();
        }
        else if (naredni_ulaz == 1) {
            second = true;
            freeSpot++;
            spot.notify_one();
        }
        else if (naredni_ulaz == 2) {
            third == true;
            freeSpot++;
            spot.notify_one();
        }
    }
};

#endif // PARKING_HPP_INCLUDED
