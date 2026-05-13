// INDEKS IME PREZIME
/**
 * Napisati konkurentni C++ program koji iz ulazne datoteke "ulaz.txt" cita red po red, obradjuje ih po navedenim komandama 
 * i potom rezultat smesta u izlazne datoteke "neparni.txt" i "parni.txt".
 *
 * U svakoj ulaznoj datoteci su podaci podeljeni delimiterom ':', i prate
 * sledeci format:
 *     1. broj: ID, unsigned int
 *     2. broj: komanda, unsigned char, odreduje sta treba raditi sa brojevima
 *                koji slede, pritom obratiti paznju da je komanda takodje BROJ
 *     3+. brojevi: brojevi, double, koje treba obraditi po definiciji komande
 *
 * Ulazna datoteka je "ulaz.txt".
 *
 * Komande koje postoje su:
 *     1) prebrojati parne brojeve na indeksima deljivim sa 3
 *     2) naci aritmeticku sredinu razlomljenih brojeva manjih od 16
 *     3) izracunati varijansu (sumu kvadrata odstupanja elemenata od srednje vrednosti deljeno sa brojem elemenata) razlomljenih brojeva
 *     4) napraviti novi niz koji sadrzi samo elemente koji su u originalnom nizu bili na indeksima sa cifrom 3 u zapisu
 *     5) elementi niza su xi vrednosti tacaka, koristiti formulu f(x) = sqrt(x) + 4 kako bi se odredile y vrednosti tacaka, 
 * napraviti novi niz koji sadrzi samo elemente koji su strogo iznad prave g(x) = 1/6*x + 3, ukoliko je y vrednost kompleksna 
 * ne dodavati je u rezultujuci niz
 * 
 * U svakoj izlaznoj datoteci su podaci nakon transformacije upisani u jedan
 * red, podeljeni delimiterom ':', i prate sledeci format:
 *     1. broj: ID, neoznacen ceo broj
 *     2+. brojevi: razlomljeni broj/evi dobijen/i transformacijom na osnovu
 *                    komande
 *
 * Izlazni podaci se rasporedjuju u izlazne datoteke i to:
 *     "neparni.txt" - rezultati za unose sa neparnim ID-om
 *     "parni.txt" - rezultati za unose sa parnim ID-om
 * 
 * Treba napraviti jednu citac nit koja ce samo citati redove iz ulaznih
 * datoteka, jednu stampac nit koja ce samo pisati izlazne podatke u izlazne
 * datoteke i 3 niti radnika koji ce transformisati ulazne podatke u izlazne.
 * 
 * NAPOMENE:
 * Komanda 0 nikada nece postojati u ulaznim datotekama.
 * Redove sa nepostojecim komandama napisati u datoteku "kanta.txt" tako da budu
 * ispisani id, komanda i potom polazni brojevi podeljeni delimiterom ':'.
*/
#include <sstream>
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <thread>
#include <algorithm>
#include <mutex>
#include <condition_variable>

#define BROJ_RADNIKA 3

using namespace std;

struct izlazni_podaci {
    unsigned int id;
    unsigned char komanda;
    vector<double> brojevi;
    bool parni_id;
};

/** Klasa koja modeluje "postansko sanduce" izmedju citaca i radnika.
*/
template<typename T>
class UlazniPodaci {
private:
    mutex m;
    condition_variable cv;
    bool kraj;
    queue<T> podaci;
public:
    UlazniPodaci() : kraj(false) {}

    void dodaj(T neobradjeni_podaci) {
        unique_lock<mutex> ul(m);
        podaci.push(neobradjeni_podaci);
        cv.notify_one();
    }

    bool preuzmi(T &neobradjeni_podaci) {
        unique_lock<mutex> ul(m);
        while(daLiCekamPodatke()){
            cv.wait(ul);
        }
        if(jeLiKraj()){
            return false;
        }
        neobradjeni_podaci = podaci.front();
        podaci.pop();
        return true;
    }

    // TODO dodati jos neku metodu ako je potrebno
    void objaviKraj(){
        unique_lock<mutex> ul(m);
        kraj = true;
        cv.notify_all();
    }

    bool daLiCekamPodatke(){
        return !kraj && podaci.empty();
    }
    bool jeLiKraj(){
        return kraj && podaci.empty();
    }
};


/** Klasa koja modeluje "postansko sanduce" izmedju radnika i pisaca.
*/
template<typename T>
class IzlazniPodaci {
private:
    mutex m;
    condition_variable cv;
    bool kraj;
    queue<T> podaci;
    int broj_radnika;
public:
    IzlazniPodaci() : kraj(false), broj_radnika(0) {}

