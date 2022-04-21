#include "ShadesController.h"

ToyController::ShadesController::ShadesController() = default;

void ToyController::ShadesController::setMotorController(StepperMotorController& motorController)
{
    this -> motorController = motorController;
}

void ToyController::ShadesController::changeMode(char* modeToSet)
{
    strcmp(modeToSet, "1") != 0? close() : open();
}

void ToyController::ShadesController::open()
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

void ToyController::ShadesController::close()
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
