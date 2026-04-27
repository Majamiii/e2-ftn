#ifndef NITI_HPP_INCLUDED
#define NITI_HPP_INCLUDED

#include <vector>
#include <thread>

#include "suma_vektora.hpp"

using namespace std;

// v - vektor A čije elemente treba sumirati
// v - vektor B čije elemente treba sumirati
// povratna vrednost - suma korespondentnih elemenata vektora A i B, izračunata pozivanjem dve niti
vector<double> sumiraj(vector<double> a, vector<double> b) {
    // Implementirati ...
    int d = a.size() / 2;

    vector<double> sume(a.size());
    vector<double>::iterator it1 = sume.begin();
    vector<double>::iterator it2 = sume.begin()+d;

    thread nit1 = thread(f, a.begin(), a.begin()+d, b.begin(), it1);
    thread nit2 = thread(f, a.begin()+d, a.end(), b.begin()+d, it2);

    nit1.join();
    nit2.join();

    return sume;
}

#endif // NITI_HPP_INCLUDED
