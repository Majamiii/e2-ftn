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
#define BROJ_IZGENERISANIH_VREDNOSTI 10

#include <iostream>
#include <queue>
#include <mutex>
#include <string>
#include <fstream>
#include <random>
#include <condition_variable>
#include <vector>
#include <thread>

using namespace std;

struct trio {
    double donja;
    double gornja;
    long long seed;
};

/** Klasa koja modeluje "postansko sanduce" izmedju citaca i radnika.
*/
template<typename T>
class UlazniPodaci {
private:
    mutex podaci_mx;                       // propusnica za sinhronizaciju nad svim poljima klase
    // TODO dodati polja ako je potrebno
    bool kraj;
    condition_variable cv;
    queue<T> podaci;
public:
    UlazniPodaci(): kraj(false) {}  // na pocetku nije kraj i nema radnika

    void dodaj(T par_granica) {
        unique_lock<mutex> ul(podaci_mx);
        podaci.push(par_granica);
        cv.notify_one();
    }

    bool preuzmi(T &par_granica) {
        unique_lock<mutex> ul(podaci_mx);

        while(daLiCekamPodatke()){
            cv.wait(ul);
        }
        
        if(jeLiKraj()){
            return false;
        }

        par_granica = podaci.front();
        podaci.pop();

        return true;
    }

    // TODO dodati jos neku metodu ako je potrebno
    void objaviKraj(){
        unique_lock<mutex> propusnica(podaci_mx);
        kraj = true;
        cv.notify_all();
    }

private:
    /**
     * Provera da li treba da cekamo podatke. Vraca istinu samo onda kada u kolekciji
     * nema podataka ali istovremeno i nije objavljen kraj stvaranja podataka.
    */
    bool daLiCekamPodatke() {
       return podaci.empty() && !kraj;
    }

    /**
     * Provera da li smo zavrsili sa citanjem podataka. Vraca istinu samo onda kada nema vise podataka
     * u kolekciji i sve niti stvaraoci podataka su se odjavili.
    */
    bool jeLiKraj() {
        return podaci.empty() && kraj;
    }
};


/** Klasa koja modeluje "postansko sanduce" izmedju radnika i pisaca.
*/
template<typename T>
class IzlazniPodaci {
private:
    mutex podaci_mx;                       // propusnica za sinhronizaciju nad svim poljima klase
    // TODO dodati polja ako je potrebno
    int br_stvaralaca_podataka;
    condition_variable cv;
    queue<T> podaci;
    bool kraj;
public:
    IzlazniPodaci(): kraj(false), br_stvaralaca_podataka(0) {}  // na pocetku nije kraj i nema radnika

    void dodaj(T brojevi) {
       unique_lock<mutex> ul(podaci_mx);
       podaci.push(brojevi);
       cv.notify_one();
    }

    bool preuzmi(T &brojevi) {
        unique_lock<mutex> ul(podaci_mx);
        while(daLiCekamPodatke()){
            cv.wait(ul);
        }
        if(jeLiKraj()){
            return false;
        }

        brojevi = podaci.front();
        podaci.pop();

        return true;
    }

    // TODO dodati jos neku metodu ako je potrebno
    void dodatRadnik(){
        unique_lock<mutex> ul(podaci_mx);
        br_stvaralaca_podataka++;
    }
    void odjavljenRadnik(){
        unique_lock<mutex> ul(podaci_mx);
        br_stvaralaca_podataka--;

        if(br_stvaralaca_podataka==0){
            kraj = true;
            cv.notify_all();
        }
    }

private:
    /**
     * Provera da li treba da cekamo podatke. Vraca istinu samo onda kada u kolekciji
     * nema podataka ali istovremeno i nije objavljen kraj stvaranja podataka.
    */
    bool daLiCekamPodatke() {
        return !kraj && podaci.empty();
    }

    /**
     * Provera da li smo zavrsili sa citanjem podataka. Vraca istinu samo onda kada nema vise podataka
     * u kolekciji i sve niti stvaraoci podataka su se odjavili.
    */
    bool jeLiKraj() {
        return kraj && podaci.empty();
    }
};


