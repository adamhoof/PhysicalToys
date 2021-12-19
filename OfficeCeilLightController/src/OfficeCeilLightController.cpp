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

String PhysicalToyController::OfficeCeilLightController::changeMode(String& mode)
{
    mode == ON ? officeLamp.on() : officeLamp.off();
    *currentModePtr = mode;
    return mode;
}
