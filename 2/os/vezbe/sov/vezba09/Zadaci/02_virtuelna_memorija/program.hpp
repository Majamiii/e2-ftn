#ifndef PROGRAM_HPP_INCLUDED
#define PROGRAM_HPP_INCLUDED

#include "dijagnostika.hpp"
#include "naredba.hpp"
#include "povratna_vrednost.hpp"

#include <condition_variable>

using namespace std;

class Program {
private:
    Dijagnostika& dijagnostika;
    int ukupno_ram;
    int slobodno_ram;
    mutex m;
    condition_variable red_naredbi, red_vm;
    int zauzeto_vm;
    int potrebno_vm;
    bool os_zauzima;
    bool proces_zauzima;
public:
    Program(Dijagnostika& d, int kapacitet) : dijagnostika(d) {
        ukupno_ram = kapacitet;
        zauzeto_vm = 0;
        slobodno_ram = ukupno_ram;
        os_zauzima = false;
        proces_zauzima = false;
    }

    Dijagnostika& getDijagnostika() {
        return dijagnostika;
    }

    // Metoda koju poziva nit koja simulira izvršenje programa, kako bi zauzela potrebnu memoriju
    //
    // naredba - naredba koja se izvršava (naredba kojom se zauzima memorija)
    // Vraća instancu klase Povratna_vrednost koja sadrži opis zauzeća memorije NAKON izvršenja naredbe.
    /*
    struct Povratna_vrednost {          // Struktura koju vraća program nakon pokušaja zauzimanja memorije
        int slobodno_ram;
        int zauzeto_u_virtuelnoj;
    };
    */
    Povratna_vrednost izvrsi_naredbu(Naredba naredba) {
        unique_lock<mutex> l(m);

        while(proces_zauzima || os_zauzima){
            red_naredbi.wait(l);
        }

        proces_zauzima = true;

        // dijagnostika.pokrenuta_naredba(naredba);

        int potrebno_memorije = 0;
        if(naredba.tip == "malloc"){
            potrebno_memorije = naredba.kolicina_memorije;
        }else{
            potrebno_memorije = naredba.ponavljanja * naredba.kolicina_memorije;
        }

        if (potrebno_memorije<=slobodno_ram){
            slobodno_ram -= potrebno_memorije;
        }else{                
            while(potrebno_vm != 0 || os_zauzima){
                red_naredbi.wait(l);
            }
            proces_zauzima = false;
            potrebno_vm = potrebno_memorije;
            red_vm.notify_one();

            while(potrebno_vm != 0 || os_zauzima) {  // čekaj da OS obradi moj zahtev
                red_naredbi.wait(l);
            }
        }
        proces_zauzima = false;
        red_naredbi.notify_one();

        // dijagnostika.izvrsena_naredba(naredba,slobodno_ram,zauzeto_vm);
        return Povratna_vrednost{slobodno_ram, zauzeto_vm};
    }

    // Metoda koju poziva nit koja simulira deo operativnog sistema koji se bavi zauzimanjem virtuelne memorije kako bi se zauzela određena količina VM
    // Potrebnu količinu VM (kao i bilo koju drugu neophodnu informaciju) preneti u nekom izabranom polju klase.
    int zauzmi_virtuelnu_memoriju() {
        unique_lock<mutex> l(m);
        while(proces_zauzima || os_zauzima || !potrebno_vm){
            red_vm.wait(l);
        }
        os_zauzima = true;

        zauzeto_vm += potrebno_vm;
        potrebno_vm = 0;

        os_zauzima = false;
        red_naredbi.notify_all();
        red_vm.notify_all();
        // dijagnostika.izvrseno_zauzimanje_vm(zauzeto_vm);
        return zauzeto_vm;
    }
};

#endif // PROGRAM_HPP_INCLUDED
