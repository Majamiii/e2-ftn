#ifndef RADNA_MEMORIJA_H_INCLUDED
#define RADNA_MEMORIJA_H_INCLUDED

#include "tip_procesa.h"
#include "dijagnostika.h"
#include <mutex>
#include <condition_variable>
#include <deque>
#include <algorithm>
#include <list>

using namespace std;
using namespace chrono;

class Radna_memorija {
private:
    	Dijagnostika& dijagnostika;
        mutex mtx;
        condition_variable slobodan;
        condition_variable opsluzilac_cv;

        int kapacitetRAM;
        bool kraj;
        vector<int> memorija;
        
        struct ZAHTEV {
            int potrebnaMemorija;
            int PID;
            Tip_procesa::tip_procesa tipProcesa;
            bool spreman;
            condition_variable cv;
            ZAHTEV(int memProcesa, int pid, Tip_procesa::tip_procesa t) : potrebnaMemorija(memProcesa), PID(pid), tipProcesa(t) {};
        };

        deque<shared_ptr<ZAHTEV>> redZahtevaSYSTEM;
        list<shared_ptr<ZAHTEV>> redZAhtevaUSER;

        void dodaj_u_RAM(shared_ptr<ZAHTEV> z) {
            for (int i = 0; i < z->potrebnaMemorija; i++)
            {
                memorija.push_back(z->PID);
                cout << i << endl;
            }
        }

        shared_ptr<ZAHTEV> nadji_najkraci_zahtev_korisnika() {

            shared_ptr<ZAHTEV> z = redZAhtevaUSER.front();

           

            return z;
        }

public:
        // parametar ukupno_okvira - ukupan broj okvira u radnoj memoriji
        Radna_memorija(Dijagnostika& d, int ukupno_okvira) : dijagnostika(d) {
            // proširiti po potrebi
            kapacitetRAM = ukupno_okvira;
            memorija.resize(ukupno_okvira, -1); //memoriju predstavljam vektorom pidova, ima onoliko mesta koliko ima okvira, i svaki koriscen okvir ce imati vrednost pid-a, inicijalizovana sva polja kao -1
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

            unique_lock<mutex> l(mtx);
            shared_ptr<ZAHTEV> zahtev = NULL;

            if (t == Tip_procesa::SYSTEM) {
                zahtev = make_shared<ZAHTEV>(memProcesa, pid, t);
                redZahtevaSYSTEM.push_back(zahtev);
            }
            else {
                zahtev = make_shared<ZAHTEV>(memProcesa, pid, t);
                redZAhtevaUSER.push_back(zahtev);
            }

            opsluzilac_cv.notify_one();

            while (!zahtev->spreman) {
                dijagnostika.proces_ceka(pid, memProcesa, t);
                zahtev->cv.wait(l);
            }
        }

        // parametar id_procesa  - jedinstveni identifikator procesa
        void oslobodi(int id_procesa) {
            // Implementirati
            unique_lock<mutex> l(mtx);
            
            for (auto it = memorija.begin(); it != memorija.end(); it++)
            {
                if ((*it) == id_procesa) {
                    (*it) = -1;
                }
            }

            slobodan.notify_one();
        }

        // potrebno pozvati metodu ispisi_okvire nakon što proces zauzme okvire
        // potrebno pozvati metodu proces_zauzeo proces zauzme okvire
        void opsluzi() {
            // Implementirati
            unique_lock<mutex> l(mtx);

            shared_ptr<ZAHTEV> zahtev = NULL;

            while (redZahtevaSYSTEM.empty() && redZAhtevaUSER.empty())
            {
                opsluzilac_cv.wait(l);
            }

            if (!redZahtevaSYSTEM.empty()) {

                zahtev = redZahtevaSYSTEM.front(); //FIFO REDOSLED OCUVAVAN
                redZahtevaSYSTEM.pop_front();
            }
            else {

                auto prvi = redZAhtevaUSER.begin();

                for (auto iteratorZahteva = redZAhtevaUSER.begin(); iteratorZahteva != redZAhtevaUSER.end(); iteratorZahteva++)
                {
                    if ((*prvi)->potrebnaMemorija > (*iteratorZahteva)->potrebnaMemorija) {
                        (*prvi) = *iteratorZahteva;
                    }
                }
                zahtev = *prvi;

                redZAhtevaUSER.erase(prvi);

            }
            
            while (zahtev->potrebnaMemorija > count(memorija.begin(), memorija.end(), -1))
            {
                slobodan.wait(l);
            }

            int j = 0;

            for (auto it = memorija.begin(); it != memorija.end(); it++)
            {
                
                if ((*it) == -1){
                    (*it) = zahtev->PID;
                    j++;
                }
                
                if (j == zahtev->potrebnaMemorija) {
                    break;
                }

            }
           
            zahtev->spreman = true;
            dijagnostika.proces_zauzeo(zahtev->PID, zahtev->potrebnaMemorija, zahtev->tipProcesa);

            zahtev->cv.notify_all();

        }
};



#endif // RADNA_MEMORIJA_H_INCLUDED
