/*
Napraviti konkurentni C++ program koji iz ulazne datoteke "ulaz.txt"
po redovima obrađuje podatke i potom rezultat smešta u izlazne datoteke
"ponovo3.txt" i "ostali.txt".

U svakoj ulaznoj datoteci su podaci podeljeni delimiterom ',' i prate
sledeći format:

1. broj: ID, unsigned int
2. broj: komanda, unsigned char, određuje šta treba raditi sa brojevima
          koji slede, pri tome obititi pažnju je i komanda takođe BROJ
3+. brojevi: brojevi, double, koje treba obraditi po definiciji komande

Ulazna datoteka je "ulaz.txt".

Komande koje postoje su:
1) počevši od nule svaki prvi razlomljeni broj dodati rezultatu a svaki
   drugi oduzeti
2) naći minimum razlomljenih brojeva
3) podrazumevati su navedeni razlomljeni brojevi redom brojevi a, b,
   c, d; izračunati e gde je:
   e = (a + 2b + 3c + 4d) / 10
4) odbaciti brojeve deljive sa 7
5) sortirati ulazno razlomljene brojeve

U svakoj izlaznoj datoteci su podaci nakon transformacije upisani u jedan
red, podeljeni delimiterom ',' da prate sledeći format:

1. broj: ID, nepoznaceo ceo broj
2+. brojevi: razlomljeni broj/evi dobijen/i transformacijom na osnovu
              komande

Izlazni podaci se raspoređuju u izlazne datoteke i to:
- "ponovo3.txt"  -> rezultati za unose sa neparnim dvocifrenim ID-om
- "ostali.txt"   -> za sve ostale rezultate

Treba napraviti jednu čitac nit koja će samo čitati redove iz ulaznih
datoteka, jednu stampac nit koja će samo pisati izlazne podatke u izlazne
datoteke i 9 niti radnika koji će transformisati ulazne podatke u izlazne.

NAPOMENE:
Komanda 0 nikada neće postojati u ulaznim datotekama.
Redove sa nepostojećim komandama napisati u datoteku "kanta.txt" tako da
budu ispisani ID, komanda i potom polazni brojevi podeljeni delimiterom ','.
*/

#include <string>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <numeric>
#include <algorithm>

#define BROJ_RADNIKA 9

using namespace std;

struct trio{
    int id;
    unsigned int komanda;
    vector<double> brojevi;
};

template<typename T>
class UlazniPodaci{
    private:
    mutex m;
    condition_variable cv;
    bool kraj;
    queue<T> podaci;

    public:
    UlazniPodaci() : kraj(false) {}

    void dodajPodatak(T podatak){
        unique_lock<mutex> ul(m);
        podaci.push(podatak);
        cv.notify_one();
    }
    bool dajPodatak(T &podatak){
        unique_lock<mutex> ul(m);
        while(daLiCekamPodatke()){
            cv.wait(ul);
        }
        if(jeLiKraj()){
            return false;
        }

        podatak = podaci.front();
        podaci.pop();
        return true;
    }

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

template<typename T>
class IzlazniPodaci{
    private:
    mutex m;
    condition_variable cv;
    bool kraj;
    queue<T> podaci;
    int broj_radnika;

    public:
    IzlazniPodaci() : kraj(false), broj_radnika(0) {}

    void dodajPodatak(T podatak){
        unique_lock<mutex> ul(m);
        podaci.push(podatak);
        cv.notify_one();
    }
    bool dajPodatak(T &podatak){
        unique_lock<mutex> ul(m);
        while(daLiCekamPodatke()){
            cv.wait(ul);
        }
        if(jeLiKraj()){
            return false;
        }

        podatak = podaci.front();
        podaci.pop();
        return true;
    }

    void prijaviRadnika(){
        unique_lock<mutex> ul(m);
        broj_radnika++;
    }
    void odjaviRadnika(){
        unique_lock<mutex> ul(m);
        broj_radnika--;
        if(!broj_radnika){
            kraj = true;
            cv.notify_one();
        }
    }

