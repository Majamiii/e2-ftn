/* 
Napisati program koji omogućava evidentiranje fakultetskih učionica.

Za svaku učionicu potrebno je evidentirati naziv učionice, kvadraturu i sve računare koji se nalaze u učionici. 
Za svaki računar evidentiraju se podaci o hard disku i procesoru.

U okviru main funkcije, definisati jednu učionicu koja sadrži dva računara.
Zatim je potrebno na konzolu ispisati hard disk i procesor svakog računara u učionici.
*/


#include <iostream>
#include <string>
#include <list>

#define MAX 100

using namespace std;

//klasa modeluje Racunar za koji se evidentira naziv diska i naziv procesora
class Racunar {
    private:
        string HDD;
        string CPU;
    public:
        void setHDD(string d) {
            HDD = d;
        }
        string getHDD() {
            return HDD;
        }
        void setCPU(string p) {
            CPU = p;
        }
        string getCPU() {
            return CPU;
        }
};

//klasa modeluje ucionicu za koju se evidentira naziv, kvadratura i racunari koji se nalaze u ucionici
class Ucionica {
    private:
        string naziv;
        double kvadratura;
        list<Racunar> racunari; //druga varijanta - racunari u ucionici su elementi STL kontejnera
    public:
        void setNaziv(string n) {
            naziv = n;
        }
        string getNaziv() {
            return naziv;
        }
        void setKvadratura(double kv) {
            kvadratura = kv;
        }
        double getKvadratura() {
            return kvadratura;
        }
        void dodajRacunar(Racunar r) {
            racunari.push_back(r); //ubacivanje objekta klase racunar u STL kontejner
        }
        list<Racunar> getRacunari() {
            return racunari;
        }
};




int main()
{
    Ucionica u;
    u.setNaziv("MIA2-3");
    u.setKvadratura(100);

    Racunar r1;
    r1.setHDD("Seagate");
    r1.setCPU("Intel i5");
    Racunar r2;
    r2.setHDD("Western Digital");
    r2.setCPU("Intel i7");

    u.dodajRacunar(r1);
    u.dodajRacunar(r2);

    list<Racunar> racunari = u.getRacunari(); //preuzimanje liste svih racunara
    list<Racunar>::iterator it;

    int i = 0;
    for (it = racunari.begin(); it != racunari.end(); it++, i++) {
        cout << "Procesor racunara[" << i << "]:" << it->getCPU() << endl;
        cout << "Disk racunara[" << i << "]:" << it->getHDD() << endl;
    }
}
