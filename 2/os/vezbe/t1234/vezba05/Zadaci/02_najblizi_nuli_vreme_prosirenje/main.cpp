/*
Proširiti zadatak najbilzi_nuli_vreme ispisom u sekundama i minutima.
*/

/*
Napraviti konkurentni program koji pronalazi element najbliži broju 0 u zadatom vektoru brojeva.

Pretragu podeliti u 3 programske niti. Ulazni vektor brojeva treba da sadrži 900.000 slučajno generisanih brojeva.

Za svaku nit, evidentirati trenutke kada je izvršavanje počelo i kada se završilo. 
Na kraju programa, ispisati koliko je trajalo izvršavanje svake niti u milisekundama.
*/

#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <mutex>

using namespace std;
using namespace chrono;

typedef vector<double>::const_iterator cit;

mutex m;
struct vreme {
    system_clock::time_point pocetak;
    system_clock::time_point kraj;
};

void f(cit pocetak, cit kraj, double & min, struct vreme * v) {
	// Implementirati...
    auto const start = system_clock::now();
    min = *pocetak;
    for(auto it=pocetak+1; it!=kraj;++it){
        
        if( abs(*it) < abs(min) ){
            // unique_lock<mutex> ul(m);
            // linija gore ne treba jer svaka nit dobije svoj minimum, nema preplitanja
            min = *it;
        }
    }
    auto const finish = system_clock::now();

    v->pocetak = start;
    v->kraj = finish;
}

const int BROJ_NITI = 3;
const int DUZINA = 900000;

int main() {
    int SEGMENT = DUZINA / BROJ_NITI;
    default_random_engine gen;

    gen.seed(duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count());// Inicijalizacija generatora slučajnih brojeva da pri svakom pokretanju daje različite brojeve
    uniform_real_distribution<double> real_dist(-1e5, 1e5);

    vector<double> v(DUZINA);
    // Puni se vektor pseudo-slučajnim brojevima
    for (int i = 0; i < DUZINA; i++)
       v[i] = real_dist(gen);

    double minimumi[BROJ_NITI];  // Niz elemenata najbližih nuli - svaka programska nit će dati svoj međurezltat
    struct vreme vremena[BROJ_NITI]; // Niz struktura u koji će biti upisani podaci o trajanju izvršavanja svake niti

    thread niti[BROJ_NITI];

	// Implementirati...

    cit it1 = v.begin();
    cit it2 = it1 + SEGMENT;

    for(int i=0;i<BROJ_NITI;i++){
        niti[i] = thread(f, it1, it2, ref(minimumi[i]), &vremena[i]);
        it1 += SEGMENT;
        it2 += SEGMENT;
    }

    for(int i=0;i<BROJ_NITI;i++){
        niti[i].join();
    }

    double minimum = minimumi[0];

    for(int i=0; i<BROJ_NITI;i++){
        if( abs(minimumi[i]) < abs(minimum)){
            minimum = minimumi[i];
        }

        /*
        duration<double, milli> trajanje = vremena[i].kraj - vremena[i].pocetak;
        duration<double> sekunde = vremena[i].kraj - vremena[i].pocetak;
        duration<double, ratio<60>> minuti = vremena[i].kraj - vremena[i].pocetak;

        cout<<"\nIzvrsavanje "<<i+1<<". niti trajalo je "<<minuti.count()<<" minuta, ";
        cout<<sekunde.count()<<" sekundi i ";
        cout<<trajanje.count()<<" milisekundi.";
        */

        duration<long long, milli> ukupno = duration_cast<duration<long long, milli>>(
            vremena[i].kraj - vremena[i].pocetak
        );

        long long ms_ukupno = ukupno.count();
        long long min_deo = ms_ukupno / 60000;
        long long sek_deo = (ms_ukupno % 60000) / 1000;
        long long ms_deo = ms_ukupno % 1000;

        cout << "\nIzvrsavanje " << i+1 << ". niti trajalo je "
        << min_deo << " minuta, "
        << sek_deo << " sekundi i "
        << ms_deo  << " milisekundi.";

    }

    cout<<endl<<endl<<"Vrednost najbliza nuli je "<<minimum<<endl;


    return 0;
}

