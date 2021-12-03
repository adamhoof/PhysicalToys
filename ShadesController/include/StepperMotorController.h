#pragma once

#include "StepperMotor.h"

#define CLOCKWISE -1
#define ANTI_CLOCKWISE 1

namespace PhysicalToyController
{
    class StepperMotorController
    {
    public:
        int32_t stepCount;
    public:
        StepperMotorController();

        StepperMotor stepperMotor {};

        void moveMotor(int direction);
    };
}
