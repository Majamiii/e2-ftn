#ifndef RASPOREDJIVAC_HPP_INCLUDED
#define RASPOREDJIVAC_HPP_INCLUDED

#include "dijagnostika.hpp"

#include <vector>
#include <condition_variable>
#include <deque>
#include <mutex>

using namespace std;
using namespace chrono;

class Red{
private:
        deque<int> procesi;
        condition_variable cv;
public:
        Red() {}

        void dodaj_u_red(unique_lock<mutex>& l, int id){
                procesi.push_back(id);
                cv.wait(l);
        }

        int izbaci_iz_reda(){
                int id = procesi.front();
                procesi.pop_front();
                cv.notify_one();
                return id;
        }

        void izbaci_posle_naredbe(int id){
                for(auto it = procesi.begin();it!=procesi.end();it++){
                        if(*it==id){
                                procesi.erase(it);
                                return;
                        }
                }
        }

        bool prazan() { return procesi.empty(); }

};

class Rasporedjivac {
private:
    Dijagnostika& dijagnostika;
    mutex m;
    int trenutni_id;
    vector<Red> redovi;
    int broj_nivoa_prioriteta;

public:
	Rasporedjivac(Dijagnostika& d, int br_nivoa_prioriteta) : dijagnostika(d), redovi(br_nivoa_prioriteta) {
                trenutni_id = -1;
                broj_nivoa_prioriteta = br_nivoa_prioriteta;
	}

	Dijagnostika& getDijagnostika() {
                return dijagnostika;
	}

    // Metoda koju poziva nit koja simulira izvršenje procesa, kako bi se proces izvršio
    //
    // id_procesa   - ID procesa
    // broj_naredbi - ukupan broj naredbi koje proces treba da izvrši
    //
    // Ukoliko je procesor već zauzet i ne mogu se izvršavati naredbe procesa, potrebno je pozvati metodu dijagnostika.proces_ceka, a nakon toga proces treba da pređe u stanje čekanja.
    // Nakon što je proces izvršio naredbu, potrebno je pozvati dijagnostika.izvrsio_naredbu.
	void izvrsi(int id_procesa, int broj_naredbi) {
                int prioritet = 0;
                for(int p=0;p<broj_naredbi; p++){

                        unique_lock<mutex> l(m);
                        if(trenutni_id==-1){
                                trenutni_id = id_procesa;
                        }
                        while(trenutni_id != id_procesa){
                                dijagnostika.proces_ceka(id_procesa);
                                redovi[prioritet].dodaj_u_red(l,id_procesa);
                        }

                        l.unlock();
                        this_thread::sleep_for(milliseconds(300));
                        l.lock();

                        redovi[prioritet].izbaci_posle_naredbe(id_procesa);

                        int sledeci_red = -1;

                        for(int i=0; i<redovi.size();i++){
                                if(!redovi[i].prazan()){
                                        sledeci_red = i;
                                        break;
                                }
                        }

                        if(sledeci_red != -1){
                                trenutni_id = redovi[sledeci_red].izbaci_iz_reda();                                
                        }else{
                                trenutni_id = -1;
                        }

                        if(prioritet<broj_nivoa_prioriteta-1){
                                prioritet++;
                        }

                        dijagnostika.izvrsio_naredbu(id_procesa, p, prioritet);

                }
                
	}
};

#endif // RASPOREDJIVAC_HPP_INCLUDED
