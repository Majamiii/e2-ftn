#ifndef RASPOREDJIVAC_HPP_INCLUDED
#define RASPOREDJIVAC_HPP_INCLUDED

#include <vector>
#include <map>
#include <mutex>
#include <condition_variable>

#include "dijagnostika.hpp"
#include "cv_tag.hpp"

using namespace std;

struct Proces {
	int id;
	int broj_naredbi;
	vector<int> tiketi;
	Proces(int i, int b, vector<int> t) : id(i), broj_naredbi(b), tiketi(t) {}
};

class Rasporedjivac {
private:
    Dijagnostika& dijagnostika;
    cv_tag red_procesa;
    map<int,int> svi_tiketi;
    int aktivni_proces;
    mutex m;

public:
    Rasporedjivac(Dijagnostika& d) : dijagnostika(d) {
        aktivni_proces = -1;
    }

    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    // Metoda koju poziva nit koja simulira izvršenje procesa, kako bi se proces izvršio
    //
    // p - struktura koja sadrži ID procesa, broj naredbi koje treba da izvrši kao i sve tikete koji pripadaju tom procesu.
    //
    // Ukoliko je procesor već zauzet i ne mogu se izvršavati naredbe procesa, potrebno je pozvati metodu dijagnostika.proces_ceka, a nakon toga proces treba da pređe u stanje čekanja.
    // Nakon što je proces izvršio naredbu, potrebno je pozvati dijagnostika.izvrsio_naredbu.
	void izvrsi(Proces p) {
        unique_lock<mutex> l(m);
        for (auto it = p.tiketi.begin(); it != p.tiketi.end(); it++) {
            svi_tiketi[*it] = p.id;     // Dodavanje tiketa u mapu svih tiketa - ključ je broj tiketa, vrednost je id procesa.
        }
        
        for(int i=0; i<p.broj_naredbi;i++){

            if (aktivni_proces == -1) {
                aktivni_proces = p.id;
            }
            while (aktivni_proces != p.id) {
                dijagnostika.proces_ceka(p.id);
                red_procesa.wait(l, p.id);
            }

            int sledeci_proces = -1;
            int sledeci_tiket = -1;

            l.unlock();
            this_thread::sleep_for(milliseconds(300));
            l.lock();

            if(i+1 == p.broj_naredbi){
   
                for (auto it = p.tiketi.begin(); it != p.tiketi.end(); it++) {
                    auto za_brisanje = svi_tiketi.find(*it);
                    svi_tiketi.erase(za_brisanje);
                }
            }
            int rand_idx;

            if(svi_tiketi.size()>0){
                rand_idx = rand() % svi_tiketi.size();
            }else{
                return;
            }
                
            
            auto it = next(svi_tiketi.begin(), rand_idx);
            sledeci_tiket = it->first;
            
            sledeci_proces = svi_tiketi[sledeci_tiket];

            aktivni_proces = sledeci_proces;
            red_procesa.notify(sledeci_proces);


            dijagnostika.izvrsio_naredbu(p.id, i, sledeci_proces);

        }
	}
};

#endif // RASPOREDJIVAC_HPP_INCLUDED
