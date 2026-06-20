#ifndef MAGISTRALA_HPP_INCLUDED
#define MAGISTRALA_HPP_INCLUDED

#include "dijagnostika.hpp"

using namespace std;

// Klasa magistrale (sabirnice). Glavna deljena promenljiva za sinhronizaciju pristupa procesora memoriji i dma kontroleru.
class Magistrala {
public:
    // Stanja sabirnice - slobodna, čitanje iz memorije, pisanje u memoriju, dma transfer. Primetiti sličnost sa stanjima iz zadatka "multiprocesor":
    enum Stanje { SLOBODNA, MEM_CITAJ, MEM_PISI, DMA};

    // Struktura u koju se beleže parametri DMA transfera. Odakle, kome i koliko bajtova se čita ili piše.
    struct DMA_transfer {
        int odakle;
        int koliko;
        int kome;
    };

    mutex m;
    condition_variable red_cekanja, red_dma;
    bool zauzeta;
    bool kraj;
    Memorija& memorija;
    bool dma;

private:
    Dijagnostika& dijagnostika;

public:
    Magistrala(Dijagnostika& d, Memorija& mem) : dijagnostika(d), memorija(mem) {
        zauzeta = false;
        kraj = false;
        dma = false;
    }

    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    char citaj_memoriju(int adresa) {
        unique_lock<mutex> l(m);

        l.unlock();
        this_thread::sleep_for(chrono::milliseconds(700));
        l.lock();

        return memorija.citaj(adresa);
    }

    void pisi_u_memoriju(int adresa, char vrednost) {
        unique_lock<mutex> l(m);

        memorija.pisi(adresa, vrednost);

        l.unlock();
        this_thread::sleep_for(chrono::milliseconds(700));
        l.lock();
    }

    void dma(DMA_transfer trans) {
        unique_lock<mutex> l(m);
        while(!dma){
            red_dma.wait(l);
        }
    }

    DMA_transfer okidac_dma_kontrolera() {
        unique_lock<mutex> l(m);
        dma = true;
        red_dma.notify_all();
    }
    
    void zavrsi() {
        kraj = true;
        red_cekanja.notify_all();
    }
};

#endif // MAGISTRALA_HPP_INCLUDED
