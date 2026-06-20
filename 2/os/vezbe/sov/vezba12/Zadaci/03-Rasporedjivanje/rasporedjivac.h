#ifndef RASPOREDJIVAC_H_INCLUDED
#define RASPOREDJIVAC_H_INCLUDED

#include <mutex>
#include <condition_variable>
#include <map>

#include "cv_tag.h"
#include "dijagnostika.h"

using namespace std;
using namespace chrono;

struct Proces {
	int id;
	int broj_naredbi;
	int broj_odsecaka;
	Proces(int i, int b, int o) : id(i), broj_naredbi(b), broj_odsecaka(o) {}
};

class Rasporedjivac {
private:
    Dijagnostika& dijagnostika;
    mutex m;
    cv_tag cv;
    map<int,int> odsecak_procesa;
    int aktivni_proces;
    int ukupno_odsecaka;

public:
    Rasporedjivac(Dijagnostika& d) : dijagnostika(d) {
        aktivni_proces = -1;
        ukupno_odsecaka = 0;
    }

    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    // Metoda koju poziva nit koja simulira izvršenje procesa, kako bi se proces izvršio
    //
    // p - struktura koja sadrži ID procesa, broj naredbi koje treba da izvrši kao i broj odsecaka.
    //
    // Ukoliko je procesor već zauzet i ne mogu se izvršavati naredbe procesa, potrebno je pozvati metodu dijagnostika.proces_ceka a nakon toga proces treba da pređe u stanje čekanja.
    // Nakon što je proces izvršio naredbu, potrebno je pozvati dijagnostika.izvrsio_naredbu.
	void izvrsi(Proces p) {
        ukupno_odsecaka += p.broj_odsecaka;
        odsecak_procesa[p.id] = p.broj_odsecaka;
        for(int naredba = 0; naredba<p.broj_naredbi; naredba++){
            unique_lock<mutex> l(m);

            if(aktivni_proces==-1){
                aktivni_proces = p.id;
            }
            while(aktivni_proces != p.id){
                dijagnostika.proces_ceka(p.id);
                cv.wait(l, p.id);
            }

            l.unlock();
            this_thread::sleep_for(milliseconds(300));
            l.lock();

            if(naredba+1 == p.broj_naredbi){
                odsecak_procesa.erase(p.id);
                ukupno_odsecaka -= p.broj_odsecaka;
            }

            int sledeci_proces = -1;

            map<int,int> kumulativni_odsecci;
            int i=0;

            if(odsecak_procesa.size()==0){
                dijagnostika.izvrsio_naredbu(p.id, naredba, sledeci_proces);
                aktivni_proces = -1;
                break;
            }

            for(auto proces = odsecak_procesa.begin(); proces != odsecak_procesa.end(); proces++){
                int tren_id = proces->first;
                for(int j = 0; j< odsecak_procesa[tren_id];j++){
                    kumulativni_odsecci[i] = tren_id;
                    i++;
                }
            }

            int idx = rand() % kumulativni_odsecci.size();
            sledeci_proces = kumulativni_odsecci[idx];

            dijagnostika.izvrsio_naredbu(p.id, naredba, sledeci_proces);

            aktivni_proces = sledeci_proces;
            cv.notify(aktivni_proces);
            this_thread::sleep_for(milliseconds(100));
        }
	}
};

#endif // RASPOREDJIVAC_H_INCLUDED
