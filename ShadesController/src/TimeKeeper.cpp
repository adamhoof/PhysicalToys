#include "TimeKeeper.h"

TimeKeeper::TimeKeeper() = default;

bool TimeKeeper::unitsOfTimePassed(uint16_t amount, uint32_t unitsMultiplier)
{
    return millis() >= amount * unitsMultiplier;
}
