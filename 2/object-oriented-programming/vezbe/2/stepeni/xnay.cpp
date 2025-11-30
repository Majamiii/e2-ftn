#include "XnaY.hpp"

XnaY::XnaY(){
    x = 1;
    y=1;
};
XnaY::XnaY(int a, int b){
    x = a;
    y = b;
};
XnaY::XnaY(const XnaY& ab){
    x = ab.getX();
    y = ab.getY();
};

void XnaY::setX(int a){
    x = a;
}
void XnaY::setY(int b){
    y = b;
}
void XnaY::setX_Y(int a, int b){
    x = a;
    y = b;
}

int XnaY::getX() const{
    return x;
};
int XnaY::getY() const{
    return y;
};
double XnaY::getXnaY() const{
    return pow(x,y);
};
