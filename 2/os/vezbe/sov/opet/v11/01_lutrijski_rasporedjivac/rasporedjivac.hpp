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
    vector<int> svi_tiketi;
    map<int,int> id_za_tiket;
    int proces_id;
    mutex m;
    cv_tag red_procesa;

public:
    Rasporedjivac(Dijagnostika& d) : dijagnostika(d) {
        proces_id = -1;
        srand(time(0));
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
        for(int tidx=0; tidx<p.tiketi.size();tidx++){
            svi_tiketi.push_back(p.tiketi[tidx]);
            id_za_tiket[p.tiketi[tidx]] = p.id;
        }
        for(int naredba = 0; naredba<p.broj_naredbi;naredba++){
            unique_lock<mutex> l(m);

            if(proces_id == -1){
                proces_id = p.id;
            }

            dijagnostika.proces_ceka(p.id);

            while(proces_id != p.id){
                red_procesa.wait(l, p.id);
            }

            l.unlock();
            this_thread::sleep_for(milliseconds(300));
            l.lock();

            int brojac = 0;

            if(naredba+1 == p.broj_naredbi){
                for(auto it = svi_tiketi.begin();it!=svi_tiketi.end();it++){
                    int temp_id = id_za_tiket[*it];
                    if( temp_id == p.id ){
                        id_za_tiket.erase(*it);
                        svi_tiketi.erase(it);
                        it--;
                    }
                }
            }

            if(svi_tiketi.size() == 0){
                return;
            }

            int rand_tiket = svi_tiketi[rand() % svi_tiketi.size()];

            int sledeci_id = id_za_tiket[rand_tiket];

            proces_id = sledeci_id;
            red_procesa.notify(proces_id);

            dijagnostika.izvrsio_naredbu(p.id, naredba, proces_id);

            this_thread::sleep_for(milliseconds(100));
        }
	}
};

#endif // RASPOREDJIVAC_HPP_INCLUDED
