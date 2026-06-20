#ifndef MEMORIJA_HPP_INCLUDED
#define MEMORIJA_HPP_INCLUDED

#include <mutex>
#include <condition_variable>
#include <vector>
class Memorija {
private:
    vector<char> memorija;
    bool zauzeto;
    mutex m;
    condition_variable cv;
public:
    Memorija(int bajtova) {
        memorija.resize(bajtova, '0');
        zauzeto = false;
    }

    char citaj(int adresa) {
        unique_lock<mutex> l(m);
        while(zauzeto){
            cv.wait(l);
        }
        zauzeto = true;

        l.unlock();
        this_thread::sleep_for(chrono::milliseconds(300));
        l.lock();

        zauzeto = false;
        stanje = SLOBODNA;

        cv.notify_one();
        return memorija[adresa];
    }

    void pisi(int adresa, char vrednost) {
        unique_lock<mutex> l(m);
        while(zauzeto){
            cv.wait(l);
        }
        zauzeto = true;

        l.unlock();
        this_thread::sleep_for(chrono::milliseconds(300));
        l.lock();

        zauzeto = false;

        memorija[adresa] = vrednost;

        cv.notify_one();
    }
};

#endif // MEMORIJA_HPP_INCLUDED
