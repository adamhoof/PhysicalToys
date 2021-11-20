#pragma once

#include "IRCodeSender.h"

namespace ApplianceController
{
    class OfficeLampController
    {
    public:

        OfficeLampController();

        IRCodeSender irCodeSender {};

        void setup();

        String changeMode(String& mode);
    };
}
