#pragma once

#include "StepperMotorController.h"
#include "MQTTClientHandler.h"

namespace PhysicalToyController
{
    class ShadesController
    {
    public:
        ShadesController();

        void open(MQTTClientHandler &mqttClientHandler, StepperMotorController &motorController);

        void close(MQTTClientHandler &mqttClientHandler, StepperMotorController &motorController);
    };
}
