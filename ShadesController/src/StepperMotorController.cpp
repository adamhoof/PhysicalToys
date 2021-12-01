#include "StepperMotorController.h"

StepperMotorController::StepperMotorController()
        :stepCount(0)
{}

void StepperMotorController::moveMotor(int direction)
{
    direction == CLOCKWISE ? stepperMotor.clockwiseStep()
                           : stepperMotor.antiClockwiseStep();
    stepCount += direction;
}
