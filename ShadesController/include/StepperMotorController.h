#pragma once

#include "StepperMotor.h"

#define POSITIONS_EQUAL stepperMotorController.getReqPos() == stepperMotorController.getCurrPos()
#define REQ_POS_GREATER stepperMotorController.getReqPos() > stepperMotorController.getCurrPos()

class StepperMotorController
{
public:
    uint8_t currPos;
    uint8_t reqPos;
public:
    StepperMotorController();

    StepperMotor stepperMotor {};

    void setupPins(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4);

    uint8_t getCurrPos();

    void setCurrPos(uint8_t pos);

    uint8_t getReqPos();

    void setReqPosFromString(String& receivedPos);
};
