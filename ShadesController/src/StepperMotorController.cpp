#include "StepperMotorController.h"

StepperMotorController::StepperMotorController()
        : currPos(0), reqPos(0)
{}

void StepperMotorController::setupPins(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4)
{
    stepperMotor.pin1 = in1;
    stepperMotor.pin2 = in2;
    stepperMotor.pin3 = in3;
    stepperMotor.pin4 = in4;

    pinMode(stepperMotor.pin1, OUTPUT);
    pinMode(stepperMotor.pin2, OUTPUT);
    pinMode(stepperMotor.pin3, OUTPUT);
    pinMode(stepperMotor.pin4, OUTPUT);
}

void StepperMotorController::setReqPosFromString(String& receivedPos)
{
    reqPos = receivedPos.toInt();
}

void StepperMotorController::setCurrPosFromString(String& receivedPos)
{
    currPos = receivedPos.toInt();
}

uint8_t StepperMotorController::getCurrPos()
{
    return currPos;
}

void StepperMotorController::setCurrPos(uint8_t pos)
{
    currPos = pos;
}

void StepperMotorController::setReqPos(uint8_t pos) {
    reqPos = pos;
}

uint8_t StepperMotorController::getReqPos()
{
    return reqPos;
}

void StepperMotorController::leaveSwitchAlone()
{
    for (int i = 0; i < 100; ++i) {
        stepperMotor.antiClockwiseStep();
    }
}

void StepperMotorController::setDelayBetweenSteps(uint8_t stepDelay)
{
    stepperMotor.delayBetweenSteps = stepDelay;
}