    bool daLiCekamPodatke(){
        return !kraj && podaci.empty();
    }
    bool jeLiKraj(){
        return kraj && podaci.empty();
    }
};

void citac(UlazniPodaci<string> &input_data){
    ifstream dat("ulaz.txt");
    string linija;
    while(getline(dat,linija)){
        input_data.dodajPodatak(linija);
    }
    input_data.objaviKraj();
}

void pisac(IzlazniPodaci<struct trio> &output_data){
    string ime_dat;
    struct trio t;
    while(output_data.dajPodatak(t)){
        vector<double> brojevi = t.brojevi;
        if(t.komanda > 5){
            ime_dat = "kanta.txt";
        }else if (t.id >= 10 && t.id <= 99 && t.id % 2 == 1){
            ime_dat = "ponovo3.txt";
        }else{
            ime_dat = "ostali.txt";
        }

        ofstream dat(ime_dat, ios::app);
        if(dat.is_open()){

            dat << t.id;

            if(t.komanda > 5){
                dat<<","<<t.komanda;
            }

            for(int i=0;i<brojevi.size();i++){
                dat<<","<<brojevi[i];
            }
            dat<<"\n";
            
            dat.close();
        }else{
            cerr << "PISAC: nemoguce otvoriti izlazni fajl.\n";
        }

    }
}

// 1) počevši od nule svaki prvi razlomljeni broj dodati rezultatu a svaki drugi oduzeti
vector<double> komanda1(vector<double>& pocetni){
    vector<double> izlazni;

    int i=0;
    double suma = 0;
    for(auto it = pocetni.begin(); it != pocetni.end(); it++){
        if(i%2 == 0){
            suma += *it;
        }else{
            suma -= *it;
        }
        i+=1;
    }
    izlazni.push_back(suma);
    return izlazni;
}

// 2) naći minimum razlomljenih brojeva
vector<double> komanda2(vector<double>& pocetni){
    vector<double>::iterator minimum = min_element(pocetni.begin(), pocetni.end());
    vector<double> izlazni;
    izlazni.push_back(*minimum);
    return izlazni;
}

/*
3) podrazumevati su navedeni razlomljeni brojevi redom brojevi a, b,
   c, d; izračunati e gde je:
   e = (a + 2b + 3c + 4d) / 10
*/
vector<double> komanda3(vector<double>& pocetni){
    vector<double> izlazni;

    if(pocetni.size() != 4){
        cerr << "Nema onoliko brojeva koliko treba za komandu 3!\n";
        return izlazni;
    }
    izlazni.push_back( (pocetni[0] + 2*pocetni[1] + 3*pocetni[2] + 4*pocetni[3])/10 );
    return izlazni;
}
// 4) odbaciti brojeve deljive sa 7
vector<double> komanda4(vector<double>& pocetni){
    vector<double> izlazni;

    for(int i=0;i<pocetni.size();i++){
        int n = pocetni[i];
        if(n % 7 > 0){
            izlazni.push_back(n);
        }
    }
    return izlazni;
}
// 5) sortirati ulazno razlomljene brojeve
vector<double> komanda5(vector<double>& pocetni){
    sort(pocetni.begin(), pocetni.end());
    return pocetni;
}

void radnik(UlazniPodaci<string> &input_data, IzlazniPodaci<struct trio> &output_data){
    string linija;

    output_data.prijaviRadnika();

    while(input_data.dajPodatak(linija)){
        stringstream ss(linija);
        int id;
        string token;
        vector<double> brojevi;
        unsigned int komanda;
        struct trio t;

        int i=0;
        while(getline(ss,token,',')){
            if(i==0){
                id = stoi(token);
            }else if(i==1){
                komanda = stoi(token);
            }else{
                brojevi.push_back(stod(token));
            }
            i+=1;
        }
        t.id = id;
        t.komanda = komanda;
        
        if(komanda>5){
            t.brojevi = brojevi;
        }else{
            if(komanda == 1){
                t.brojevi = komanda1(brojevi);
            }else if(komanda == 2){
                t.brojevi = komanda2(brojevi);
            }else if(komanda == 3){
                t.brojevi = komanda3(brojevi);
            }else if(komanda == 4){
                t.brojevi = komanda4(brojevi);
            }else {
                t.brojevi = komanda5(brojevi);
            }
        }
        output_data.dodajPodatak(t);
    }
    output_data.odjaviRadnika();
}

int main(){
    UlazniPodaci<string> ulaz;
    IzlazniPodaci<struct trio> izlaz;
    thread radnici[BROJ_RADNIKA];

    ofstream("kanta.txt").close();
    ofstream("ponovo3.txt").close();
    ofstream("ostali.txt").close();

    thread t1 = thread(citac, ref(ulaz));
    thread t2 = thread(pisac, ref(izlaz));
    for(auto &it: radnici){
        it = thread(radnik, ref(ulaz), ref(izlaz));
    }

    t1.join();
    for(auto &it: radnici){
        it.join();
    }
    t2.join();

    return 0;
}