/**
 * Napisati C++ program koji cita podatke o uniformnim distribucijama iz ulazne datoteke i potom za
 * svaku distribuciju generise po 10 brojeva, racuna njihov prosek, i nalazi najmanji i najveci broj. 
 * 
 * U ulaznoj datoteci "distribucije.txt" se u svakom redu nalaze informacije o donjoj i gornjoj granici
 * intervala u kojem treba generisati brojeve a potom vrednost koju treba iskoristiti kao jezgro (seed)
 * za generisanje nasumicnih brojeva. Navedene vrednosti su odvojene dvotackom. Granice su razlomljeni
 * brojevi a jezgro je veoma velika celobrojna vrednost.
 * 
 * U izlaznoj datoteci "brojevi.csv" treba da se nalaze u jednom redu odvojeni zarezom prvo 10 
 * izgenerisanih brojeva a potom i prosek, najmanji element i najveci element.
 * 
 * Treba napraviti jednu nit koja ce samo citati ulazne podatke, jednu nit koja ce samo pisati gotove
 * brojeve u datoteku i 6 niti radnika koji ce na osnovu podataka iz ulazne datoteke generisati sve
 * neophodno za ispis u izlaznu datoteku.
*/
#define BROJ_RADNIKA 6

#include <algorithm>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <mutex>
#include <numeric>
#include <queue>
#include <random>
#include <string>
#include <thread>
#include <vector>

using namespace std;

struct trio {
    double donja;           // donja granica intervala
    double gornja;          // gornja granica intervala
    unsigned long long seed; // jezgro za generator slucajnih brojeva
};

/** Klasa koja modeluje "postansko sanduce" izmedju citaca i radnika.
*/
template<typename T>
class UlazniPodaci {
private:
    mutex podaci_mx;              // propusnica za sinhronizaciju nad svim poljima klase
    condition_variable cv;

    queue<T> kolekcija;
    
    bool kraj;
    int radnici;
    // TODO dodati polja ako je potrebno
public:
    UlazniPodaci(): kraj(false), radnici(0) {}  // na pocetku nije kraj i nema radnika

    void dodaj(T par_granica) {
        // TODO
        {
            unique_lock<mutex> l(podaci_mx);
            kolekcija.push(move(par_granica));
        }
        cv.notify_one();
    }

    bool preuzmi(T &par_granica) {
        // TODO
        unique_lock<mutex> l(podaci_mx);

        while( daLiCekamPodatke() ){
            cv.wait(l);
        }

        if(jeLiKraj()){
            return false;
        }

        par_granica = move(kolekcija.front());
        kolekcija.pop();
        return true;
    }

    /** Citac poziva ovu metodu kad zavrsi sa slanjem svih podataka. */
    void objavi_kraj() {
        {
            lock_guard<mutex> lock(podaci_mx);
            kraj = true;
        }
        cv.notify_all();   // probudi sve radnike koji cekaju
    }

    // TODO dodati jos neku metodu ako je potrebno

private:
    /**
     * Provera da li treba da cekamo podatke. Vraca istinu samo onda kada u kolekciji
     * nema podataka ali istovremeno i nije objavljen kraj stvaranja podataka.
    */
    bool daLiCekamPodatke() {
        // TODO
        return !kraj && kolekcija.size()==0;
    }

    /**
     * Provera da li smo zavrsili sa citanjem podataka. Vraca istinu samo onda kada nema vise podataka
     * u kolekciji i sve niti stvaraoci podataka su se odjavili.
    */
    bool jeLiKraj() {
        // TODO
        return kolekcija.empty() && kraj;
    }
};


/** Klasa koja modeluje "postansko sanduce" izmedju radnika i pisaca.
*/
template<typename T>
class IzlazniPodaci {
private:
    mutex podaci_mx;                       // propusnica za sinhronizaciju nad svim poljima klase
    // TODO dodati polja ako je potrebno
    condition_variable cv;
    queue<T> kolekcija;
    bool kraj;
    int br_stvaralaca_podataka;
public:
    IzlazniPodaci(): kraj(false), br_stvaralaca_podataka(0) {}  // na pocetku nije kraj i nema radnika

     /** Radnik se prijavljuje pre pocetka rada. */
    void prijavi_radnika() {
        lock_guard<mutex> lock(podaci_mx);
        ++br_stvaralaca_podataka;
    }
 
    /** Radnik se odjavljuje kad zavrsi; poslednji radnik budi pisaca. */
    void odjavi_radnika() {
        {
            lock_guard<mutex> lock(podaci_mx);
            if (--br_stvaralaca_podataka == 0)
                kraj = true;
        }
        cv.notify_all();
    }
    
