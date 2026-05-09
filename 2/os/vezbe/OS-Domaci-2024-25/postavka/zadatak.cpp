// INDEKS IME PREZIME
/**
 * Napisati konkurentni C++ program koji iz ulazne datoteke "ulaz.txt" cita red po red, 
 * obradjuje ih po navedenim komandama i potom rezultat smesta u izlazne datoteke "parni.txt" i "neparni.txt".
 *
 * U svakoj ulaznoj datoteci su podaci podeljeni delimiterom '|', i prate
 * sledeci format:
 *     1. broj: ID, unsigned int
 *     2. broj: komanda, unsigned char, odreduje sta treba raditi sa brojevima
 *                koji slede, pritom obratiti paznju da je komanda takodje BROJ
 *     3+. brojevi: brojevi, double, koje treba obraditi po definiciji komande
 *
 * Ulazna datoteka je "ulaz.txt".
 *
 * Komande koje postoje su:
 *     1) Sortirati ulazni skup podataka u opadajućem redosledu.
 *     2) U izlaznom nizu ispisati kumulativne sume ulaznih elemenata, zaključno sa korespodentnim 
 * indeksom iz ulaznog niza. PRIMER: [1,5,-2,3,-1,2] => [1,6,4,7,6,8]
 *     3) Za svaki od ulaznih elemenata ispisati njegov obrnuti broj, pri čemu treba obrnuti i znak. 
 * PRIMER: 38.91 => -19.83, -11.23 => 32.11
 *
 * U svakoj izlaznoj datoteci su podaci nakon transformacije upisani u jedan
 * red, podeljeni delimiterom ';', i prate sledeci format:
 *     1. broj: ID, neoznacen ceo broj
 *     2+. brojevi: razlomljeni broj/evi dobijen/i transformacijom na osnovu
 *                    komande
 *
 * Izlazni podaci se rasporedjuju u izlazne datoteke i to:
 *     "parni.txt" - rezultati unosa čiji je ID paran broj
 *     "neparni.txt" - rezultati unosa čiji je ID neparan broj
 *
 * Treba napraviti jednu citac nit koja ce samo citati redove iz ulaznih
 * datoteka, jednu stampac nit koja ce samo pisati izlazne podatke u izlazne
 * datoteke i 5 niti radnika koji ce transformisati ulazne podatke u izlazne.
 *
 * NAPOMENE:
 * Komanda 0 nikada nece postojati u ulaznim datotekama.
 * Redove sa nepostojecim komandama napisati u datoteku "kanta.txt" tako da budu
 * ispisani id, komanda i potom polazni brojevi podeljeni delimiterom ','.
 */
#include <sstream>
#include <string>
#include <thread>
#include <iostream>
#include <fstream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define BROJ_RADNIKA 5

struct izlazni_podaci
{
    int ID;
    vector<double> brojevi;
};

/** Klasa koja modeluje "postansko sanduce" izmedju citaca i radnika.
 */
template <typename T>
class UlazniPodaci
{
private:
    mutex m;
    condition_variable cv;
    queue<T> podaci;
    bool kraj;
public:
    UlazniPodaci() : kraj(false) {}

    void dodaj(T neobradjeni_podaci)
    {
        unique_lock<mutex> ul(m);
        podaci.push(neobradjeni_podaci);
        cv.notify_one();
    }

    bool preuzmi(T &neobradjeni_podaci)
    {
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
    bool jeLiKraj(){
        return kraj && podaci.empty();
    }
    bool daLiCekamPodatke(){
        return !kraj && podaci.empty();
    }
};

/** Klasa koja modeluje "postansko sanduce" izmedju radnika i pisaca.
 */
template <typename T>
class IzlazniPodaci
{
private:
    mutex m;
    int br_radnika;
    condition_variable cv;
    bool kraj;
    queue<T> podaci;
public:
    IzlazniPodaci() : br_radnika(0), kraj(false) {}

    void dodaj(T obradjeni_podaci)
    {
        unique_lock<mutex> ul(m);
        podaci.push(obradjeni_podaci);
        cv.notify_one();
    }

