#include "OfficeLampController.h"

ApplianceController::OfficeLampController::OfficeLampController() :
        currentMode {""},
        currentModePtr {&currentMode}
{}

void ApplianceController::OfficeLampController::init()
{
    officeLamp.irCodeSender.setup();
}

String ApplianceController::OfficeLampController::changeMode(String& mode)
{
    if (mode == "white") {
        officeLamp.onWhite();
    } else if (mode == "yellow") {
        officeLamp.onYellow();
    } else if (mode == "green") {
        officeLamp.onGreen();
    } else if (mode == "blue") {
        officeLamp.onBlue();
    } else if (mode == "red") {
        officeLamp.onRed();
    } else if (mode == "pink") {
        officeLamp.onPink();
    } else if (mode == "off") {
        officeLamp.off();
    }
    *currentModePtr = mode;
    return mode;
}
