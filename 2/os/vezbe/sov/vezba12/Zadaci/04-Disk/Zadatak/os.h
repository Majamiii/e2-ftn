#ifndef OS_H_INCLUDED
#define OS_H_INCLUDED

#include "dijagnostika.h"

#include <vector>
#include <condition_variable>
#include <mutex>
#include <map>
#include <algorithm>
#include <numeric>

using namespace std;
using namespace chrono;

struct UI_zahtev{
    condition_variable cv;
    bool obradjen;
    int id;
    UI_zahtev(int i) : id(i), obradjen(false) {}
};

class OS {
private:
    Dijagnostika& dijagnostika;
    bool smer_navise;
    mutex m;
    int pozicija;
    vector<int> sve_pozicije;
    map<int,shared_ptr<UI_zahtev>> zahtev_za_poziciju;
    condition_variable ui_zahtev;

public:
    OS(Dijagnostika& d, int t, bool kvs) : dijagnostika(d) {
        smer_navise = true;
        pozicija = t;
        cout<<"na pocetku je glava diska na stazi "<<t<<endl<<endl;
    }

    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    // Metoda koju poziva nit koja simulira izvršenje procesa, kako bi se uputio zahtev ka U/I uređaju
    //
    // id_procesa - ID procesa koji upućuje zahtev
    // broj_staze - broj staze diska kojoj nit želi da pristupi
    //
    // Metoda treba da formira novi zahtev i uputi ga U/I uređaju na obradu. Proces će biti blokiran dok god se ovaj
    // zahtev ne izvrši. Pre nego što stupi u blokadu, potrebno je pozvati dijagnostika.proces_ceka.
    void uputi_UI_zahtev(int id_procesa, int broj_staze) {
        unique_lock<mutex> l(m);

        sve_pozicije.push_back(broj_staze);
        shared_ptr<UI_zahtev> zahtev = make_shared<UI_zahtev>(id_procesa);
        zahtev_za_poziciju[broj_staze] = zahtev;
        ui_zahtev.notify_one();

        if(zahtev->obradjen == false){
            dijagnostika.proces_ceka(id_procesa, broj_staze);
        }
        
        while(zahtev->obradjen == false){           
            zahtev->cv.wait(l);
        }
    }

    // Metoda koju poziva nit koja simulira deo operativnog sistema koji upravlja diskom, kako bi se obradio jedan pristigli zahtev
    //
    // Prema uslovima zadatka, metoda treba da obradi najblizi zahtev koji je u smeru kretanja glave
    //
    // Povratna vrednost metode treba da bude broj staze koji je obrađen.
    int obradi_zahtev() {
        unique_lock<mutex> l(m);

        while(sve_pozicije.empty()){
            return -1;
        }
        
        sort(sve_pozicije.begin(), sve_pozicije.end());
        
        int sledeca_pozicija = -1;
        int indeks_za_brisanje = -1;
        
        for(int i = 0; i < sve_pozicije.size(); i++){
            if(sve_pozicije[i] >= pozicija){
                if(smer_navise){
                    sledeca_pozicija = sve_pozicije[i];
                } else {
                    sledeca_pozicija = sve_pozicije[(i - 1 + sve_pozicije.size()) % sve_pozicije.size()];
                }
                
                indeks_za_brisanje = (smer_navise) ? i : (i - 1 + sve_pozicije.size()) % sve_pozicije.size();
                break;
            }
        }
        
        if(sledeca_pozicija == -1){
            if(smer_navise){
                indeks_za_brisanje = 0;
            }else{
                indeks_za_brisanje = sve_pozicije.size()-1;
            }
            sledeca_pozicija = sve_pozicije[indeks_za_brisanje];
        }

        shared_ptr<UI_zahtev> zahtev = zahtev_za_poziciju[sledeca_pozicija];

        sve_pozicije.erase(sve_pozicije.begin() + indeks_za_brisanje);
        zahtev_za_poziciju.erase(sledeca_pozicija);
        
        l.unlock();
        this_thread::sleep_for(milliseconds(300));
        l.lock();

        pozicija = sledeca_pozicija;
        
        zahtev->obradjen = true;
        zahtev->cv.notify_one();
        
        return pozicija;
    }
};

#endif // OS_H_INCLUDED

