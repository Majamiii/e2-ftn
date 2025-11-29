#ifndef JSTROUGAO_HPP_INCLUDED
#define JSTROUGAO_HPP_INCLUDED
#include "JKtrougao.hpp"

class JStrougao : public JKtrougao{
public:
    JStrougao() :JKtrougao(3, 3){}
    JStrougao(double aa) : JKtrougao(aa, aa) {}
    JStrougao(const JStrougao& jst) : JKtrougao(jst){}

};


#endif // JSTROUGAO_HPP_INCLUDED
