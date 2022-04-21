#pragma once

#include "WifiController.h"
#include "MQTTClientHandler.h"
#include "StepperMotorController.h"

#define OPEN 1
#define CLOSE 0

namespace ToyController
{
    class ShadesController
    {
    public:
        ShadesController();

        StepperMotorController motorController;

        void setMotorController(StepperMotorController& motorController);

        void changeMode(char* modeToSet);

        void open();

        void close();
    };
}
