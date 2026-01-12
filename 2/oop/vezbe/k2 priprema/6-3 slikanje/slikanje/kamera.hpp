#ifndef KAMERA_HPP_INCLUDED
#define KAMERA_HPP_INCLUDED

#include <iostream>

class Kamera{
protected:
    int megaPikseli, freeSpace;
    static int photoCounter;
public:
    Kamera() : megaPikseli(0),freeSpace(0) {}
    Kamera(int pikseli, int prostor) : megaPikseli(pikseli), freeSpace(prostor){}
    Kamera(const Kamera& cam) : megaPikseli(cam.megaPikseli),freeSpace(cam.freeSpace) {}

    int getPhotoCount(){
        return photoCounter;
    }

    bool slikaj(){
        if(freeSpace-megaPikseli>0){
            freeSpace-=megaPikseli;
            photoCounter++;
            return true;
        }
        else{
            return false;
        }
    }

};

#endif // KAMERA_HPP_INCLUDED
