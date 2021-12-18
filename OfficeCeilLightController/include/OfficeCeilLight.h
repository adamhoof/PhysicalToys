#pragma once

#include <Arduino.h>

#define ON "on"
#define OFF "off"

namespace Toy
{
    class OfficeCeilLight
    {

    public:
        OfficeCeilLight();

        uint8_t togglePin{};

        void on();

        void off();
    };
}
