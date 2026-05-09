/**
 * Napisati C++ program koji iz ulazne datoteke cita podatke o temperaturi u toku vikenda sa ski 
 * staza na Kopaoniku, Zlatiboru i Jahorini i odredjuje koji dani i na kojoj planini su idealni 
 * za skijanje a koji nisu. Neki idealni opseg temperature za skijanje je od -5 do 3 stepena.
 * 
 * Za svaku od planina postoji posebna datoteka cije ime se sastoji od imena planine i prosirenja
 * (ekstenzije) ".txt". U svakoj pojedinacnoj datoteci se u jednom redu nalaze podaci za jedan dan. 
 * Jedan red sadrzi redom ime_dana, datum, i potom izmerene temperature. Temperatura se meri na 
 * svakih sat vremena, pocevsi od 8 ujutru, do 8 uvece. Svi podaci su odvojeni razmakom.
 * 
 * Izgled jednog reda iz ulaznih datoteka "Kopaonik.txt" "Zlatibor.txt" "Jahorina.txt"
 * 
 *     subota 01.02.  -15 -13 -10 -8 -3 0 -2 -3 2 2 -5 -7 -3
 * 
 * NAPOMENA: ukoliko ne postoji neka od ulaznih datoteka, treba samo napisati poruku da datoteka
 * ne postoji i nastaviti dalje sa izvrsavanjem programa uz oslonac na podatke iz preostalih
 * datoteka
 * 
 * Treba za svaki dan pronaci najnizu i najvisu dnevnu temperaturu. Ukoliko minimalna i maksimalna
 * temperatura upadaju u navedeni opseg, treba informacije za taj dan ispisati u datoteku 
 * "idealno.txt", u suprotnom u datoteku "lose.txt".
 *
 * Ispis u izlaznu datoteku treba da prati format:
 *     <ime_planine> [<ime_dana> <datum>] <min. temp.> >> <maks. temp.>
 * 
 * Primer ispisa u bilo kojoj od izlaznih datoteka "idealno.txt", "lose.txt":
 * 
 *     Kopaonik [subota 01.02.] -15 >> 2
 *
 * Treba napraviti jednu nit koja ce samo citati podatke iz ulaznih datoteka, jednu nit koja ce 
 * samo pisati spremljene podatke u izlazne datoteke i 4 niti radnika koji ce na osnovu podataka iz
 * ulaznih datoteka generisati sve neophodno za ispis u izlazne datoteke.
*/

#define BR_RADNIKA 4
#define BR_MERENJA_TEMPERATURE 13
#define MINIMALNA_IDEALNA_TEMPERATURA -5
#define MAKSIMALNA_IDEALNA_TEMPERATURA 3

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <string>
#include <queue>
#include <thread>

using namespace std;

class StanjeSkijalistaNaDan {
private:
    string skijaliste;
    string dan;
    string datum;
    int najveca,najmanja;
    bool dobra;
public:
    StanjeSkijalistaNaDan() {}
    StanjeSkijalistaNaDan(string s, string dn, string dt, int max, int min) : skijaliste(s), dan(dn), datum(dt), najveca(max), najmanja(min) {
        if((najveca<=MAKSIMALNA_IDEALNA_TEMPERATURA)&&(najmanja>=MINIMALNA_IDEALNA_TEMPERATURA)){
            dobra = true;
        }else{
            dobra = false;
        }
    }
    
    string getSkijaliste(){return skijaliste;};
    string getDanIDatum(){return "["+dan+" "+datum+"]";}
    int getNajveca(){return najveca;}
    int getNajmanja(){return najmanja;}
    bool dobraTemperatura(){return dobra;}

private:
    // TODO dodati metode po potrebi
};

/** Klasa koja modeluje "postansko sanduce" izmedju citaca i radnika.
*/
template<typename T>
class RedoviIzDatoteke {
private:
    mutex podaci_mx;                       // propusnica za sinhronizaciju nad svim poljima klase
    // TODO dodati polja po potrebi
    bool kraj;
    queue<T> podaci;
    condition_variable cv;
public:
    RedoviIzDatoteke(): kraj(false) {}

    void dodaj(T redIzDatoteke) {
        unique_lock<mutex> ul(podaci_mx);
        podaci.push(redIzDatoteke);
        cv.notify_one();
    }

    bool preuzmi(T &redIzDatoteke) {
        unique_lock<mutex> ul(podaci_mx);
        
        while(daLiCekamPodatke()){
            cv.wait(ul);
        }
        if(jeLiKraj()){
            return false;
        }

        redIzDatoteke = move(podaci.front());
        podaci.pop();
        return true;
    }

