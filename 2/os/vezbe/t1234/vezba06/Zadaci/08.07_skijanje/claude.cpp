#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <climits>
#include <algorithm>

/**
 * Program cita podatke o temperaturama na ski stazama (Kopaonik, Zlatibor, Jahorina)
 * i odredjuje koji dani su idealni za skijanje (temperatura od -5 do 3 stepena).
 *
 * Arhitektura niti:
 *   1 citac  -->  [RedoviIzDatoteke]  -->  4 radnika  -->  [PodaciZaIspis]  -->  1 pisac
 */

#define BR_RADNIKA 4
#define BR_MERENJA_TEMPERATURE 13
#define MINIMALNA_IDEALNA_TEMPERATURA -5
#define MAKSIMALNA_IDEALNA_TEMPERATURA 3

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Klasa koja cuva obradjene podatke za jedan dan na jednoj planini
// ─────────────────────────────────────────────────────────────────────────────
class StanjeSkijalistaNaDan {
private:
    string ime_planine;
    string ime_dana;
    string datum;
    int    min_temp;
    int    max_temp;
    bool   idealno;

public:
    StanjeSkijalistaNaDan() : min_temp(0), max_temp(0), idealno(false) {}

    StanjeSkijalistaNaDan(const string& planina,
                          const string& dan,
                          const string& dat,
                          int min_t,
                          int max_t)
        : ime_planine(planina), ime_dana(dan), datum(dat),
          min_temp(min_t), max_temp(max_t)
    {
        idealno = (min_t >= MINIMALNA_IDEALNA_TEMPERATURA &&
                   max_t <= MAKSIMALNA_IDEALNA_TEMPERATURA);
    }

    // Vraca string za ispis u izlaznu datoteku
    string getIspis() const {
        return ime_planine + " [" + ime_dana + " " + datum + "] " +
               to_string(min_temp) + " >> " + to_string(max_temp);
    }

    bool jeIdealno() const { return idealno; }
};


// ─────────────────────────────────────────────────────────────────────────────
// "Postansko sanduce" izmedju citaca i radnika
//   Jedan proizvodac (citac), vise potrosaca (radnici)
// ─────────────────────────────────────────────────────────────────────────────
template<typename T>
class RedoviIzDatoteke {
private:
    mutex              podaci_mx;
    condition_variable cv;
    queue<T>           podaci;
    bool               kraj;    // citac je zavrsio ucitavanje

public:
    RedoviIzDatoteke() : kraj(false) {}

    // Citac dodaje red iz datoteke
    void dodaj(T redIzDatoteke) {
        {
            unique_lock<mutex> lock(podaci_mx);
            podaci.push(move(redIzDatoteke));
        }
        cv.notify_one();  // probudi jednog radnika
    }

    // Citac javlja da je gotov sa svim datotekama
    void objavi_kraj() {
        {
            unique_lock<mutex> lock(podaci_mx);
            kraj = true;
        }
        cv.notify_all();  // probudi sve radnike da se mogu zavrsiti
    }

    // Radnik pokusava da preuzme red.
    // Vraca true i puni redIzDatoteke ako ima podataka.
    // Vraca false kada je kraj i nema vise podataka.
    bool preuzmi(T& redIzDatoteke) {
        unique_lock<mutex> lock(podaci_mx);
        // Cekaj dok ima smisla cekati
        cv.wait(lock, [this] { return !daLiCekamPodatke(); });
        if (jeLiKraj()) return false;
        redIzDatoteke = move(podaci.front());
        podaci.pop();
        return true;
    }

private:
    // Treba da cekamo: red je prazan, ali citac jos nije rekao kraj
    bool daLiCekamPodatke() {
        return !podaci.empty() || kraj;
    }

    // Stvarno je kraj: red je prazan I citac je rekao kraj
    bool jeLiKraj() {
        return podaci.empty() && kraj;
    }
};


// ─────────────────────────────────────────────────────────────────────────────
// "Postansko sanduce" izmedju radnika i pisaca
//   Vise proizvođaca (radnici), jedan potrosac (pisac)
// ─────────────────────────────────────────────────────────────────────────────
template<typename T>
class PodaciZaIspis {
private:
    mutex              podaci_mx;
    condition_variable cv;
    queue<T>           podaci;
    bool               kraj;                 // svi radnici su zavrsili
    int                br_stvaralaca_podataka; // koliko radnika je jos aktivno

public:
    PodaciZaIspis() : kraj(false), br_stvaralaca_podataka(0) {}

    // Radnik se prijavljuje na pocetku svog rada
    void prijavi_stvaraoca() {
        unique_lock<mutex> lock(podaci_mx);
        br_stvaralaca_podataka++;
    }

    // Radnik se odjavljuje na kraju svog rada
    void odjavi_stvaraoca() {
        {
            unique_lock<mutex> lock(podaci_mx);
            br_stvaralaca_podataka--;
            if (br_stvaralaca_podataka == 0) {
                kraj = true;
            }
        }
        cv.notify_all();  // moze biti da je pisac cekao – obavesti ga
    }

    // Radnik dodaje obradjene podatke
    void dodaj(T stanjeSkijalista) {
        {
            unique_lock<mutex> lock(podaci_mx);
            podaci.push(move(stanjeSkijalista));
        }
        cv.notify_one();
    }

