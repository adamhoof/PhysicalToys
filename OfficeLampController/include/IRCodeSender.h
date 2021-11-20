#pragma once

#include <Arduino.h>
#include <IRsend.h>

class IRCodeSender
{
private:
    const uint32_t onSignal = 0x00F7C03F;
    const uint32_t whiteSignal = 0x00F7E01F;
    const uint32_t yellowSignal = 0x00F728D7;
    const uint32_t blueSignal = 0x00F7609F;
    const uint32_t greenSignal = 0x00F7A05F;
    const uint32_t redSignal = 0x00F720DF;
    const uint32_t pinkSignal = 0x00F76897;
    const uint32_t offSignal = 0x00F740BF;

    void send(uint32_t rawDataToSend);

public:
    IRCodeSender();

    IRsend irSend {25};

    void setup();

    void onWhite();

    void onYellow();

    void onBlue();

    void onGreen();

    void onRed();

    void onPink();

    void off();
};
