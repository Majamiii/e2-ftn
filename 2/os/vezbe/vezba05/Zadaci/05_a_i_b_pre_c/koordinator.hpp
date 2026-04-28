#ifndef KOORDINATOR_HPP_INCLUDED
#define KOORDINATOR_HPP_INCLUDED

#include <condition_variable>

using namespace std;

class Koordinator {
private:
    const int cekam_niti;     // Konstanta koja govori koliko niti se čeka na završetak pre nego što se aktivira poslednja.
    static int broj_zavrsenih_niti;
    condition_variable dozvoljeno;
    mutex m;
public:
    Koordinator(int cn) : cekam_niti(cn) {
        // Proširiti po potrebi ...
    }

    // Metoda koju na svom KRAJU zovu niti (a i b) koje ne čekaju (izvršavaju se odmah).
    void zavrsio() {
        // Implementirati ...
        broj_zavrsenih_niti += 1;
        unique_lock<mutex> ul(m);
        if(broj_zavrsenih_niti == cekam_niti){
            dozvoljeno.notify_one();
        }
    }

    // Metodu koju na svom POČETKU zovu niti (c) koje čekaju (ne izvršavaju se odmah).
    void cekam() {
        // Implementirati ...
        unique_lock<mutex> ul(m);
        while (broj_zavrsenih_niti != cekam_niti){
            dozvoljeno.wait(ul);
        }
    }
};

#endif // KOORDINATOR_HPP_INCLUDED
