#pragma once

#include <Arduino.h>

#define ON "O"
#define OFF "o"

namespace PhysicalToy
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
