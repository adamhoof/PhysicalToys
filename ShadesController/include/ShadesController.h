#pragma once

#include "WifiController.h"
#include "MQTTClientHandler.h"
#include "StepperMotorController.h"

#define OPEN 1
#define CLOSE 0

namespace PhysicalToyController
{
    class ShadesController
    {
    public:
        ShadesController();

        void open(StepperMotorController& motorController);

        void close(StepperMotorController& motorController);
    };
}
