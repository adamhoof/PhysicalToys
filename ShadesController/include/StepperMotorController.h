#pragma once

#include "StepperMotor.h"

#define CLOCKWISE 1
#define ANTI_CLOCKWISE 0

class StepperMotorController
{
public:
    StepperMotorController();

    StepperMotor stepperMotor {};

    void setupPins(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4);

    void setDelayBetweenSteps(uint8_t stepDelay);

    void moveByStepAmount(uint8_t dir, uint32_t amountOfSteps);

    void moveClockwise();

    void moveAntiClockwise();
};
