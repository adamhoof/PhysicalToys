#include "ShadesController.h"

PhysicalToyController::ShadesController::ShadesController() = default;

void PhysicalToyController::ShadesController::open(StepperMotorController& motorController)
{

    for (uint16_t i = 0; i < 200; ++i) {
        motorController.setDelayBetweenSteps(3);
        motorController.stepperMotor.antiClockwiseStep();
    }
    for (uint16_t i = 0; i < 9000; ++i) {
        motorController.setDelayBetweenSteps(2);
        motorController.stepperMotor.antiClockwiseStep();
    }

    motorController.setCurrPos(OPEN);
}

void PhysicalToyController::ShadesController::close(StepperMotorController& motorController)
{
    for (int i = 0; i < 20; ++i) {
        motorController.setDelayBetweenSteps(3);
        motorController.stepperMotor.clockwiseStep();
    }
    while (digitalRead(32)) {
        motorController.setDelayBetweenSteps(2);
        motorController.stepperMotor.clockwiseStep();
    }
    motorController.setDelayBetweenSteps(3);
    motorController.leaveSwitchAlone();

    motorController.setCurrPos(CLOSE);
}
