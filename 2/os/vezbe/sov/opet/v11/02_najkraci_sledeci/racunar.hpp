#ifndef RACUNAR_HPP_INCLUDED
#define RACUNAR_HPP_INCLUDED


#include "dijagnostika.hpp"

#include <mutex>
#include <condition_variable>
#include <map>
#include <numeric>
#include <algorithm>
#include <vector>

using namespace std;
using namespace chrono;

class Racunar {
private:
    Dijagnostika& dijagnostika;
    mutex m;
    condition_variable red_procesa, red_zahteva;
    int trenutni_id;
    map<int,int> id_za_trajanje;
    vector<int> sva_trajanja;
    bool kraj;

public:
    Racunar(Dijagnostika& d) : dijagnostika(d) {
        trenutni_id = -1;
        kraj = false;
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
        unique_lock<mutex> l(m);
        
        sva_trajanja.push_back(trajanje);
        id_za_trajanje[trajanje] = id_procesa;
        
        red_zahteva.notify_one();
        

        if(trenutni_id != -1){
            dijagnostika.proces_ceka(id_procesa);
        }else{
            trenutni_id = id_procesa;
        }

        while(trenutni_id != id_procesa){
            red_procesa.wait(l);
        }

        if(kraj){
            return;
        }

        l.unlock();
        this_thread::sleep_for(milliseconds(100*trajanje));
        l.lock();

        dijagnostika.proces_zavrsio(id_procesa);

        red_zahteva.notify_one();

    }

    // Metoda koju poziva nit koja simulira raspoređivač operativnog sistema, kako bi se izabrao sledeći proces za izvršenje.
    //
    // Ukoliko još uvek ne postoji potreba da se raspoređivač aktivira, potrebno je pozvati metodu dijagnostika.rasporedjivac_ceka a nakon toga nit treba da pređe u stanje čekanja.
    // Nakon što se raspoređivač aktivirao i izabrao sledeći proces, potrebno je pozvati dijagnostika.rasporedjivac_izvrsio.
    void rasporedjuj() {
        while(true){
            unique_lock<mutex> l(m);

            if(kraj){
                return;
            }

            while(sva_trajanja.size() == 0){
                if(kraj){
                    return;
                }
                dijagnostika.rasporedjivac_ceka();
                red_zahteva.wait(l);
            }
            
            if(kraj){
                return;
            }

            int sledeci_proces = -1;

            sort(sva_trajanja.begin(), sva_trajanja.end());
            int sledece_trajanje = *sva_trajanja.begin();
            sledeci_proces = id_za_trajanje[sledece_trajanje];

            sva_trajanja.erase(sva_trajanja.begin());
            id_za_trajanje.erase(sledece_trajanje);

            trenutni_id = sledeci_proces;

            dijagnostika.rasporedjivac_izvrsio(sledeci_proces);
            red_procesa.notify_all();
        }
    }

    // Metoda koja postavlja signal za kraj izvršavanja i pokreće raspoređivač iz čekanja kako bi program mogao da se završi
    void zavrsi() {
        unique_lock<mutex> l(m);
        kraj = true;
        red_procesa.notify_all();
        red_zahteva.notify_all();
    }
};

#endif // RACUNAR_HPP_INCLUDED