    bool preuzmi(T &obradjeni_podaci)
    {
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

    void dodajRadnika(){
        unique_lock<mutex> ul(m);
        br_radnika++;
    }
    void odjaviRadnika(){
        unique_lock<mutex> ul(m);
        br_radnika--;
        if(!br_radnika){
            kraj = true;
            cv.notify_all();
        }
    }

    bool jeLiKraj(){
        return kraj && podaci.empty();
    }
    bool daLiCekamPodatke(){
        return !kraj && podaci.empty();
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
/*
vector<double> izdvoj_brojeve(const string red_datoteke, unsigned &id, unsigned char &komanda)
{
    
}
*/

vector<double> sortiraj_opadajuce(vector<double> tokeni){
    sort(tokeni.begin(), tokeni.end(), greater<double>());
    return tokeni;
}

vector<double> kumulativna_suma(vector<double> tokeni){
    double suma = 0;
    vector<double> izlaz;
    for(int i=0;i<tokeni.size();i++){
        suma += tokeni[i];
        izlaz.push_back(suma); // ili suma+i -> tekst ima drugaciji primer nego sto pise
    }
    return izlaz;
}

vector<double> obrnuti_broj(vector<double> tokeni){
    vector<double> izlaz;
    for(double broj : tokeni){
        bool negativan = broj < 0;
        broj = abs(broj);

        long long ceo_deo = (long long)broj;
        double decimalni_deo = broj - ceo_deo;

        // Obrni ceo deo
        long long obrnuti_ceo = 0;
        while(ceo_deo > 0){
            obrnuti_ceo = obrnuti_ceo * 10 + ceo_deo % 10;
            ceo_deo /= 10;
        }

        // Obrni decimalni deo: 0.91 -> cifre "91" -> obrni -> "19" -> 0.19
        string dec_str = to_string(decimalni_deo).substr(2); // iza "0."
        // ukloni trailing nule
        while(dec_str.size() > 1 && dec_str.back() == '0')
            dec_str.pop_back();
        reverse(dec_str.begin(), dec_str.end());
        double obrnuti_dec = stod("0." + dec_str);

        // Obrnuti i znak prema specifikaciji
        double rezultat = obrnuti_dec + obrnuti_ceo;
        if (negativan){
            rezultat *= -1;
        }
        izlaz.push_back(rezultat);
    }
    return izlaz;
}

/**
 * Logika radnika - niti koje vrse transformaciju ulaznih podataka u izlazne
 * podatke spremne za ispis.
 */
void radnik_nit(UlazniPodaci<string> &ulaz, IzlazniPodaci<struct izlazni_podaci> &izlaz)
{
    izlaz.dodajRadnika();
    string linija;

    while(ulaz.preuzmi(linija)){
        stringstream ss(linija);
        string token;
        vector<double> tokeni;
        tokeni.resize(0);
        int i=0;
        unsigned int id;
        unsigned char komanda;
        while(getline(ss,token,'|')){
            if(i==0){
                id = stoi(token);
            }else if (i==1){
                komanda = stoi(token);  // ascii vrednost broja koji je token
            }else{
                tokeni.push_back(stod(token));
            }
            i+=1;
        }
        vector<double> izlazni_vektor;
        if(komanda == 1){
            izlazni_vektor = sortiraj_opadajuce(tokeni);
        }else if (komanda == 2){
            izlazni_vektor = kumulativna_suma(tokeni);
        }else{
            izlazni_vektor = obrnuti_broj(tokeni);
        }
        struct izlazni_podaci struktura;
        struktura.ID = id;
        struktura.brojevi = izlazni_vektor;
        izlaz.dodaj(struktura);
    }
    izlaz.odjaviRadnika();
}

/**
 * Logika citaca - nit koja radi citanje iz ulazne datoteke i salje u ulaznu
 * kolekciju za radnike
 */
void citac_nit(UlazniPodaci<string> &ulaz){

    ifstream dat("ulaz.txt");
    string s;

    while(getline(dat,s)){
        ulaz.dodaj(s);
    }

    ulaz.objaviKraj();
}

/**
 * Logika stampaca - nit koja radi pisanje u izlaznu datoteku podataka dobijenih
 * od radnika
 */
void stampac_nit(IzlazniPodaci<struct izlazni_podaci> &izlaz)
{
    string o_fname;
    struct izlazni_podaci podaci;
    while(izlaz.preuzmi(podaci)){
        if(podaci.ID % 2 == 0){
            o_fname = "parni.txt";
        }else{
            o_fname = "neparni.txt";
        }

        ofstream dat(o_fname,ios::app);
        if(dat.is_open()){
            dat<<podaci.ID<<";";

            for(int i=0; i<podaci.brojevi.size()-1;i++){
                dat<<podaci.brojevi[i]<<";";
            }
            dat<<podaci.brojevi[podaci.brojevi.size()-1]<<"\n";
            dat.close();

        }else{
            cerr<<"STAMPAC: nemoguce otvoriti fajl.\n";
        }
    }
}

int main()
{
    IzlazniPodaci<struct izlazni_podaci> izlaz;
    UlazniPodaci<string> ulaz;

    ofstream("parni.txt").close();
    ofstream("neparni.txt").close();
    ofstream("kanta.txt").close();

    thread radnici[BROJ_RADNIKA];
    thread t1 = thread(citac_nit, ref(ulaz));
    thread t2 = thread(stampac_nit, ref(izlaz));


    for(int i=0;i<BROJ_RADNIKA;i++){
        radnici[i] = thread(radnik_nit, ref(ulaz), ref(izlaz));
    }
    t1.join();
    for(int i=0;i<BROJ_RADNIKA;i++){
        radnici[i].join();
    }
    t2.join();

    exit(0);
}