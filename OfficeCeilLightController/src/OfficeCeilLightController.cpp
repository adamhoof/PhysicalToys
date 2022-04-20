#include "OfficeCeilLightController.h"

PhysicalToyController::OfficeCeilLightController::OfficeCeilLightController() :
        currentMode {""},
        currentModePtr {&currentMode}
{};

void PhysicalToyController::OfficeCeilLightController::setTogglePin(uint8_t pin)
{
    officeLamp.togglePin = pin;
}

void PhysicalToyController::OfficeCeilLightController::init() const
{
    pinMode(officeLamp.togglePin, OUTPUT);
}

void PhysicalToyController::OfficeCeilLightController::changeMode(char* modeToSet)
{
    strcmp(modeToSet, ON) != 0 ? officeLamp.off() : officeLamp.on();
}
