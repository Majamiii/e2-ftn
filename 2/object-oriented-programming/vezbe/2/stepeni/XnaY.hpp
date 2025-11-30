#ifndef XNAY_HPP_INCLUDED
#define XNAY_HPP_INCLUDED

#include <cmath>
#include <iostream>


class XnaY{
private:
    int x;
    int y;
public:
    XnaY();
    XnaY(int a, int b);
    XnaY(const XnaY& ab);

    void setX(int a);
    void setY(int b);
    void setX_Y(int a, int b);

    int getX() const;
    int getY() const;
    double getXnaY() const;
};


#endif // XNAY_HPP_INCLUDED
