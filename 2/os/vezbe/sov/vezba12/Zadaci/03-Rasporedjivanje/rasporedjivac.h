#ifndef RASPOREDJIVAC_H_INCLUDED
#define RASPOREDJIVAC_H_INCLUDED

#include <mutex>
#include <condition_variable>
#include <map>

#include "dijagnostika.h"

using namespace chrono;
using namespace std;

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
    condition_variable red_procesi;
    int proces_id;
    int ukupno_odsecaka;
    vector<int> raspodela;  // ima toliko el koliko ima odsecaka i toliko el ima vrednost id koliko taj proces ima odsecaka

public:
    Rasporedjivac(Dijagnostika& d) : dijagnostika(d) {
        proces_id = -1;
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
        srand(time(0));
        unique_lock<mutex> l(m);
        ukupno_odsecaka += p.broj_odsecaka;

        for(int i=0;i<p.broj_odsecaka;i++){
            raspodela.push_back(p.id);
        }

        for(int i=0; i<p.broj_naredbi;i++){

            if(proces_id == -1){
                proces_id = p.id;
            }

            while(proces_id != p.id){
                dijagnostika.proces_ceka(p.id);
                red_procesi.wait(l);
            }

            l.unlock();
            this_thread::sleep_for(milliseconds(300));
            l.lock();

            proces_id = -1;

            if(i+1==p.broj_naredbi){
                for(auto it=raspodela.begin();it!=raspodela.end();it++){
                    if(*it == p.id){
                        raspodela.erase(it);
                        it--;
                    }
                }
                ukupno_odsecaka -= p.broj_odsecaka;
            }

            int random_broj;
            if(ukupno_odsecaka>0){
                random_broj = rand() % ukupno_odsecaka;
                proces_id = raspodela[random_broj];
            }else{
                random_broj = -1;
            }

            if(proces_id == -1){
                return;
            }

            dijagnostika.izvrsio_naredbu(p.id, i, proces_id);
            red_procesi.notify_all();

        }

	}
};

#endif // RASPOREDJIVAC_H_INCLUDED