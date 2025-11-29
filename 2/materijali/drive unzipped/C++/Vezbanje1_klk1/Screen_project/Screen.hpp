#ifndef SCREEN_HPP_INCLUDED
#define SCREEN_HPP_INCLUDED


enum ScreenStates {
    ssON,
    ssOFF
};

class Screen {
private:
    ScreenStates state;
    int brightness;

public:
    Screen() {
        state = ssOFF;
        brightness = 0;
    }
    bool incB() {
        if (brightness != 20 && state == ssON) {
            brightness =+ 2;
            return true;
        }
        return false;
    }
    bool decB() {
        if (brightness != 0 && state == ssON) {
            brightness -= 2;
            return true;
        }
        return false;
    }
    void setState(ScreenStates st) {
            state = st;
            brightness = 0;
    }
    int getBrightness() const {
        return brightness;
    }
    ScreenStates getState() const {
        return state;
    }
};


#endif // SCREEN_HPP_INCLUDED
