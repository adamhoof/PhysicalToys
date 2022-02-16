#pragma once

#include <Arduino.h>

#define MINUTES 60000
#define HOURS 3600000

class TimeKeeper
{
public:
    TimeKeeper();

    bool unitsOfTimePassed(uint16_t amount, uint32_t unitsMultiplier);
};
