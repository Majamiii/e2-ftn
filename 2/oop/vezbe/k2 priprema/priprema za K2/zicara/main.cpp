#include "zicara.hpp"

using namespace std;

int main()
{

    Karta letnja(111,LETO);
    cout<<letnja<<endl;
    cout<<"geter za broj: "<<letnja.getBrKarte()<<endl;
    cout<<"geter za vrstu: "<<letnja.getVrsta()<<endl; // TODO: switch

    Putnik putnik(333,SKI_OPENING,"1407005","Majami");
    cout<<putnik;
    cout<<putnik.getMb()<<endl<<putnik.getVrsta()<<endl;

    PutnikDete dete(putnik,"7385924");
    cout<<dete.toString()<<endl;

    cout<<"... zicara ..."<<endl;
    Zicara<SKI,30,120> z;

    cout<<z.dodajPutnika(&putnik)<<endl;

    cout<<"prevozimo praznu turu: "<<z.preveziTuru()<<endl;

    Putnik putnik_ski(333,SKI,"1407005","Majami");
    cout<<z.dodajPutnika(&putnik_ski);

    cout<<endl<<z.brojPutnika()<<endl;

    z.otvori();
    cout<<z<<endl;

    z.preveziTuru();
    cout<<z<<endl;


    return 0;
}
