#ifndef NITI_HPP_INCLUDED
#define NITI_HPP_INCLUDED

#include <vector>
#include <thread>
#include <numeric>

#include "suma_vektora.hpp"

typedef vector<double>::const_iterator ci;

using namespace std;

// v - vektor čije elemente treba sumirati
// n - koliko niti treba pokrenuti
// povratna vrednost - suma svih elemenata vektora, izračunata pokretanjem n niti (svaka nit treba da obradi jedan deo elemenata)

void niti(ci pocetak, ci kraj, double& zbir) {
    // Implementirati ...
    zbir=0.0;
    for(;pocetak!=kraj;++pocetak){
        zbir += *pocetak;
    }
}


double sumiraj(vector<double> v, int n) {
    // Implementirati ...
    int d = v.size() / n;
    vector<double> zbir(n);
    vector<thread> nit(n);

    vector<double>::iterator curr = v.begin();
    vector<double>::iterator next = v.begin()+d;

    for(int i=0; i<n-1; ++i){
        nit[i] = thread(niti, curr, next, ref(zbir[i]));
        curr += d;
        next += d;
    }

    nit[n-1] = thread(niti, curr, v.end(), ref(zbir[n-1]));

    for(int i=0;i<n;i++){
        nit[i].join();
    }

    return accumulate(zbir.begin(), zbir.end(), 0);
}



#endif // NITI_HPP_INCLUDED
