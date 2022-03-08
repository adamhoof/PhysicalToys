#pragma once

#include "IRCodeSender.h"

namespace PhysicalToy
{
    class OfficeLamp
    {
    public:
        OfficeLamp();

        IRCodeSender irCodeSender{};

        void onWhite();

        void onYellow();

        void onBlue();

        void onGreen();

        void onRed();

        void onPink();

        void off();
    };
}