    // TODO dodati metode po potrebi
    void objaviKraj(){
        unique_lock<mutex> ul(podaci_mx);
        kraj = true;
        cv.notify_all();
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


/** Klasa koja modeluje "postansko sanduce" izmedju radnika i pisaca.
*/
template<typename T>
class PodaciZaIspis {
private:
    mutex podaci_mx;                       // propusnica za sinhronizaciju nad svim poljima klase
    // TODO dodati polja po potrebi
    bool kraj;
    int br_stvaralaca_podataka;
    condition_variable cv;
    queue<T> podaci;
public:
    PodaciZaIspis(): kraj(false), br_stvaralaca_podataka(0) {}  // na pocetku nije kraj i nema radnika

    void dodaj(T stanjeSkijalista) {
        unique_lock<mutex> ul(podaci_mx);
        podaci.push(stanjeSkijalista);
        cv.notify_one();
    }

    bool preuzmi(T &stanjeSkijalista) {
        unique_lock<mutex> ul(podaci_mx);

        while(daLiCekamPodatke()){
            cv.wait(ul);
        }
        if(jeLiKraj()){
            return false;
        }

        stanjeSkijalista = move(podaci.front());
        podaci.pop();
        return true;
    }

    // TODO dodati metode po potrebi

    void prijaviRadnika(){
        unique_lock<mutex> ul(podaci_mx);
        br_stvaralaca_podataka++;
    }
    void odjaviRadnika(){
        unique_lock<mutex> ul(podaci_mx);
        br_stvaralaca_podataka--;
        if(!br_stvaralaca_podataka){
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

void citac(vector<string> imena_ulaznih_datoteka, RedoviIzDatoteke<string>& redovi_iz_ulaznih_datoteka) {
    string linija;
    string linijaf;

    for(auto it: imena_ulaznih_datoteka){
        ifstream dat(it);
        
        if (dat.is_open()){

            while(getline(dat,linija)){
                linijaf = it.substr(0, it.size()-4) + " " + linija;
                redovi_iz_ulaznih_datoteka.dodaj(linijaf);
                // cout<<linijaf<<endl;
            }
            dat.close();
        }else{
            cerr <<"CITAC: datoteka ne postoji."<<endl;
        }

    }
    redovi_iz_ulaznih_datoteka.objaviKraj();
}

void radnik(RedoviIzDatoteke<string>& redovi_iz_ulaznih_datoteka, PodaciZaIspis<StanjeSkijalistaNaDan>& pripremljeni_podaci){
    pripremljeni_podaci.prijaviRadnika();
    string linija;

    while(redovi_iz_ulaznih_datoteka.preuzmi(linija)){
        vector<int> temperature;
        stringstream s(linija);
        string ski,dan,datum;

        s>>ski>>dan>>datum;

        int temp;
        while(s>>temp){
            temperature.push_back(temp);
        }

        int min,max;
        min = max = temperature[0];

        for(int i=1;i<BR_MERENJA_TEMPERATURE;i++){
            int vr = temperature[i];
            if(vr<min){
                min = vr;
            }
            if(vr>max){
                max = vr;
            }
        }
        pripremljeni_podaci.dodaj(StanjeSkijalistaNaDan(ski,dan,datum,max,min));
    }

    pripremljeni_podaci.odjaviRadnika();
}

void pisac(PodaciZaIspis<StanjeSkijalistaNaDan>& pripremljeni_podaci) {
    StanjeSkijalistaNaDan skijaliste;
    string output_filename;

    while(pripremljeni_podaci.preuzmi(skijaliste)){
        if(skijaliste.dobraTemperatura()){
            output_filename = "idealno.txt";
        }else{
            output_filename = "lose.txt";
        }

        ofstream dat(output_filename, ios::app);
        if(dat.is_open()){
            // Kopaonik [subota 01.02.] -15 >> 2
            dat<<skijaliste.getSkijaliste()<<" "<<skijaliste.getDanIDatum()<<" "
                <<skijaliste.getNajmanja()<<" >> "<<skijaliste.getNajveca()<<'\n';
            dat.close();
        }else{
            cerr<<"PISAC: nemoguce otvoriti izlaznu datoteku.\n";
        }

    }

}


int main() {
    PodaciZaIspis<StanjeSkijalistaNaDan> pripremljeni_podaci;
    RedoviIzDatoteke<string> redovi_iz_ulaznih_datoteka;
    vector<string> datoteke{"Kopaonik.txt", "Jahorina.txt", "Zlatibor.txt"};

    ofstream("idealno.txt").close();
    ofstream("lose.txt").close();

    thread t1 = thread(citac, datoteke, ref(redovi_iz_ulaznih_datoteka));
    vector<thread> t(BR_RADNIKA);
    for(int i=0;i<BR_RADNIKA;i++){
        t[i] = thread(radnik, ref(redovi_iz_ulaznih_datoteka), ref(pripremljeni_podaci));
    }
    thread t2 = thread(pisac, ref(pripremljeni_podaci));

    t1.join();
    for(int i=0;i<BR_RADNIKA;i++){
        t[i].join();
    }
    t2.join();

    return 0;
}