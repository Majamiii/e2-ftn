#ifndef ZICARA_HPP_INCLUDED
#define ZICARA_HPP_INCLUDED

#include "putnik.hpp"
#include "list.hpp"

enum StanjeZicare {OTVORENA, ZATVORENA};

template <VrstaKarte SEZONA, int BROJ_SEDISTA, int INTERVAL>

class Zicara {
private:
    List<Putnik*> putnici;
    StanjeZicare stanje;
    int UkupnoVoznji, ukupnoMinuta;
public:
    Zicara():stanje(ZATVORENA), UkupnoVoznji(0), ukupnoMinuta(0) {};

    void otvori() {
        stanje = OTVORENA;
        ukupnoMinuta = 0;
        UkupnoVoznji = 0;
    }

    void zatvori() {
        stanje = ZATVORENA;
        putnici.clear();
    }

    bool DodajPutnika(Putnik* p) {
        if(p->getVrstaKarte()!=SEZONA) {
            return false;
        }
        Putnik* pom;

        for (int i = 0; i <= putnici.size(); i ++) {
            putnici.read(i, pom);

            if ((*pom).mb == (*p).ime) {
                return false;
            }
        }
        return putnici.add(putnici.size()+1, pom);
    }

    int BrojPutnika() const {
        return putnici.size();
    }

    bool PreveziTuru() {
        if(stanje == ZATVORENA || putnici.empty()) {
            return false;
        }
        if (BROJ_SEDISTA >= putnici.size()) {
            UkupnoVoznji =+ putnici.size();
            putnici.clear();
        } else {
            for(int i = 0; i < BROJ_SEDISTA; i++) {
                putnici.remove(1);
                UkupnoVoznji++;
            }
        }

        ukupnoMinuta += INTERVAL;
        return true;
    }

    friend ostream& operator<<(ostream& os, const Zicara& zic) {
        os << "Sezona: ";
        switch(SEZONA) {
        case(LETO):
            os<< "LETO"<<endl;
            break;
        case(SKI):
            os<<  "SKI"<<endl;
            break;
        case(SKI_OPENING):
            os<<  "SKI OPENING"<<endl;
            break;
        }
        os << "Broj sedista: " << BROJ_SEDISTA << endl;
        os << "Trajanje jedne voznje: " << INTERVAL << endl;
        os << "Stanje: " << (zic.stanje == 1 ? "ZATVORENA" : "OTVORENA" )<< endl;
        os << "Ukupan broj voznji: " << zic.ukupnoVoznji << endl;
        os << "Radno vreme(sati): " << zic.getRadnoVremeUSatima() << endl;
        os << "Broj putnika u redu: " << zic.putnici.size() << endl;

        if(zic.putnici.size()) {
            Putnik* pom;
            for(int i = 0; i < BROJ_SEDISTA; i++) {
                zic.putnici.read(i, pom);
                cout<<(*pom)<<endl;
            }


        }

        return os;
    }
    double getRadnoVremeUSatima() const {
        return (double)ukupnoMinuta / 60;
    }



};








#endif // ZICARA_HPP_INCLUDED
