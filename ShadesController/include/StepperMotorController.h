#pragma once

#include "StepperMotor.h"

#define POS_EQUAL stepperMotorController.getRequiredPos() == stepperMotorController.getPos()

class StepperMotorController
{
public:
    uint8_t pos;
    uint8_t requiredPos;
public:
    StepperMotorController();

    StepperMotor stepperMotor {};

    void setupPins(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4);

    void calibrate();

    uint8_t getPos();

    uint8_t getRequiredPos();

    void posToMoveTo(String& receivedPos);

    void open();

    void close();
};
