#ifndef VIDEOKAMERA_HPP_INCLUDED
#define VIDEOKAMERA_HPP_INCLUDED

#include "kamera.hpp"

class VideoKamera:public Kamera{

protected:
    static int videoCounter;
public:
    VideoKamera() : Kamera() {}
    VideoKamera(int mp, int prostor) : Kamera(mp,prostor) {}
    VideoKamera(const VideoKamera& vk) : Kamera((Kamera)vk) {}

    int getVideoCounter(){return videoCounter;}
    bool snimaj(int sekunde){
        if(freeSpace - sekunde*megaPikseli > 0){
            freeSpace -= sekunde*megaPikseli;
            videoCounter++;
            return true;
        }else{
        return false;}
    }

};

#endif // VIDEOKAMERA_HPP_INCLUDED
