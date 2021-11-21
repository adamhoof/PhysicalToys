#pragma once

#include "OfficeLamp.h"

namespace PhysicalToyController
{
    class OfficeCeilLightController
    {
    public:
        OfficeCeilLightController();

        Toy::OfficeLamp officeLamp{};

        void setTogglePin(uint8_t pin);

        void init() const;

        String changeMode(String& mode);

    };
}
