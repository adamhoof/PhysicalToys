#pragma once

#include "OfficeLamp.h"

namespace ApplianceController
{
    class OfficeLampController
    {
    public:
        String currentMode;
        String* currentModePtr;

        OfficeLampController();

        PhysicalToy::OfficeLamp officeLamp {};

        void init();

        String changeMode(char* mode);
    };
}
