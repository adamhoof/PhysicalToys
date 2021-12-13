#include "StepperMotorController.h"

PhysicalToyController::StepperMotorController::StepperMotorController()
        : pos(0), requiredPos(0)
{}

void PhysicalToyController::StepperMotorController::posToMoveTo(String& receivedPos)
{
        requiredPos = receivedPos.toInt();
}

uint8_t PhysicalToyController::StepperMotorController::getPos()
{
    return pos;
}

uint8_t PhysicalToyController::StepperMotorController::getRequiredPos()
{
    return requiredPos;
}

void PhysicalToyController::StepperMotorController::open()
{
    for (int i = 0; i < 500; ++i) {
        stepperMotor.clockwiseStep();
    }
    pos = 1;
}

void PhysicalToyController::StepperMotorController::close()
{
    while (digitalRead(32)) {
        stepperMotor.antiClockwiseStep();
    }
    for (int i = 0; i < 100; ++i) {
        stepperMotor.clockwiseStep();
    }
    pos = 0;
}
