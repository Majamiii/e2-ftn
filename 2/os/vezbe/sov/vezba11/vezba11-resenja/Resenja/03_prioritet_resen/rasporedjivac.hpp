#ifndef RASPOREDJIVAC_HPP_INCLUDED
#define RASPOREDJIVAC_HPP_INCLUDED

#include "dijagnostika.hpp"
#include "red.hpp"
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono;

class Rasporedjivac {
private:
  Dijagnostika &dijagnostika;
  int aktivan_proces;
  mutex procesor_mtx;
  vector<Red> redovi;

public:
  Rasporedjivac(Dijagnostika &d, int broj_nivoa_prioriteta) : dijagnostika(d) {
    aktivan_proces = -1;
    for (int i = 0; i < broj_nivoa_prioriteta; i++) {
      redovi.push_back(Red());
    }
  }

  Dijagnostika &getDijagnostika() { return dijagnostika; }

  // Metoda koju poziva nit koja simulira izvršenje procesa, kako bi se proces
  // izvršio
  //
  // id_procesa   - ID procesa
  // broj_naredbi - ukupan broj naredbi koje proces treba da izvrši
  // prioritet    - prioritet procesa
  //
  // Ukoliko je procesor već zauzet i ne mogu se izvršavati naredbe procesa,
  // potrebno je pozvati metodu dijagnostika.proces_ceka, a nakon toga proces
  // treba da pređe u stanje čekanja. Nakon što je proces izvršio naredbu,
  // potrebno je pozvati dijagnostika.izvrsio_naredbu.
  void izvrsi(int id_procesa, int broj_naredbi, int prioritet) {
    // Implementirati ...
    for (int i = 0; i < broj_naredbi; i++) {
      unique_lock<mutex> l(procesor_mtx);

      if (aktivan_proces == -1) {
        aktivan_proces = id_procesa;
      }

      while (aktivan_proces != id_procesa) {
        dijagnostika.proces_ceka(id_procesa);
        redovi[prioritet].ubaci_u_red(l, id_procesa);
      }

      l.unlock();
      this_thread::sleep_for(milliseconds(300));
      l.lock();

      int sledeci_red = -1;

      for (int i = 0; i < redovi.size(); i++) {
        if (!redovi[i].prazan()) {
          sledeci_red = i;
          break;
        }
      }

      if (sledeci_red != -1) {
        if (sledeci_red <= prioritet || i == broj_naredbi - 1) {
          aktivan_proces = redovi[sledeci_red].izbaci_iz_reda();
        }

      } else {
        aktivan_proces = -1;
      }

      dijagnostika.izvrsio_naredbu(id_procesa, i);
    }
  }
};

#endif // RASPOREDJIVAC_HPP_INCLUDED
