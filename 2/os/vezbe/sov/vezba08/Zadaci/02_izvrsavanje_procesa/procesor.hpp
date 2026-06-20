#ifndef PROCESOR_HPP_INCLUDED
#define PROCESOR_HPP_INCLUDED

#include "dijagnostika.hpp"

#include <condition_variable>

using namespace std;
using namespace chrono;

class Procesor {
private:
    Dijagnostika& dijagnostika;
    mutex m;
    bool procesor_zauzet, prekid;
    condition_variable red_procesa;
    condition_variable red_prekida;
public:
    Procesor(Dijagnostika& d) : dijagnostika(d) {
       procesor_zauzet = false;
       prekid = false;
    }

    // Pomoćna metoda koja vraća referencu na objekat Dijagnostika asociran sa ovim objektom
    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    // Metoda koju poziva nit koja simulira proces, kako bi se izvršile sve naredbe procesa.
    //
    // id           - id procesa
    // broj_naredbi - ukupan broj naredbi koje ovaj proces izvršava
    //
    // Ukoliko je procesor već zauzet i ne mogu se izvršavati naredbe procesa, potrebno je pozvati metodu dijagnostika.proces_ceka a nakon toga proces treba da pređe u stanje čekanja.
    // Kada proces uspe da zauzme procesor, pre izvršenja naredbe treba da se pozove dijagnostika.proces_izvrsava.
    // Nakon što je proces izvršio naredbu, potrebno je pozvati dijagnostika.proces_zavrsio.
    void izvrsi_proces(int id, int broj_naredbi) {
        for(int i=0; i<broj_naredbi;i++){
            unique_lock<mutex> l(m);

            while(procesor_zauzet){
                dijagnostika.proces_ceka(id);
                red_procesa.wait(l);
            }

            procesor_zauzet = true;
            dijagnostika.proces_izvrsava(id, i);

            l.unlock();
            this_thread::sleep_for(seconds(1));
            l.lock();

            dijagnostika.proces_zavrsio(id,i);
            procesor_zauzet = false;

            if(prekid)
                red_prekida.notify_one();
            else
                red_procesa.notify_one();

            l.unlock();
            this_thread::sleep_for(milliseconds(100));
        }
    }

    // Metoda koju poziva nit koja simulira obrađivač U/I prekida kako bi se inicirao i obradio prekid.
    //
    // Ukoliko je procesor već zauzet i ne može se obaviti obrađivanje prekida, potrebno je pozvati metodu dijagnostika.obradjivac_ceka a nakon toga obrađivač treba da pređe u stanje čekanja, dok se procesor ne oslobodi.
    // Kada obrađivač uspe da zauzme procesor, pre obrade prekida treba da se pozove dijagnostika.obradjivac_izvrsava.
    // Nakon što je obrađivač završio obradu, potrebno je pozvati dijagnostika.obradjivac_zavrsio.
    void prekini() {
        unique_lock<mutex> l(m);

        while(procesor_zauzet){
            dijagnostika.obradjivac_ceka();
            red_procesa.wait(l);
        }

        procesor_zauzet = true;
        dijagnostika.obradjivac_izvrsava();

        l.unlock();
        this_thread::sleep_for(milliseconds(300));
        l.lock();

        dijagnostika.obradjivac_zavrsio();
        procesor_zauzet = false;

        prekid = false;

        red_procesa.notify_one();
    }
};

#endif // PROCESOR_HPP_INCLUDED
