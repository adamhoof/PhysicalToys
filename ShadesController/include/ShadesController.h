#pragma once

#include "StepperMotorController.h"
#include "OpenCloseSwitchesTracker.h"

#define OPEN_SWITCH 33
#define CLOSE_SWITCH 32

#define OPEN_SWITCH_NOT_PRESSED digitalRead(OPEN_SWITCH)
#define CLOSE_SWITCH_NOT_PRESSED digitalRead(CLOSE_SWITCH)

namespace ToyController
{
    class ShadesController
    {
    public:
        ShadesController();

        StepperMotorController motorController{};

        char currentMode[10];
        char requiredMode[10];

        void setMotorController(StepperMotorController& motorController);

        void changeMode(char* modeToSet);

        void open();

        void close();
    };
}
