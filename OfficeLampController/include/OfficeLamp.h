#pragma once

#include "IRCodeSender.h"

namespace PhysicalToy
{
    class OfficeLamp
    {
    public:
        OfficeLamp();

        IRCodeSender irCodeSender{};

        void on();

        void mode(uint32_t mode);

        void off();
    };
}