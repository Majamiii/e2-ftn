#ifndef JSTROUGAO_HPP_INCLUDED
#define JSTROUGAO_HPP_INCLUDED

#include "JKTrougao.hpp"

class JSTrougao : public JKTrougao {                    //public nasledjivanje ne menja nista
    public:                                             //dodajemo nove metode
        JSTrougao() : JKTrougao(1, 1) {}                //konstruktori se ne nasledjuju pa se ponovu pisu
        JSTrougao(double aa) : JKTrougao(aa, aa) {}     //kontruktor kopije samo sva puta salje na sve ostale stranice (ima ih dve jednake vec jer je JDt nasledik JKt)
        JSTrougao(const JSTrougao &jst) : JKTrougao(jst.a, jst.b) {} //kontruktor kopije koji dodaje samo na jedno mesto  
};      //posto se nasledjuje JKt imamo samo dve duzine stranica te ako konstruiseo jst preko jkt onda imamo obavezno samo jednu vrednost

        //preporuka za nasledjivanje da se nasledjuje najmanja sira klasa

#endif // JSTROUGAO_HPP_INCLUDED
