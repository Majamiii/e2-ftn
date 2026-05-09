#ifndef SKLADISTE_HPP_INCLUDED
#define SKLADISTE_HPP_INCLUDED

#include "kamion_ognjen.hpp"
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;
using namespace chrono;
class Skladiste {
private:
	Kamion& kamion;
	mutex prilaz_skladistu;
	condition_variable boom, normal;
	int freeRampCounter = 2;
	int boomCount;

public:
	Skladiste(Kamion& k) : kamion(k) {
		// Prosiriti po potrebi ...
	}

	// Metoda koju poziva nit koja simulira kretanje kamiona kada on pokusava da istovari robu.
	// Metoda je blokirajuca - ako su sve rampe za istovar zauzete, izvrsenje ce blokirati dok se neka ne oslobodi.
	//
	// rbr       - Redni broj kamiona
	// kolicina  - Kolicina robe koja se prevozi (u tonama)
	// zapaljivo - Ukazuje na to da li je roba koja se prevozi zapaljiva (takva roba ima prioritet pri istovaru!)
	//
	// Potrebno je pozvati metodu kamion.ceka kada su rampe zauzete i kamion mora da ceka.
	// Potrebno je pozvati metodu kamion.istovara kada zapocne istovar robe iz kamiona (primetiti da ta metoda zahteva da joj se prosledi indeks rampe na kojoj se obavlja istovar!)
	// Potrebno je pozvati metodu kamion.odlazi kada je kamion zavrsio istovar i odlazi.

	void istovari(int rbr, int kolicina, bool zapaljivo) {
		// Prosiriti po potrebi ...
		
		{
			unique_lock<mutex> freeEntry(prilaz_skladistu);

			if (zapaljivo) {
				while (true)
				{
					if (freeRampCounter > 0) {
						kamion.istovara(rbr, kolicina, zapaljivo, freeRampCounter);
						boomCount++;
						freeRampCounter--;
						break;
					}
					else {
						kamion.ceka(rbr, kolicina, zapaljivo);
						boom.wait(freeEntry);
					}
				}
			}
			else {
				normal.wait(freeEntry);
				kamion.ceka(rbr, kolicina, zapaljivo);
				
				while (true)
				{
					if (freeRampCounter > 0) {
						kamion.istovara(rbr, kolicina, zapaljivo, freeRampCounter);
						freeRampCounter--;
						break;
					} 
					else {
						kamion.ceka(rbr, kolicina, zapaljivo);
						normal.wait(freeEntry);
					}
				}
			}
		}

		this_thread::sleep_for(milliseconds(kolicina));

		{
			unique_lock<mutex> freeExit(prilaz_skladistu);

			if (zapaljivo == true){
				freeRampCounter++;
				boomCount--;
				cout << boomCount << endl;

				boom.notify_one();
			}

			if (boomCount == 0) {
				normal.notify_one();
			}

			if (zapaljivo == false) {
				kamion.odlazi(rbr);
				freeRampCounter++;
				normal.notify_one();
				
			}

		}
	
	}
};

#endif // SKLADISTE_HPP_INCLUDED