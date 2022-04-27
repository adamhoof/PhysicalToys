#include "ShadesController.h"

ToyController::ShadesController::ShadesController() :
        currentMode {"2"},
        requiredMode {"2"}
{}

void ToyController::ShadesController::setMotorController(StepperMotorController& motorController)
{
    this->motorController = motorController;
}

void ToyController::ShadesController::changeMode(char* modeToSet)
{
    if (strcmp(currentMode, modeToSet) == 0) {
        return;
    }
    strcpy(requiredMode, modeToSet);
    strcmp(modeToSet, "1") != 0 ? close() : open();
}

void ToyController::ShadesController::open()
{
    while (OPEN_SWITCH_NOT_PRESSED) {
        if (strcmp(requiredMode, "1") != 0) {
            return;
        }
        motorController.moveAntiClockwise();
    }
    motorController.moveByStepAmount(CLOCKWISE, 100); // move away from switch
    strcpy(currentMode, "1");
}

void ToyController::ShadesController::close()
{
    while (CLOSE_SWITCH_NOT_PRESSED) {
        if (strcmp(requiredMode, "0") != 0) {
            return;
        }
        motorController.moveClockwise();
    }
    motorController.moveByStepAmount(ANTI_CLOCKWISE, 100); // move away from switch
    strcpy(currentMode, "0");
}
