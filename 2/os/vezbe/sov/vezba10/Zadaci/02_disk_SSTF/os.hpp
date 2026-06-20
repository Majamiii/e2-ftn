#ifndef OS_HPP_INCLUDED
#define OS_HPP_INCLUDED

#include "dijagnostika.hpp"

#include <condition_variable>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;
using namespace chrono;


struct Zahtev{
    bool izvrsen;
    int broj_staze;
    int broj_zeljene_staze;
    int vreme_izvrsavanja;
    int id_procesa;
    condition_variable cv_zahtev;
    Zahtev(int br) : izvrsen(false), broj_staze(br) {}
};

class OS {
private:
    Dijagnostika& dijagnostika;
    int ukupno_vreme_izvrsavanja;
    int trenutna_glava_diska;
    bool gotovo;
    mutex m;
    condition_variable cv_ui;
    vector<shared_ptr<Zahtev>> zahtevi;

public:
    OS(Dijagnostika& d, int t) : dijagnostika(d) {
        ukupno_vreme_izvrsavanja = 0;
        trenutna_glava_diska = 0;
        gotovo = false;
    }

    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    // Metoda koju poziva nit koja simulira izvršenje procesa, kako bi se uputio zahtev ka U/I uređaju
    //
    // id_procesa - ID procesa koji upućuje zahtev
    // broj_staze - broj staze diska kojoj nit želi da pristupi
    //
    // Metoda treba da formira novi zahtev i uputi ga U/I uređaju na obradu. Proces će biti blokiran dok god se ovaj zahtev ne izvrši. Pre nego što stupi u blokadu, potrebno je pozvati dijagnostika.proces_ceka.
    void uputi_UI_zahtev(int id_procesa, int broj_staze) {
        unique_lock<mutex> l(m);
        shared_ptr<Zahtev> zahtev = shared_ptr<Zahtev>(new Zahtev(trenutna_glava_diska));
        zahtev->broj_staze = broj_staze;
        zahtevi.push_back(zahtev);
        cv_ui.notify_one();

        while(!zahtev->izvrsen){
            dijagnostika.proces_ceka(id_procesa, broj_staze);
            zahtev->cv_zahtev.wait(l);
        }
    }

    // Metoda koju poziva nit koja simulira deo operativnog sistema koji upravlja diskom, kako bi se obradio jedan pristigli zahtev
    //
    // Prema uslovima zadatka, metoda treba da obradi zahtev kojim se pristupa onoj stazi koja je najbliža stazi na kojoj je trenutno glava diska
    //
    // Povratna vrednost metode treba da bude broj staze koji je obrađen.
    int obradi_zahtev() {
        unique_lock<mutex> ul(m);
        
        if(gotovo){ 
            cout<<"Ukupno vreme izvrsavanja u ms je "<<ukupno_vreme_izvrsavanja<<endl;
            ul.unlock();
            this_thread::sleep_for(seconds(1));
            return -1;
        }

        while(zahtevi.empty() && !gotovo){
            cv_ui.wait(ul);
        }

        
        int min_distanca = abs(trenutna_glava_diska - zahtevi[0]->broj_staze);

        shared_ptr<Zahtev> min_zahtev = zahtevi[0];
        int idx=0;

        for(int i=1;i<zahtevi.size();i++){
            int distanca = abs(zahtevi[i]->broj_staze - trenutna_glava_diska);
            if(distanca < min_distanca){
                min_distanca = distanca;
                min_zahtev = zahtevi[i];
                idx = i;
            }
        }

        zahtevi.erase(zahtevi.begin() + idx);

        int vreme_izvrsavanja = abs(min_zahtev->broj_staze - trenutna_glava_diska)*10;
        
        ul.unlock();
        this_thread::sleep_for(milliseconds(vreme_izvrsavanja));
        ul.lock();

        ukupno_vreme_izvrsavanja += vreme_izvrsavanja;
        trenutna_glava_diska = min_zahtev->broj_staze;

        min_zahtev->izvrsen = true;
        min_zahtev->cv_zahtev.notify_one();

        return trenutna_glava_diska;
    }

    // Metoda koja vraca sumu svih vremena potrosenih za obradu zahteva
    int dobaviUkupnoTrajanje() {
        unique_lock<mutex> l(m);
        return ukupno_vreme_izvrsavanja;
    }

    // Metoda koja postavlja signal za kraj izvršavanja i pokreće obrađivač iz čekanja kako bi program mogao da se završi
    void zavrsi() {
        unique_lock<mutex> l(m);
        gotovo = true;
        cout<<"Ukupno vreme izvrsavanja u ms je "<<ukupno_vreme_izvrsavanja<<endl;
        // ul.unlock();
        cv_ui.notify_one();
    }
};

#endif // OS_HPP_INCLUDED
