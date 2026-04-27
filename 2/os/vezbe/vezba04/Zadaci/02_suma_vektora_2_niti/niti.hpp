#ifndef NITI_HPP_INCLUDED
#define NITI_HPP_INCLUDED

#include <vector>
#include <thread>

#include "suma_vektora.hpp"

typedef vector<double>::const_iterator ci;

using namespace std;

// v - vektor čije elemente treba sumirati
// povratna vrednost - suma svih elemenata vektora, izračunata pokretanjem 2 niti (svaka treba da obradi jednu polovinu elemenata)
void niti(ci pocetak, ci kraj, double& zbir) {
    // Implementirati ...
    zbir=0.0;
    for(;pocetak!=kraj;++pocetak){
        zbir += *pocetak;
    }
}


double sumiraj(vector<double> v) {
    // Implementirati ...
    int n = v.size() / 2;
    ci pola = v.begin() + n;

    double zbir1 = 0;
    double zbir2 = 0;

    thread nit1 = thread(niti, v.begin(), pola, ref(zbir1));
    thread nit2 = thread(niti, pola, v.end(), ref(zbir2));

    nit1.join();
    nit2.join();

    return zbir1+zbir2;
}


#endif // NITI_HPP_INCLUDED
