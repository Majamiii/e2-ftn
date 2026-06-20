#ifndef RASPOREDJIVAC_HPP_INCLUDED
#define RASPOREDJIVAC_HPP_INCLUDED

#include "dijagnostika.hpp"
#include <condition_variable>
#include <vector>
#include <queue>
#include <deque>

using namespace std;
using namespace chrono;

class Red{
private:
    deque<int> procesi;
    condition_variable cv;

public:
    Red() {}

    void dodaj_u_red(unique_lock<mutex> &l, int id_procesa){
        procesi.push_back(id_procesa);
        cv.wait(l);
    }

    int izbaci_iz_reda(){
        int p = procesi.front();
        procesi.pop_front();
        cv.notify_one();
        return p;
    }
    bool prazan() { return procesi.empty(); }

};

class Rasporedjivac {
private:
    Dijagnostika& dijagnostika;
    vector<Red> redovi;
    mutex m;
    int trenutni_id;

public:
    Rasporedjivac(Dijagnostika& d, int broj_nivoa_prioriteta) : dijagnostika(d), redovi(broj_nivoa_prioriteta) {
        trenutni_id = -1;
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
        for(int i=0;i<broj_naredbi;i++){
            unique_lock<mutex> l(m);

            if(trenutni_id == -1){
                trenutni_id = id_procesa;
            }

            if(trenutni_id != id_procesa){
                dijagnostika.proces_ceka(id_procesa);
                redovi[prioritet].dodaj_u_red(l,id_procesa);
            }

            l.unlock();
            this_thread::sleep_for(milliseconds(300));
            l.lock();

            int sledeci_red = -1;

            for(int j=0;j<redovi.size();j++){
                if(!redovi[j].prazan()){
                    sledeci_red = j;
                    break;
                }
            }
            
            if (sledeci_red != -1) {
                if (sledeci_red <= prioritet || i == broj_naredbi - 1) {
                    trenutni_id = redovi[sledeci_red].izbaci_iz_reda();
                }
            } else {
                trenutni_id = -1;
            }

            dijagnostika.izvrsio_naredbu(id_procesa, i);

        }
	}
};

#endif // RASPOREDJIVAC_HPP_INCLUDED
