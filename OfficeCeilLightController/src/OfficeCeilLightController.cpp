#include "OfficeCeilLightController.h"

ToyController::OfficeCeilLightController::OfficeCeilLightController() :
        currentMode {""},
        currentModePtr {&currentMode}
{};

void ToyController::OfficeCeilLightController::setTogglePin(uint8_t pin)
{
    officeLamp.togglePin = pin;
}

void ToyController::OfficeCeilLightController::init() const
{
    pinMode(officeLamp.togglePin, OUTPUT);
}

void ToyController::OfficeCeilLightController::changeMode(char* modeToSet)
{
    strcmp(modeToSet, ON) != 0 ? officeLamp.off() : officeLamp.on();
}
