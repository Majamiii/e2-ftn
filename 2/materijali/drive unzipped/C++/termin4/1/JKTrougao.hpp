#ifndef JKTROUGAO_HPP_INCLUDED
#define JKTROUGAO_HPP_INCLUDED

#include "Trougao.hpp"

class JKTrougao : public Trougao {    //public nasledjivanje ne menja nista
    public:              //dodajemo samo dodatne metode/polja
        JKTrougao() : Trougao(1, 2, 2) {}  //drugacije pozivamo novi (prazan) konstruktor bez parametara sa vrednostima koje se prosledjuju
        JKTrougao(double aa, double bb) : Trougao(aa, bb, bb) {} //konstruktor sa parametrima, samo dva jer je j-kraki
        JKTrougao(const JKTrougao &jkt) : Trougao(jkt) {}  //konstruktor kopije - uzima kopiju jkt i te vrednosti prosledjuje za novi trougao.
};                      //const & za aslanje po referenci sa samo read-only pristupom
        //nismo dodali getere, setere i ostalo smo nasledili pa nema potrebe da se pisu opet
        //metode mogu biti i izmenjene - redefinisane metode +

        //kopira se dekleracija metode, pa se samo izmeni telo - radi drugacije ali se poziva isto
        // naslednik.getObim (npr)

        //seter za c ne sme da menja iskljucivo B ili C vec da menja obe

        void setC(double cc) { 
            c = cc;
            b = cc;
        }

        void setB(double bb) {
            b = bb;
            c = cc;
        }





#endif // JKTROUGAO_HPP_INCLUDED
