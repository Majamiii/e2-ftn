#ifndef BANKA_HPP_INCLUDED
#define BANKA_HPP_INCLUDED

#include <condition_variable>
#include <mutex>

#include "valuta.hpp"
#include "kredit.hpp"

using namespace std;

class Banka {
private:
    Kredit& kredit;
    int dinari;
    int evri;
    mutex m;
    condition_variable odobreno;
public:

    Banka(Kredit& kr, int inicijalni_dsaldo, int inicijalni_esaldo)
        : kredit(kr), dinari(inicijalni_dsaldo), evri(inicijalni_esaldo) {
        // Prosiriti po potrebi ...
    }

    // Metoda koju poziva nit koja simulira klijenta banke, kada klijent zatraži kredit od banke.
    // Ukoliko banka nema odgovarajuća sredstva kako bi omogućila kredit, metoda će blokirati dok se ta sredstva ne oslobode.
    //
    // rbr - Redni broj klijenta
    // svota - Novčani iznos koji je potreban klijentu
    // valuta - Valuta u kojem je novčani iznos
    //
    // Potrebno je pozvati metodu kredit.ceka kada nema sredstava odgovarajuće valute da se odobri kredit.
    // Potrebno je pozvati metodu kredit.dobio kada se kredit realizuje.
    void uzmi_kredit(int rbr, int svota, Valuta valuta) {
        // Implementirati ...

        unique_lock<mutex> l(m);

        if(valuta==0){  // dinari
            while(svota > dinari){
                kredit.ceka(rbr,svota,valuta);
                odobreno.wait(l);
            }
            dinari -= svota;
            kredit.dobio(rbr,svota,dinari,valuta);
        }else{
            while(svota>evri){
                kredit.ceka(rbr,svota,valuta);
                odobreno.wait(l);
            }
            evri -= svota;
            kredit.dobio(rbr,svota,evri,valuta);
        }

    }

    // Metoda koju poziva nit koja simulira klijenta banke, kada klijent vrati kredit koji je prethodno uzeo od banke.
    //
    // rbr - Redni broj klijenta
    // svota - Novčani iznos koji je potreban klijentu
    // valuta - Valuta u kojem je novčani iznos
    //
    // Potrebno je pozvati metodu kredit.vratio kada je kredit vraćen.
    void vrati_kredit(int rbr, int svota, Valuta valuta) {
        // Implementirati ...
        unique_lock<mutex> u(m);

        if(valuta==0){
            dinari += svota;
            kredit.vratio(rbr,svota,dinari,valuta);
        }else{
            evri += svota;
            kredit.vratio(rbr,svota,evri,valuta);
        }

        odobreno.notify_all();
    }
};

#endif // BANKA_HPP_INCLUDED
