#include "OfficeCeilLightController.h"

PhysicalToyController::OfficeCeilLightController::OfficeCeilLightController() = default;

void PhysicalToyController::OfficeCeilLightController::setup()
{
    pinMode(TOGGLE_PIN, OUTPUT);
}

String PhysicalToyController::OfficeCeilLightController::changeMode(String& mode)
{
    if (mode == ON){
        digitalWrite(TOGGLE_PIN, LOW);
    } else if (mode == OFF) {
        digitalWrite(TOGGLE_PIN, HIGH);
    }
    return mode;
}
