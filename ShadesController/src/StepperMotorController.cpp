#include "StepperMotorController.h"

StepperMotorController::StepperMotorController() = default;

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

void StepperMotorController::setDelayBetweenSteps(uint8_t stepDelay)
{
    if (stepperMotor.delayBetweenSteps == stepDelay) {
        return;
    }
    stepperMotor.delayBetweenSteps = stepDelay;
}


void StepperMotorController::moveClockwise()
{
    stepperMotor.clockwiseStep();
}

void StepperMotorController::moveAntiClockwise()
{
    stepperMotor.antiClockwiseStep();
}

void StepperMotorController::moveByStepAmount(uint8_t dir, uint32_t amountOfSteps)
{
    switch (dir) {
        case CLOCKWISE:
            for (int i = 0; i < amountOfSteps; ++i) {
                stepperMotor.clockwiseStep();
            }
            break;
        case ANTI_CLOCKWISE:
            for (int i = 0; i < amountOfSteps; ++i) {
                stepperMotor.antiClockwiseStep();
            }
            break;
        default:
            break;
    }
}
