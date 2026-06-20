#ifndef RACUNAR_HPP_INCLUDED
#define RACUNAR_HPP_INCLUDED

#include <map>
#include <mutex>
#include <condition_variable>

#include "dijagnostika.hpp"

using namespace std;
using namespace chrono;

class Racunar {
private:
    Dijagnostika& dijagnostika;
    map<int,int> procesi;   // kljuc je trajanje, vrednost je id
    bool kraj;
    bool rasporedjivac_aktivan;
    int id;
    condition_variable red_procesa;
    condition_variable cv_rasp;
    mutex m;
public:
    Racunar(Dijagnostika& d) : dijagnostika(d) {
        kraj = false;
        rasporedjivac_aktivan = false;
        id = -1;
    }

    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    // Metoda koju poziva nit koja simulira izvršenje procesa, kako bi se proces izvršio
    //
    // id_procesa   - ID procesa
    // trajanje     - trajanje procesa (izraženo u stotinama milisekundi)
    //
    // Ukoliko je procesor već zauzet i ne mogu se izvršavati naredbe procesa, potrebno je pozvati metodu dijagnostika.proces_ceka a nakon toga proces treba da pređe u stanje čekanja.
    // Nakon što se proces izvršio, potrebno je pozvati dijagnostika.proces_zavrsio.
    void izvrsi(int id_procesa, int trajanje) {
        procesi[trajanje] = id_procesa; // dodajemo odmah u mapu
        unique_lock<mutex> l(m);
        if(id == -1){
            id = id_procesa;
        }
        while(id != id_procesa){
            dijagnostika.proces_ceka(id_procesa);
            red_procesa.wait(l);
        }

        l.unlock();
        this_thread::sleep_for(milliseconds(100*trajanje));
        l.lock();

        rasporedjivac_aktivan=true;
        dijagnostika.proces_zavrsio(id_procesa);
        procesi.erase(trajanje);
        cv_rasp.notify_one();
    }

    // Metoda koju poziva nit koja simulira raspoređivač operativnog sistema, kako bi se izabrao sledeći proces za izvršenje.
    //
    // Ukoliko još uvek ne postoji potreba da se raspoređivač aktivira, potrebno je pozvati metodu dijagnostika.rasporedjivac_ceka a nakon toga nit treba da pređe u stanje čekanja.
    // Nakon što se raspoređivač aktivirao i izabrao sledeći proces, potrebno je pozvati dijagnostika.rasporedjivac_izvrsio.
    void rasporedjuj() {
        while(true){
            unique_lock<mutex> l(m);
            while(rasporedjivac_aktivan == false){
                dijagnostika.rasporedjivac_ceka();
                cv_rasp.wait(l);
            }
            if(kraj) return;
    
            int min_trajanje = procesi.begin()->first;
            int min_id = procesi.begin()->second;
            auto it2 = procesi.begin();
            for(auto it = procesi.begin(); it!=procesi.end();it++){
                if(it->first < min_trajanje){
                    it2 = it;
                }
            }
            min_trajanje = it2->first;
            min_id = it2->second;

            // auto za_brisanje = procesi.find(min_trajanje);
            // procesi.erase(za_brisanje);

            if(procesi.empty()){
                dijagnostika.rasporedjivac_izvrsio(-1);
                return;
            }else{
                dijagnostika.rasporedjivac_izvrsio(min_id);
        
                id = min_id;
                rasporedjivac_aktivan = false;
                red_procesa.notify_all();
            }

        }

    }

    // Metoda koja postavlja signal za kraj izvršavanja i pokreće raspoređivač iz čekanja kako bi program mogao da se završi
    void zavrsi() {
        unique_lock<mutex> l(m);
        kraj = true;
        cv_rasp.notify_one();
    }
};

#endif // RACUNAR_HPP_INCLUDED
