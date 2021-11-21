#pragma once

#include "OfficeLamp.h"

namespace ApplianceController
{
    class OfficeLampController
    {
    public:

        OfficeLampController();

        PhysicalToy::OfficeLamp officeLamp {};

        void init();

        String changeMode(String& mode);
    };
}
