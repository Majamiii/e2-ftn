#ifndef PRAVILANOBLIK_HPP_INCLUDED
#define PRAVILANOBLIK_HPP_INCLUDED

#include "oblik.hpp"

class PravilanOblik : public Oblik {
public:
    PravilanOblik() : Oblik(1,1) {}
    PravilanOblik(double a) : Oblik(a,a) {}
    PravilanOblik(const PravilanOblik& po) : Oblik(po) {}
};

#endif // PRAVILANOBLIK_HPP_INCLUDED