    void dodaj(T obradjeni_podaci) {
        unique_lock<mutex> ul(m);
        podaci.push(obradjeni_podaci);
        cv.notify_one();
    }

    bool preuzmi(T &obradjeni_podaci) {
        unique_lock<mutex> ul(m);
        while(daLiCekamPodatke()){
            cv.wait(ul);
        }
        if(jeLiKraj()){
            return false;
        }
        obradjeni_podaci = podaci.front();
        podaci.pop();
        return true;
    }

    // TODO dodati jos neku metodu ako je potrebno
    void objaviRadnika(){
        unique_lock<mutex> ul(m);
        broj_radnika++;
    }
    void odjaviRadnika(){
        unique_lock<mutex> ul(m);
        broj_radnika--;
        if(!broj_radnika){
            kraj = true;
            cv.notify_one();    // svejedno u principu da li all ili one jer imamo jednog stampaca
        }
    }
    
    bool daLiCekamPodatke(){
        return !kraj && podaci.empty();
    }
    bool jeLiKraj(){
        return kraj && podaci.empty();
    }
};


/**
 * Parsiranje reda iz ulazne datoteke
 *   parametri:
 *     - red_datoteke, sadrzaj jednog reda ulazne datoteke
 *     - id, adresa gde ce biti upisan id procitan iz reda
 *     - komanda, adresa gde ce biti upisan id komande procitan iz reda
 *   vraca: kolekciju brojeva koje radnik treba da transformise po komandi
*/
vector<double> izdvoj_brojeve(const string red_datoteke, unsigned &id, unsigned char &komanda) {
    istringstream red_datoteke_tok(red_datoteke);
    vector<double> brojevi;
    string broj;

    if (getline(red_datoteke_tok, broj, ':'))
        id = stoul(broj);

    if (getline(red_datoteke_tok, broj, ':'))
        komanda = stoul(broj);

    while (getline(red_datoteke_tok, broj, ':'))
        brojevi.push_back(stod(broj));

    return brojevi;
}

/*
 * Komande koje postoje su:
 *     1) prebrojati parne brojeve na indeksima deljivim sa 3
 *     2) naci aritmeticku sredinu razlomljenih brojeva manjih od 16
 *     3) izracunati varijansu (sumu kvadrata odstupanja elemenata od srednje vrednosti deljeno sa brojem elemenata) razlomljenih brojeva
 *     4) napraviti novi niz koji sadrzi samo elemente koji su u originalnom nizu bili na indeksima sa cifrom 3 u zapisu
 *     5) elementi niza su xi vrednosti tacaka, koristiti formulu f(x) = sqrt(x) + 4 kako bi se odredile y vrednosti tacaka, 
 * napraviti novi niz koji sadrzi samo elemente koji su strogo iznad prave g(x) = 1/6*x + 3, ukoliko je y vrednost kompleksna 
 * ne dodavati je u rezultujuci niz
*/

vector<double> obradiOperaciju(unsigned char komanda, vector<double> brojevi){
    vector<double> izlaz;
    string indeks;

    int cmd = komanda;

    switch(cmd){
        case 1: {
            int broj=0;
            for(int i=0;i<brojevi.size();i++){
                if(i%3==0){
                    if(int(brojevi[i])%2 == 0){

                        broj++;
                    }
                }
            }
            izlaz.push_back(broj);
            break;
        }
        case 2: {

            double suma=0; double n=0;
            for(int i=0;i<brojevi.size();i++){
                if(brojevi[i]<16){
                    suma += brojevi[i];
                    n++;
                }
            }
            izlaz.push_back(suma/n);
            break;
        }
        case 3:{

            double suma=0;
            for(int i=0;i<brojevi.size();i++){
                suma += brojevi[i];
            }
            double prosek = suma/brojevi.size();
            
            double suma_2 = 0;
            for(int i=0;i<brojevi.size();i++){
                suma_2 += pow( (prosek - brojevi[i]),2);
            }
            izlaz.push_back(suma_2/brojevi.size());
            break;
        }
        case 4:{

            // napraviti novi niz koji sadrzi samo elemente koji su u originalnom nizu bili na indeksima sa cifrom 3 u zapisu
            for(int i=0;i<brojevi.size();i++){
                indeks = to_string(i);
                if (indeks.find_first_of('3') != string::npos){
                    izlaz.push_back(brojevi[i]);
                }
            }
            break;
        }
        case 5:
        /*
        elementi niza su xi vrednosti tacaka, koristiti formulu f(x) = sqrt(x) + 4 kako bi se odredile y vrednosti tacaka, 
        * napraviti novi niz koji sadrzi samo elemente koji su strogo iznad prave g(x) = 1/6*x + 3, ukoliko je y vrednost kompleksna 
        * ne dodavati je u rezultujuci niz
         */
        {
            for(int i = 0; i < brojevi.size(); i++) {
                // cout << "BROJ: " << brojevi[i] << endl;
                if(brojevi[i] >= 0) {
                    double y = sqrt(brojevi[i]) + 4;
                    double prava = (1.0 / 6.0) * brojevi[i] + 3;
                    if(y > prava) {
                        izlaz.push_back(brojevi[i]);
                    }
                }
            }
            break;
        }
        default:{
            izlaz.push_back(komanda);
            for(auto it:brojevi){
                izlaz.push_back(it);
            }
        }
    }
    return izlaz;
}

