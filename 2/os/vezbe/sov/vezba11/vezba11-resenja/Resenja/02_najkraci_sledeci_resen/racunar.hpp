#ifndef RACUNAR_HPP_INCLUDED
#define RACUNAR_HPP_INCLUDED

#include "dijagnostika.hpp"
#include <memory>
#include <queue>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono;

struct Proces {
  condition_variable cv;
  int trajanje;
  int id;
  Proces(int t, int i) : trajanje(t), id(i) {}
};

class Racunar {
private:
  Dijagnostika &dijagnostika;

  /* prioritetni red je struktura podataka slicna obicnom redu, ali se iz njega
   * ne izlazi po FIFO principu vec postoji neko pravilo koje odredjuje
   * prioritet
   *
   * u nasem slucaju veci prioritet imaju procesi cije je vreme
   * cekanja krace
   *
   * ako ne definisemo nasu funkciju za poredjenje podrazumevano ponasanje
   * prioritetnog reda je da najveci element ima prioritet, sto svakako nema
   * smisla u nasem slucaju jer poredimo strukture a ne brojeve
   *
   * funkcija za poredjenje u prioritetnom redu radi suprotno logici koju smo
   * navikli da vidimo u, recimo, funkciji za poredjenje kod sort algoritma, pa
   * zbog toga pitamo da li je a->trajanje VECE od b->trajanje iako zelimo da
   * MANJE trajanje ima veci prioritet
   *
   * napomena: sve ovo moze da se uradi i uz pomoc vektora, ali onda morate pri
   * svakom rasporedjivanju traziti poziciju elementa sa najkracim trajanjem i
   * pozivati vector.erase(), sto nije efikasno
   */
  static bool cmp(shared_ptr<Proces> a, shared_ptr<Proces> b) {
    return a->trajanje > b->trajanje;
  }
  // prioritetni red prima 3 template parametra:
  // 1. tip podatka koji cuvamo u njemu (koristimo shared_ptr<Proces> umesto
  // samo Proces jer Proces sadrzi uslovnu promenljivu koja se ne sme kopirati)
  // 2. kontejner koji se koristi u pozadini da cuva podatke (vector je default
  // opcija)
  // 3. funkcija za odredjivanje prioriteta elemenata (slicno kao lambda koju
  // prosledjujemo sort funkciji)
  // sve ovo je jako lepo dokumentovano na cppreference
  // https://cppreference.com/cpp/container/priority_queue
  priority_queue<shared_ptr<Proces>, vector<shared_ptr<Proces>>,
                 decltype(&Racunar::cmp)>
      procesi;
  int aktivan_proces;
  mutex procesor_mtx;
  bool rasporedjivac_aktivan;
  condition_variable racunar_cv;

public:
  Racunar(Dijagnostika &d) : dijagnostika(d), procesi(cmp) {
    aktivan_proces = -1;
    rasporedjivac_aktivan = false;
  }

  Dijagnostika &getDijagnostika() { return dijagnostika; }

  // Metoda koju poziva nit koja simulira izvršenje procesa, kako bi se proces
  // izvršio
  //
  // id_procesa   - ID procesa
  // trajanje     - trajanje procesa (izraženo u stotinama milisekundi)
  //
  // Ukoliko je procesor već zauzet i ne mogu se izvršavati naredbe procesa,
  // potrebno je pozvati metodu dijagnostika.proces_ceka a nakon toga proces
  // treba da pređe u stanje čekanja. Nakon što se proces izvršio, potrebno je
  // pozvati dijagnostika.proces_zavrsio.
  void izvrsi(int id_procesa, int trajanje) {
    shared_ptr<Proces> p = make_shared<Proces>(trajanje, id_procesa);

    unique_lock<mutex> l(procesor_mtx);

    if (aktivan_proces ==
        -1) { // prvi proces nailazi na slobodan procesor pa ga zauzima, jednom
              // kada ga zauzme izvrsice sve svoje naredbe
      aktivan_proces = id_procesa;
    } else {
      // svi ostali koji naidju na zauzet procesor ce biti u
      // opticaju da budu izabrani prilikom rasporedjivanja
      procesi.push(p);
    }

    while (aktivan_proces != id_procesa) {
      dijagnostika.proces_ceka(id_procesa);
      p->cv.wait(l);
    }

    l.unlock();
    this_thread::sleep_for(milliseconds(100 * trajanje));
    l.lock();

    dijagnostika.proces_zavrsio(id_procesa);

    rasporedjivac_aktivan = true;
    racunar_cv.notify_one();
  }

  // Metoda koju poziva nit koja simulira raspoređivač operativnog sistema, kako
  // bi se izabrao sledeći proces za izvršenje.
  //
  // Ukoliko još uvek ne postoji potreba da se raspoređivač aktivira, potrebno
  // je pozvati metodu dijagnostika.rasporedjivac_ceka a nakon toga nit treba da
  // pređe u stanje čekanja. Nakon što se raspoređivač aktivirao i izabrao
  // sledeći proces, potrebno je pozvati dijagnostika.rasporedjivac_izvrsio.
  void rasporedjuj() {
    unique_lock<mutex> l(procesor_mtx);
    while (true) {
      while (!rasporedjivac_aktivan) {
        dijagnostika.rasporedjivac_ceka();
        racunar_cv.wait(l);
      }

      if (procesi.size() > 0) {
        // posto koristimo prioritetni red, top i pop nam garantuju da je u
        // pitanju element sa najkracim trajanjem
        shared_ptr<Proces> sledeci = procesi.top();
        procesi.pop();
        sledeci->cv.notify_one();
        aktivan_proces = sledeci->id;
      } else {
        aktivan_proces = -1;
      }

      rasporedjivac_aktivan = false;
      dijagnostika.rasporedjivac_izvrsio(aktivan_proces);
    }
  }
};

#endif // RACUNAR_HPP_INCLUDED
