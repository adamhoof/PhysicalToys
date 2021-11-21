#pragma once

#include "OfficeCeilLight.h"

namespace PhysicalToyController
{
    class OfficeCeilLightController
    {
    public:
        OfficeCeilLightController();

        PhysicalToy::OfficeCeilLight officeLamp{};

        void setTogglePin(uint8_t pin);

        void init() const;

        String changeMode(String& mode);

    };
}
