#pragma once

#include "StepperMotor.h"

#define CLOCKWISE -1
#define ANTI_CLOCKWISE 1
#define POS_EQUAL stepperMotorController.getRequiredPos() == stepperMotorController.getPos()
#define POS_NOT_EQUAL stepperMotorController.getRequiredPos() != stepperMotorController.getPos()

namespace PhysicalToyController
{
    class StepperMotorController
    {
    public:
        uint8_t pos;
        uint8_t requiredPos;
    public:
        StepperMotorController();

        StepperMotor stepperMotor {};

        uint8_t getPos();

        uint8_t getRequiredPos();

        void posToMoveTo(String& receivedPos);

        void open();

        void close();
    };
}