    void dodaj(T brojevi) {
        // TODO
        {
            unique_lock<mutex> l(podaci_mx);
            kolekcija.push(move(brojevi));
        }
        cv.notify_one();
    }

    bool preuzmi(T &brojevi) {
        // TODO
        unique_lock<mutex> lock(podaci_mx);
        while(daLiCekamPodatke()){
            cv.wait(lock);
        }
        if(jeLiKraj()){
            return false;
        }

        brojevi = move(kolekcija.front());
        kolekcija.pop();
        return true;
    }

    // TODO dodati jos neku metodu ako je potrebno

private:
    /**
     * Provera da li treba da cekamo podatke. Vraca istinu samo onda kada u kolekciji
     * nema podataka ali istovremeno i nije objavljen kraj stvaranja podataka.
    */
    bool daLiCekamPodatke() {
        // TODO
        return kolekcija.empty() && !kraj;
    }

    /**
     * Provera da li smo zavrsili sa citanjem podataka. Vraca istinu samo onda kada nema vise podataka
     * u kolekciji i sve niti stvaraoci podataka su se odjavili.
    */
    bool jeLiKraj() {
        // TODO
        return kolekcija.empty() && kraj;
    }
};


/**
 * Logika radnika - niti koje vrse transformaciju ulaznih podataka u izlazne podatke spremne za ispis.
*/
void radnik(UlazniPodaci<struct trio> &ulaz, IzlazniPodaci<vector<double>> &izlaz) {
    // TODO
    izlaz.prijavi_radnika();
    trio t;

    while(ulaz.preuzmi(t)){
        mt19937_64 gen(t.seed);
        uniform_real_distribution<double> dist(t.gornja, t.donja);

        vector<double> rezultat;
        rezultat.reserve(13);

        for(int i=0;i<10;++i){
            rezultat.push_back(dist(gen));
        }

        double prosek = accumulate(rezultat.begin(), rezultat.end(), 0.0) / 10.0;
        double najmanji = *min_element(rezultat.begin(), rezultat.end());
        double najveci = *max_element(rezultat.begin(), rezultat.end());
        
        rezultat.push_back(prosek);
        rezultat.push_back(najmanji);
        rezultat.push_back(najveci);

        izlaz.dodaj(move(rezultat));
   
    }
    izlaz.odjavi_radnika();
}

/**
 * Logika citaca_iz_datoteke - nit koja radi citanje iz ulazne datoteke i salje u ulaznu kolekciju za radnike
*/
void citacf(string ime_ulazne_dat, UlazniPodaci<struct trio> &ulaz) {
    // TODO
    ifstream dat(ime_ulazne_dat);
    string linija;

    while(getline(dat,linija)){
        if(linija.empty()){
            continue;
        }
        trio t;

        size_t p1 = linija.find(':');
        size_t p2 = linija.find(':', p1+1);

        t.donja = stod(linija.substr(0,p1));
        t.gornja = stod(linija.substr(p1+1, p2-p1-1));
        t.seed = stoull(linija.substr(p2+1));

        ulaz.dodaj(t);
    }

    ulaz.objavi_kraj();

}

/**
 * Logika pisaca_u_datoteku - nit koja radi pisanje u izlaznu datoteku podataka dobijenih od radnika
*/
void pisacf(IzlazniPodaci<vector<double>> &izlaz, string ime_izlazne_dat) {
    // TODO
    ofstream dat(ime_izlazne_dat);
    dat<<fixed;

    vector<double> red;

    while(izlaz.preuzmi(red)){
        for(size_t i=0; i<red.size(); ++i){
            if(i>0){
                dat<<',';
            }
            dat<<red[i];
        }
        dat<<'\n';
    }

}

int main() {
    UlazniPodaci<struct trio> ulazni_podaci;  // bafer podataka koje salje citac_iz_datoteke a obradjuju radnici
    IzlazniPodaci<vector<double>> izlazni_podaci;  // bafer podataka koje pripremaju radnici a ispisuju se u datoteku u pisacu_u_datoteku
    thread citac{citacf, "distribucije.txt", ref(ulazni_podaci)},  // stvaranje niti citaca_iz_datoteke
           pisac{pisacf, ref(izlazni_podaci), "brojevi.csv"},      // stvaranje niti pisaca_u_datoteku
           radnici[BROJ_RADNIKA];

    for (auto &nit: radnici)
        nit = thread(radnik, ref(ulazni_podaci), ref(izlazni_podaci));  // stvaranje niti radnika

    for (auto &nit: radnici)
        nit.join();
    citac.join();
    pisac.join();

    return 0;
}