/**
 * Logika radnika - niti koje vrse transformaciju ulaznih podataka u izlazne podatke spremne za ispis.
*/
void radnik(UlazniPodaci<struct trio> &ulaz, IzlazniPodaci<vector<double>> &izlaz) {
    izlaz.dodatRadnik();

    vector<double> vrednosti;
    struct trio t;

    while(ulaz.preuzmi(t)){
        uniform_real_distribution<double> dist(t.donja,t.gornja);
        default_random_engine eng;
        eng.seed(t.seed);
        vrednosti.clear();
        vrednosti.resize(BROJ_IZGENERISANIH_VREDNOSTI+3);
        double suma, prosek, minimum, maksimum, d;
        suma = prosek = minimum = maksimum = d = dist(eng);
        vrednosti[0] = d;

        for(int i=1; i<BROJ_IZGENERISANIH_VREDNOSTI;i++){
            d = dist(eng);
            suma += d;
            if (d>maksimum)
                maksimum = d;
            if (d<minimum)
                minimum = d;

            vrednosti[i] = d;
        }
        prosek = suma/BROJ_IZGENERISANIH_VREDNOSTI;

        vrednosti[10] = prosek;
        vrednosti[11] = minimum;
        vrednosti[12] = maksimum;

        izlaz.dodaj(vrednosti);
    }
    izlaz.odjavljenRadnik();
}

/**
 * Logika citaca_iz_datoteke - nit koja radi citanje iz ulazne datoteke i salje u ulaznu kolekciju za radnike
*/
void citacf(string ime_ulazne_dat, UlazniPodaci<struct trio> &ulaz) {
    ifstream dat(ime_ulazne_dat);
    string linija;

    trio t;

    if(dat.is_open()){
        while(getline(dat,linija)){
            int p1 = linija.find(":");
            int p2 = linija.find(":", p1+1);
            t.donja = stod(linija.substr(0,p1));
            t.gornja = stod(linija.substr(p1+1,p2-p1-1));
            t.seed = stoll(linija.substr(p2+1, linija.size()-p2-1));
            ulaz.dodaj(t);
        }
        dat.close();
    }else{
        cerr<<"CITAC: ne mogu da otvorim ulaznu datoteku.\n";
    }
    ulaz.objaviKraj();
}

/**
 * Logika pisaca_u_datoteku - nit koja radi pisanje u izlaznu datoteku podataka dobijenih od radnika
*/
void pisacf(IzlazniPodaci<vector<double>> &izlaz, string ime_izlazne_dat) {
    ofstream dat(ime_izlazne_dat);
    vector<double> brojevi;

    if(dat.is_open()){

        for(int i=0;i<BROJ_IZGENERISANIH_VREDNOSTI;i++){
            dat<<i+1<<".,";
        }
        dat<<"prosek,minimum,maksimum\n";

        while(izlaz.preuzmi(brojevi)){
            for(int i=0;i<brojevi.size()-1;i++){
                dat << brojevi[i]<<",";
            }
            dat << brojevi[brojevi.size()-1]<<"\n";
        }
        dat.close();
    }else{
        cerr << "PISAC: ne mogu da otvorim izlaznu datoteku.\n";
    }

}

int main() {
    IzlazniPodaci<vector<double>> izlaz;
    UlazniPodaci<struct trio> ulaz;

    thread radnici[BROJ_RADNIKA];
    
    for(int i=0; i<BROJ_RADNIKA; i++){
        radnici[i] = thread(radnik, ref(ulaz), ref(izlaz));
    }
    thread p1 = thread(citacf, "distribucije.txt", ref(ulaz));
    thread p2 = thread(pisacf, ref(izlaz), "brojevi.csv");

    p1.join();
    for(int i=0; i<BROJ_RADNIKA; i++){
        radnici[i].join();
    }
    p2.join();
    
    return 0;
}
