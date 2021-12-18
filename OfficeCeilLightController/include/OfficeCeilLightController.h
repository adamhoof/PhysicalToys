#pragma once

#include "OfficeCeilLight.h"

namespace PhysicalToyController
{
    class OfficeCeilLightController
    {
    public:
        OfficeCeilLightController();

        Toy::OfficeCeilLight officeLamp{};

        void setTogglePin(uint8_t pin);

        void init() const;

        String changeMode(String& mode);

    };
}
