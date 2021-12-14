#pragma once

#include "StepperMotorController.h"
#include "MQTTClientHandler.h"

#define OPEN 1
#define CLOSE 0

namespace PhysicalToyController
{
    class ShadesController
    {
    public:
        ShadesController();

        static void open(MQTTClientHandler& mqttClientHandler, StepperMotorController& motorController);

        static void close(MQTTClientHandler& mqttClientHandler, StepperMotorController& motorController);
    };
}
