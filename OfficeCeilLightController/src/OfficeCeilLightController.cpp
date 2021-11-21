#include "OfficeCeilLightController.h"

PhysicalToyController::OfficeCeilLightController::OfficeCeilLightController() = default;

void PhysicalToyController::OfficeCeilLightController::setup()
{
    pinMode(TOGGLE_PIN, OUTPUT);
}

String PhysicalToyController::OfficeCeilLightController::changeMode(String& mode)
{
    mode == ON ? digitalWrite(TOGGLE_PIN, LOW): digitalWrite(TOGGLE_PIN, HIGH);
    return mode;
}
