#ifndef OS_H_INCLUDED
#define OS_H_INCLUDED

#include "dijagnostika.h"

#include <algorithm>
#include <numeric>
#include <condition_variable>
#include <climits>
#include <memory>
#include <vector>

using namespace std;
using namespace chrono;

struct UI_zahtev{
    bool obradjen;
    condition_variable cv;
    int zeljena_poz;
    int proces;
    UI_zahtev(bool z_obradjen = false, int poz = 0, int p = -1) : obradjen(z_obradjen), zeljena_poz(poz), proces(p) {}
};

class OS {
private:
    Dijagnostika& dijagnostika;
    mutex m;
    int pozicija;
    bool smer_navise;
    condition_variable procesi_cv, ui_cv;
    int id;
    vector<shared_ptr<UI_zahtev>> zahtevi;
public:
    OS(Dijagnostika& d, int t, bool kvs) : dijagnostika(d) {
        pozicija = t;
        smer_navise = kvs;
        id = -1;
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
        if(id==-1){
            id = id_procesa;
        }
        id = id_procesa;
        shared_ptr<UI_zahtev> zahtev = make_shared<UI_zahtev>(false, broj_staze, id_procesa);
        zahtevi.push_back(zahtev);
        ui_cv.notify_one();

        while(!zahtev->obradjen){
            dijagnostika.proces_ceka(id_procesa, broj_staze);
            zahtev->cv.wait(l);
        }

        l.unlock();
        this_thread::sleep_for(milliseconds(300));
        l.lock();

        id = -1;
        procesi_cv.notify_one();
    }

    // Metoda koju poziva nit koja simulira deo operativnog sistema koji upravlja diskom, kako bi se obradio jedan pristigli zahtev
    //
    // Prema uslovima zadatka, metoda treba da obradi najblizi zahtev koji je u smeru kretanja glave
    //
    // Povratna vrednost metode treba da bude broj staze koji je obrađen.
    int obradi_zahtev() {
        while(true){
            unique_lock<mutex> l(m);
            while(zahtevi.empty()){
                ui_cv.wait(l);
            }
    
            int min_idx = -1;
            int min_razlika = INT_MAX;
    
            // 1. pokušaj: najbliži zahtev u trenutnom smeru kretanja
            for(int i = 0; i < (int)zahtevi.size(); i++){
                int poz = zahtevi[i]->zeljena_poz;
                if(smer_navise){
                    if(poz >= pozicija && (poz - pozicija) < min_razlika){
                        min_razlika = poz - pozicija;
                        min_idx = i;
                    }
                } else {
                    if(poz <= pozicija && (pozicija - poz) < min_razlika){
                        min_razlika = pozicija - poz;
                        min_idx = i;
                    }
                }
            }
    
            // 2. ako nema nijednog zahteva u trenutnom smeru, napravi krug lepo
            if(min_idx == -1){
                pozicija =0;
                for(int i = 0; i < (int)zahtevi.size(); i++){
                    int poz = zahtevi[i]->zeljena_poz;
                    if(smer_navise){
                        if(poz >= pozicija && (poz - pozicija) < min_razlika){
                            min_razlika = poz - pozicija;
                            min_idx = i;
                        }
                    } else {
                        if(poz <= pozicija && (pozicija - poz) < min_razlika){
                            min_razlika = pozicija - poz;
                            min_idx = i;
                        }
                    }
                }
            }
    
            int obradjena_staza = zahtevi[min_idx]->zeljena_poz;
    
            zahtevi[min_idx]->obradjen = true;
            zahtevi[min_idx]->cv.notify_one();
    
            pozicija = obradjena_staza;
            procesi_cv.notify_all();
    
            zahtevi.erase(zahtevi.begin() + min_idx);

            if(zahtevi.empty()){
                return -1;
            }
    
            return obradjena_staza;
        }
    }
};

#endif // OS_H_INCLUDED


