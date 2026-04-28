// Definisati klasu Parking koja modeluje Parking prostor kapaciteta jednog mesta.
// Ova klasa ima operacije: udji() i izadji().
//
// Automobili koji dolaze na Parking su predstavljeni programskim nitima. 
// Za ulazak na Parking, automobil poziva metodu udji(). 
// Za izlazak sa Parkinga, automobil poziva metodu izadji().
//
// Automobil se na Parkingu zadržava 3 sekunde. 
// Pri ulasku, ukoliko je Parking zauzet, automobil mora da sačeka da se Parking oslobodi.
//
// Implementirati označene metode u klasi Parking u fajlu parking.h

#include <thread>

#include "parking.hpp"

using namespace std;

void automobil(Parking& p, int rba) {
    p.udji();                        //Automobil pokusava da udje. Ukoliko je vec neko na Parkingu ulazi se u cekanje.
   { unique_lock<mutex> l(m);
      cout << "Automobil " << rba << " usao na Parking." << endl;  //Ispis ID-a niti automobila koji ulazi.
   }
    //Sleep automobila pri koriscenju Parkinga. Za to vreme svi ostali automobili cekaju, dok trenutni automobil ne izadje.
   this_thread::sleep_for(chrono::seconds(3));  
   p.izadji();                     //Automobil izlazi sa Parkinga. Notificira jednog od automobila koji cekaju da moze da udje.
   { unique_lock<mutex> l(m);    
      cout << "Automobil " << rba << " izasao sa Parkinga." << endl;  //Ispis ID-a niti automobila koji izlazi.
   }
}

const int automobila = 10;

int main() {
    Automobil a;
    Parking p(a);
    thread t[automobila];
    for(int i = 0; i < automobila; i++)
        t[i] = thread(automobil, ref(p), i + 1);
    for(int i = 0; i < automobila; i++)
        t[i].join();
    
    return 0;
}
