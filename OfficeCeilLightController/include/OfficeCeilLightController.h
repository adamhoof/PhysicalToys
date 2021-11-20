#pragma once

#include <Arduino.h>

#define ON "O"
#define OFF "o"
#define TOGGLE_PIN 18

namespace PhysicalToyController
{
    class OfficeCeilLightController
    {
    public:
        OfficeCeilLightController();

        void setup();

        String changeMode(String& mode);

    };
}
