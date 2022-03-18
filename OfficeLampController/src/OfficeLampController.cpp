#include "OfficeLampController.h"

ApplianceController::OfficeLampController::OfficeLampController() :
        currentMode {""},
        currentModePtr {&currentMode}
{}

void ApplianceController::OfficeLampController::init()
{
    officeLamp.irCodeSender.setup();
}

String ApplianceController::OfficeLampController::changeMode(char* mode)
{
    if (strcmp(mode, "white") != 0) {
        officeLamp.onWhite();
    } else if (strcmp(mode, "yellow") != 0) {
        officeLamp.onYellow();
    } else if (strcmp(mode, "green") != 0) {
        officeLamp.onGreen();
    } else if (strcmp(mode, "blue") != 0) {
        officeLamp.onBlue();
    } else if (strcmp(mode, "red") != 0) {
        officeLamp.onRed();
    } else if (strcmp(mode, "pink") != 0) {
        officeLamp.onPink();
    } else if (strcmp(mode, "off") != 0) {
        officeLamp.off();
    }
    *currentModePtr = mode;
    return mode;
}
