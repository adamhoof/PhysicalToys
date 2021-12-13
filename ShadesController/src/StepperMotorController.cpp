#include "StepperMotorController.h"

StepperMotorController::StepperMotorController()
        : pos(0), requiredPos(0)
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

void StepperMotorController::calibrate()
{
    while (digitalRead(32)) {
        stepperMotor.clockwiseStep();
    }
    uint8_t i;

    for (i = 0; i < 100; ++i) {
        stepperMotor.antiClockwiseStep();
    }
    for (i = 0; i < 100; ++i) {
        stepperMotor.clockwiseStep();
    }
    for (i = 0; i < 100; ++i) {
        stepperMotor.antiClockwiseStep();
    }
    pos = 0;
}

void StepperMotorController::posToMoveTo(String& receivedPos)
{
    requiredPos = receivedPos.toInt();
}

uint8_t StepperMotorController::getPos()
{
    return pos;
}

uint8_t StepperMotorController::getRequiredPos()
{
    return requiredPos;
}

void StepperMotorController::open()
{
    for (uint32_t i = 0; i < 11000; ++i) {
        stepperMotor.antiClockwiseStep();
    }
    pos = 1;
}

void StepperMotorController::close()
{
    calibrate();
}
