#ifndef RASPOREDJIVAC_HPP_INCLUDED
#define RASPOREDJIVAC_HPP_INCLUDED

#include "dijagnostika.hpp"
#include "cv_hrono.hpp"

#include <deque>
#include <map>
#include <vector>

using namespace std;
using namespace chrono;

class Red {
public:
    deque<int> svi_procesi_za_red;
    cv_hrono red_po_prioritetu;

    // metode

    int izbaci_iz_reda(){
        int p = svi_procesi_za_red.front();
        svi_procesi_za_red.pop_front();
        red_po_prioritetu.notify_one();
        return p;
    }

    void ubaci_u_red(unique_lock<mutex> &l, int p){
        svi_procesi_za_red.push_back(p);
        red_po_prioritetu.wait(l);
    }

    bool prazan(){
        return svi_procesi_za_red.empty();
    }
};

class Rasporedjivac {
private:
    mutex m;
    Dijagnostika& dijagnostika;
    vector<Red> svi_redovi;
    int trenutni_proces;
public:
    Rasporedjivac(Dijagnostika& d, int broj_nivoa_prioriteta) : dijagnostika(d), svi_redovi(broj_nivoa_prioriteta) {
        trenutni_proces = -1;
    }

    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    // Metoda koju poziva nit koja simulira izvršenje procesa, kako bi se proces izvršio
    //
    // id_procesa   - ID procesa
    // broj_naredbi - ukupan broj naredbi koje proces treba da izvrši
    // prioritet    - prioritet procesa
    //
    // Ukoliko je procesor već zauzet i ne mogu se izvršavati naredbe procesa, potrebno je pozvati metodu dijagnostika.proces_ceka, a nakon toga proces treba da pređe u stanje čekanja.
    // Nakon što je proces izvršio naredbu, potrebno je pozvati dijagnostika.izvrsio_naredbu.
	void izvrsi(int id_procesa, int broj_naredbi, int prioritet) {
        for(int naredba = 0; naredba<broj_naredbi; naredba++){
            unique_lock<mutex> l(m);
            
            if(trenutni_proces == -1 ){
                trenutni_proces = id_procesa;
            }
            
            while (trenutni_proces != id_procesa) {
                // dijagnostika.proces_ceka(id_procesa);
                svi_redovi[prioritet].ubaci_u_red(l, id_procesa);
            }

            l.unlock();
            this_thread::sleep_for(milliseconds(300));
            l.lock();

            int sledeci_prioritet = -1;
            for (int i = 0; i < svi_redovi.size(); i++) {
                if (!svi_redovi[i].prazan()) {
                    sledeci_prioritet = i;
                    break;
                }
            }

            if(sledeci_prioritet != -1){
                if (sledeci_prioritet <= prioritet || naredba == broj_naredbi - 1) {
                    trenutni_proces = svi_redovi[sledeci_prioritet].izbaci_iz_reda();
                }
            }else{
                trenutni_proces = -1;
            }

            dijagnostika.izvrsio_naredbu(id_procesa,naredba);

            this_thread::sleep_for(milliseconds(100));

        }
        
	}
};

#endif // RASPOREDJIVAC_HPP_INCLUDED
