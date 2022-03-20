#pragma once

#include <Arduino.h>
#include <IRsend.h>

class IRCodeSender
{
public:
    IRCodeSender();

    IRsend irSend {25};

    void setup();

    void send(uint32_t rawDataToSend);
};
