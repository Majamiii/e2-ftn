#ifndef OS_HPP_INCLUDED
#define OS_HPP_INCLUDED

#include "dijagnostika.hpp"
#include "proces.hpp"

#include <condition_variable>
#include <queue>

using namespace std;
using namespace chrono;

struct UI_zahtev{
    int id;
    bool obradjen;
    condition_variable cv;
    UI_zahtev(int idd) : id(idd), obradjen(false) {}
};

class OS {
private:
    Dijagnostika& dijagnostika;
    int maks_instrukcija;
    int id_procesa;
    mutex m;
    queue<shared_ptr<UI_zahtev>> zahtevi;
    condition_variable red_procesa;
    condition_variable ui;
    default_random_engine dr;
    uniform_int_distribution<> vreme_obrade_standradne, vreme_obrade_ui;
    bool gotovo;
public:
    // d                 - Referenca na objekat Dijagnostika, koji služi za ispis stanja simulacije
    // maks_uzastopnih_i - Maksimalan dozvoljen broj uzastopnih STANDARD instrukcija, nakon kojeg obavezno sledi preključivanje
    OS(Dijagnostika& d, int maks_uzastopnih_i) : dijagnostika(d) {
        gotovo = false;
        maks_instrukcija = maks_uzastopnih_i;
        id_procesa = -1;
        dr.seed(steady_clock::now().time_since_epoch().count());
        vreme_obrade_standradne = uniform_int_distribution<>(10,50);
        vreme_obrade_ui = uniform_int_distribution<>(100,300);
    }

    // Pomoćna metoda koja vraća objekat klase Dijagnostika koji služi za ispis stanja simulacije
    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    // Metoda koju poziva nit koja simulira proces kako bi se izvršile sve instrukcije procesa.
    //
    // p - Struktura koja sadrži opis procesa (ID procesa i instrukcije koje treba izvršiti)
    //
    // Ukoliko proces ne može da se izvrši (procesor je zauzet), proces mora da se uveže u red spremnih i treba pozvati metodu dijagnostika.proces_ceka.
    // Ukoliko dođe do toga da izvršenje procesa prestaje (dostignut je maksimalan dozvoljen broj uzastopnih STANDARD instrukcija ili su sve instrukcije procesa izvršene), potrebno je pozvati dijagnostika.proces_oslobadja_procesor.
    // Kada se izvrši STANDARD instrukcija nekog procesa, potrebno je pozvati dijagnostika.proces_izvrsio_standardnu.
    // Kada se izvršava UI instrukcija, potrebno je pozvati par metoda: dijagnostika.proces_ceka_na_UI kada se pokrene U/I operacija (nakon čega sledi čekanje na U/I podsistem) i dijagnostika.proces_zavrsio_UI kada se završi U/I operacija.
	void izvrsi_proces(Proces& p) {
        int broj_uzastopnih = 0;
        for(auto it = p.instrukcije.begin(); it!=p.instrukcije.end();it++){
            unique_lock<mutex> l(m);

            while((id_procesa != -1)&&(p.id != id_procesa)){
                dijagnostika.proces_ceka(p.id);
                red_procesa.wait(l);
            }

            id_procesa = p.id;

            if( (*it)==STANDARD ){

                l.unlock();
                this_thread::sleep_for(milliseconds(vreme_obrade_standradne(dr)));
                l.lock();
                dijagnostika.proces_izvrsio_standardnu(p.id);

                if(++broj_uzastopnih == maks_instrukcija  || it == p.instrukcije.end()-1){
                    dijagnostika.proces_oslobadja_procesor(p.id);
                    id_procesa = -1;
                    broj_uzastopnih=0;
                    red_procesa.notify_one();
                    l.unlock();
                    this_thread::sleep_for(milliseconds(100));
                }

            }else{
                // UI
                shared_ptr<UI_zahtev> zahtev = shared_ptr<UI_zahtev>(new UI_zahtev(p.id));
                zahtevi.push(zahtev);
                ui.notify_one();

                dijagnostika.proces_ceka_na_UI(p.id);

                broj_uzastopnih = 0;
                id_procesa = -1;
                red_procesa.notify_one();

                while(!zahtev->obradjen){
                    zahtev->cv.wait(l);
                }
                dijagnostika.proces_zavrsio_UI(p.id);
            }

        }
	}

    // Metoda koju poziva nit koja simulira obrađivač U/I zahteva kako bi se obradili trenutno pohranjeni U/I zahtevi.
    //
    // Potrebno je pozvati dijagnostika.ui_ceka kada ne postoje trenutno pohranjeni U/I zahtevi i obrađivač čeka na prvi.
    // Potrebno je pozvati dijagnostika.ui_zapocinje kada obrađivač krene u obradu U/I zahteva. Kada obrađivač završi taj zahtev, potrebno je pozvati dijagnostika.ui_zavrsio.
	void obradi_zahteve() {
        while(true){          
            unique_lock<mutex> l(m);
            while(zahtevi.empty() && !gotovo){
                dijagnostika.ui_ceka();
                ui.wait(l);
            }

            if(gotovo) return;

            shared_ptr<UI_zahtev> zahtev = zahtevi.front();
            zahtevi.pop();

            
            dijagnostika.ui_zapocinje(zahtev->id);

            l.unlock();
            this_thread::sleep_for(milliseconds(vreme_obrade_ui(dr)));
            l.lock();

            zahtev->obradjen = true;
            zahtev->cv.notify_one(); 
            dijagnostika.ui_zavrsio(zahtev->id);

        }
	}


    // Metoda koja služi da se prekine beskonačna obrada zahteva od strane obrađivača U/I zahteva.
    void zavrsi() {
        unique_lock<mutex> l(m);
        gotovo = true;
        ui.notify_one();
    }
};

#endif // OS_HPP_INCLUDED
