#include "OfficeLampController.h"

ApplianceController::OfficeLampController::OfficeLampController() :
        currentMode {nullptr}
{}

void ApplianceController::OfficeLampController::init()
{
    officeLamp.irCodeSender.setup();
}

void ApplianceController::OfficeLampController::changeMode(char* modeToSet)
{
    strcmp(modeToSet, "off") != 0 ? officeLamp.mode(availableModes[modeToSet]) : officeLamp.off();
}