/**
 * Logika radnika - niti koje vrse transformaciju ulaznih podataka u izlazne
 * podatke spremne za ispis.
*/
void radnik_nit(UlazniPodaci<string> &ulaz, IzlazniPodaci<struct izlazni_podaci> &izlaz) {
    izlaz.objaviRadnika();
    string linija;

    while(ulaz.preuzmi(linija)){
        stringstream ss(linija);
        string token;
        vector<double> brojevi;

        unsigned int id;
        unsigned char komanda;

        int i=0;
        while(getline(ss,token,':')){
            if(i==0){id = stoul(token);}
            else if(i==1){komanda = stoul(token);}
            else{brojevi.push_back(stod(token));}
            i++;
        }

        struct izlazni_podaci st;
        st.id = id;
        st.parni_id = (id%2 == 0);
        st.komanda = komanda;
        st.brojevi = obradiOperaciju(komanda, brojevi);

        izlaz.dodaj(st);
    }

    izlaz.odjaviRadnika();
}

/**
 * Logika citaca - nit koja radi citanje iz ulazne datoteke i salje u ulaznu
 * kolekciju za radnike
*/
void citac_nit(UlazniPodaci<string> &ulaz) {
    ifstream dat("ulaz.txt");
    string linija;

    if(dat.is_open()){

        while(getline(dat,linija)){
            ulaz.dodaj(linija);
        }

        dat.close();
    }else{
        cerr<<"CITAC: nemoguce otvoriti ulazni fajl.\n";
    }

    ulaz.objaviKraj();
}

/**
 * Logika stampaca - nit koja radi pisanje u izlaznu datoteku podataka dobijenih
 * od radnika
*/
void stampac_nit(IzlazniPodaci<struct izlazni_podaci> &izlaz) {
    string output_file;
    struct izlazni_podaci struktura;
    vector<struct izlazni_podaci> svi;

    while(izlaz.preuzmi(struktura)){
        svi.push_back(struktura);
    }

    sort(svi.begin(), svi.end(), [](const izlazni_podaci &a, const izlazni_podaci &b){
        return a.id < b.id;
    });

    for(auto &struktura : svi){

        if(struktura.komanda > 5){
            output_file = "kanta.txt";
        }else if(struktura.parni_id){
            output_file = "parni.txt";
        }else{
            output_file = "neparni.txt";
        }

        ofstream dat(output_file, ios::app);

        if(dat.is_open()){

            dat << struktura.id << ":";
            vector<double> brojevi = struktura.brojevi;

            for(int i = 0; i < (int)brojevi.size(); i++){
                dat << brojevi[i];
                if(i < (int)brojevi.size() - 1) dat << ":";
            }
            dat << "\n";

            dat.close();
        }else{
            cerr<<"STAMPAC: nemoguce obraditi izlaznu datoteku.\n";
        }

    }

}

int main() {
    IzlazniPodaci<struct izlazni_podaci> izlaz;
    UlazniPodaci<string> ulaz;
    thread radnici[BROJ_RADNIKA];

    ofstream("parni.txt").close();
    ofstream("neparni.txt").close();
    ofstream("kanta.txt").close();

    thread p1 = thread(citac_nit, ref(ulaz));
    for(int i=0;i<BROJ_RADNIKA;i++){
        radnici[i] = thread(radnik_nit, ref(ulaz), ref(izlaz));
    }
    thread p2 = thread(stampac_nit, ref(izlaz));

    p1.join();
    for(int i=0;i<BROJ_RADNIKA;i++){
        radnici[i].join();
    }
    p2.join();

    exit(0);
}