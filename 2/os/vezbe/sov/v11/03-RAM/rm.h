#ifndef RADNA_MEMORIJA_H_INCLUDED
#define RADNA_MEMORIJA_H_INCLUDED

#include "tip_procesa.h"
#include "dijagnostika.h"
#include <mutex>
#include <condition_variable>
#include <deque>
#include <algorithm>
#include <queue>
#include <list>

using namespace std;
using namespace chrono;

class Zahtev {
public:
	int broj_okvira;
	int id_procesa;
	Tip_procesa::tip_procesa tip_procesa;
	bool obradjen;
	condition_variable cv;
	Zahtev(int n_okvira, int pid, Tip_procesa::tip_procesa t) : broj_okvira(n_okvira), id_procesa(pid), tip_procesa(t), obradjen(false) {}
};

class Radna_memorija {
private:
	Dijagnostika& dijagnostika;
	vector<int> memorija;
	int broj_slobodnih_okvira;
	queue<shared_ptr<Zahtev>> sistemski_zahtevi;
	vector<shared_ptr<Zahtev>> korisnicki_zahtevi;
	mutex m;

	condition_variable cekam_procese, cekam_oslobodjenje;

public:
	// parametar ukupno_okvira - ukupan broj okvira u radnoj memoriji
	Radna_memorija(Dijagnostika& d, int ukupno_okvira) : dijagnostika(d) {
		memorija.resize(ukupno_okvira, -1);
		broj_slobodnih_okvira = ukupno_okvira;
	}

	Dijagnostika& getDijagnostika() {
		return dijagnostika;
	}

	// parametar broj_okvira - koliko okvira treba procesu za izvršavanje
	// parametar id_procesa  - jedinstveni identifikator procesa
	// parametar tip_procesa - da li je proces USER ili SYSTEM
	// nakon što pošalje zahtev, proces mora da sačeka dok opslužilac ne zauzme zahtevani broj okvira
	// i tada je potrebno pozvati metodu proces_ceka
	void napravi_zahtev(int memProcesa, int pid, Tip_procesa::tip_procesa t) {
		unique_lock<mutex> l(m);

		shared_ptr<Zahtev> zahtev = make_shared<Zahtev>(memProcesa,pid,t);
		if(t == 0){
			sistemski_zahtevi.push(zahtev);
			cekam_procese.notify_one();
		}else{
			korisnicki_zahtevi.push_back(zahtev);
			cekam_procese.notify_one();
		}

		while(zahtev->obradjen == false){
			dijagnostika.proces_ceka(pid,memProcesa,t);
			zahtev->cv.wait(l);
		}

	}

	// parametar id_procesa  - jedinstveni identifikator procesa
	void oslobodi(int id_procesa) {
		unique_lock<mutex> l(m);
		int brojac = 0;

		for(int i=0; i<memorija.size();i++){
			if(memorija[i] == id_procesa){
				memorija[i] = -1;
				brojac+=1;
			}
		}

		broj_slobodnih_okvira += brojac;

		cekam_oslobodjenje.notify_all();
		
	}

	// potrebno pozvati metodu ispisi_okvire nakon što proces zauzme okvire
	// potrebno pozvati metodu proces_zauzeo proces zauzme okvire
	void opsluzi() {
		// Implementirati
		unique_lock<mutex> l(m);
		while(true){

			while(sistemski_zahtevi.size() == 0 && korisnicki_zahtevi.size()==0){
				cekam_procese.wait(l);
			}
			
			if(sistemski_zahtevi.size() == 0 && korisnicki_zahtevi.size()==0){
				return;
			}
			
			if(sistemski_zahtevi.size()>0){
				// prvo se obradjuju sistemski

				for(int i=0;i<sistemski_zahtevi.size();i++){
					shared_ptr<Zahtev> zahtev = sistemski_zahtevi.front();

					while(broj_slobodnih_okvira < zahtev->broj_okvira){
						cekam_oslobodjenje.wait(l);
					}

					int j=0;
					while(j != zahtev->broj_okvira){
						for(int k=0;k<memorija.size();k++){
							if(memorija[k]==-1){
								memorija[k] = zahtev->id_procesa;
								j++;
							}
							if(j == zahtev->broj_okvira)
								break;
						}
						if(j == zahtev->broj_okvira)
								break;
					}

					broj_slobodnih_okvira -= zahtev->broj_okvira;

					dijagnostika.proces_zauzeo(zahtev->id_procesa, zahtev->broj_okvira, zahtev->tip_procesa);
            		dijagnostika.ispisi_okvire(memorija.begin(), memorija.end());

					zahtev->obradjen = true;
					zahtev->cv.notify_one();
					sistemski_zahtevi.pop();
				}

				
			}
			else{
				// korisnicki zahtevi
				for(int i=0;i<korisnicki_zahtevi.size();i++){
					int idx_najmanjih_okvira = 0;
					int br_najmanjih_okvira = korisnicki_zahtevi[0]->broj_okvira;

					for(int j=0;j<korisnicki_zahtevi.size();j++){
						if(korisnicki_zahtevi[j]->broj_okvira < br_najmanjih_okvira){
							br_najmanjih_okvira = korisnicki_zahtevi[j]->broj_okvira;
							idx_najmanjih_okvira = 0;
						}
					}

					shared_ptr<Zahtev> zahtev = korisnicki_zahtevi[idx_najmanjih_okvira];

					for(auto it = korisnicki_zahtevi.begin(); it!=korisnicki_zahtevi.end();it++){
						shared_ptr<Zahtev> zahtev2 = *it;
						if(zahtev->id_procesa == zahtev2->id_procesa){
							korisnicki_zahtevi.erase(it);
							break;
						}
					}

					while(broj_slobodnih_okvira < zahtev->broj_okvira){
						cekam_oslobodjenje.wait(l);
					}

					int j=0;
					while(j != zahtev->broj_okvira){
						for(int k=0;k<memorija.size();k++){
							if(memorija[k]==-1){
								memorija[k] = zahtev->id_procesa;
								j++;
							}
							if(j == zahtev->broj_okvira)
								break;
						}
						if(j == zahtev->broj_okvira)
								break;
					}
					
					broj_slobodnih_okvira -= zahtev->broj_okvira;

					dijagnostika.proces_zauzeo(zahtev->id_procesa, zahtev->broj_okvira, zahtev->tip_procesa);
            		dijagnostika.ispisi_okvire(memorija.begin(), memorija.end());

					zahtev->obradjen = true;
					zahtev->cv.notify_one();

				}
			}
		}
		
	}
};



#endif // RADNA_MEMORIJA_H_INCLUDED
