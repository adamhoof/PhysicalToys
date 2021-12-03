#include "StepperMotorController.h"

PhysicalToyController::StepperMotorController::StepperMotorController()
        :stepCount(0)
{}

void PhysicalToyController::StepperMotorController::moveMotor(int direction)
{
    direction == CLOCKWISE ? stepperMotor.clockwiseStep()
                           : stepperMotor.antiClockwiseStep();
    stepCount += direction;
}