    // Pisac preuzima podatak za ispis.
    // Vraca true i puni stanjeSkijalista ako ima podataka.
    // Vraca false kada nema vise nista.
    bool preuzmi(T& stanjeSkijalista) {
        unique_lock<mutex> lock(podaci_mx);
        cv.wait(lock, [this] { return !daLiCekamPodatke(); });
        if (jeLiKraj()) return false;
        stanjeSkijalista = move(podaci.front());
        podaci.pop();
        return true;
    }

private:
    bool daLiCekamPodatke() {
        return !podaci.empty() || kraj;
    }

    bool jeLiKraj() {
        return podaci.empty() && kraj;
    }
};


// ─────────────────────────────────────────────────────────────────────────────
// Nit citac: otvara svaku ulaznu datoteku i salje redove u red cekanja.
// Prefiks svakog reda je ime planine (ime datoteke bez ekstenzije).
// ─────────────────────────────────────────────────────────────────────────────
void citac(vector<string> imena_ulaznih_datoteka,
           RedoviIzDatoteke<string>& redovi_iz_ulaznih_datoteka)
{
    for (const auto& ime_datoteke : imena_ulaznih_datoteka) {
        ifstream f(ime_datoteke);
        if (!f.is_open()) {
            cout << "[UPOZORENJE] Datoteka \"" << ime_datoteke
                 << "\" ne postoji – preskacemo je.\n";
            continue;
        }

        // Izvuci ime planine iz naziva datoteke (bez ekstenzije)
        string ime_planine = ime_datoteke.substr(0, ime_datoteke.rfind('.'));

        string red;
        while (getline(f, red)) {
            if (red.empty()) continue;
            // Posalji "ImePlanine <ostatak reda>"
            redovi_iz_ulaznih_datoteka.dodaj(ime_planine + " " + red);
        }
    }

    // Sve datoteke procitane – obavesti radnike
    redovi_iz_ulaznih_datoteka.objavi_kraj();
}


// ─────────────────────────────────────────────────────────────────────────────
// Nit radnik: uzima redove, racuna min/max temperaturu, pravi StanjeSkijalistaNaDan
// ─────────────────────────────────────────────────────────────────────────────
void radnik(RedoviIzDatoteke<string>&            redovi_iz_ulaznih_datoteka,
            PodaciZaIspis<StanjeSkijalistaNaDan>& pripremljeni_podaci)
{
    pripremljeni_podaci.prijavi_stvaraoca();

    string red;
    while (redovi_iz_ulaznih_datoteka.preuzmi(red)) {
        istringstream ss(red);

        string ime_planine, ime_dana, datum;
        ss >> ime_planine >> ime_dana >> datum;

        int temp;
        int min_temp = INT_MAX;
        int max_temp = INT_MIN;

        for (int i = 0; i < BR_MERENJA_TEMPERATURE; ++i) {
            if (ss >> temp) {
                min_temp = min(min_temp, temp);
                max_temp = max(max_temp, temp);
            }
        }

        if (min_temp == INT_MAX) continue;  // prazan / neispravan red

        StanjeSkijalistaNaDan stanje(ime_planine, ime_dana, datum,
                                     min_temp, max_temp);
        pripremljeni_podaci.dodaj(stanje);
    }

    pripremljeni_podaci.odjavi_stvaraoca();
}


// ─────────────────────────────────────────────────────────────────────────────
// Nit pisac: upisuje podatke u "idealno.txt" ili "lose.txt"
// ─────────────────────────────────────────────────────────────────────────────
void pisac(PodaciZaIspis<StanjeSkijalistaNaDan>& pripremljeni_podaci)
{
    ofstream f_idealno("idealno.txt");
    ofstream f_lose("lose.txt");

    if (!f_idealno || !f_lose) {
        cerr << "[GRESKA] Ne mogu da otvorim izlazne datoteke!\n";
        return;
    }

    StanjeSkijalistaNaDan stanje;
    while (pripremljeni_podaci.preuzmi(stanje)) {
        if (stanje.jeIdealno()) {
            f_idealno << stanje.getIspis() << "\n";
        } else {
            f_lose    << stanje.getIspis() << "\n";
        }
    }
}


// ─────────────────────────────────────────────────────────────────────────────
// main
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    RedoviIzDatoteke<string>             redovi_iz_ulaznih_datoteka;
    PodaciZaIspis<StanjeSkijalistaNaDan> pripremljeni_podaci;

    vector<string> imena_ulaznih_datoteka = {
        "Kopaonik.txt",
        "Zlatibor.txt",
        "Jahorina.txt"
    };

    // Pokretanje niti
    thread th_reader(citac, imena_ulaznih_datoteka,
                     ref(redovi_iz_ulaznih_datoteka));

    thread th_writer(pisac, ref(pripremljeni_podaci));

    thread th_workers[BR_RADNIKA];
    for (auto& th : th_workers) {
        th = thread(radnik,
                    ref(redovi_iz_ulaznih_datoteka),
                    ref(pripremljeni_podaci));
    }

    // Cekanje na zavrsetak
    th_reader.join();

    for (auto& th : th_workers) {
        th.join();
    }

    th_writer.join();

    cout << "Obrada zavrsena. Pogledajte 'idealno.txt' i 'lose.txt'.\n";
    return 0;
}