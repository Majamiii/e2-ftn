#ifndef PRODAVNICA_HPP_INCLUDED
#define PRODAVNICA_HPP_INCLUDED
#include "list.hpp"
#include "dinstring.hpp"

class Prodavnica{
private:
    DinString naziv;
    List <Proizvod*> proizvodi;
public:
    Prodavnica(const DinString& nn) : naziv(nn) {};

    bool dodajProizvod(Proizvod& proizvod_novi) {
        Proizvod* pom;    //pomocni clan

        for (int i = 0; i <= proizvodi.size(); i++) {
            proizvodi.read(i, pom);
            if ((*pom).getNaziv() == proizvod_novi.getNaziv()) {
                return false;
            }
            return proizvodi.add(1, &proizvod_novi);
        }
        return false;
    }

    void obrisi_proizvod(const DinString& del) {
        Proizvod* pom;

        for (int i = 0; i <= proizvodi.size(); i++) {
            proizvodi.read(i, pom);
            if((*pom).getNaziv() == del) {
                proizvodi.remove(i);
            }
        }
    }

    void obrisi_proizvod(int i) {
        proizvodi.remove(i);
    }

    void akcija() {
        Proizvod* pom;

        for (int i = 0; i <= proizvodi.size(); i++) {
            proizvodi.read(i, pom);
            (*pom).izracunajPopust();
        }
    }

    friend ostream& operator<<(ostream& os, const Prodavnica& p){
        os << p.naziv << endl << "Proizvodi:" << endl;
        Proizvod* pom;
        for (int i = 1; i <= p.proizvodi.size(); i++){
            p.proizvodi.read(i,pom);
            pom->ispisi();
            os << endl;
        }
        return os;
    }
};

#endif // PRODAVNICA_HPP_INCLUDED
