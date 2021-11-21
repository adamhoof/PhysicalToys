#include "OfficeLampController.h"

ApplianceController::OfficeLampController::OfficeLampController() = default;

void ApplianceController::OfficeLampController::init()
{
    officeLamp.irCodeSender.setup();
}

String ApplianceController::OfficeLampController::changeMode(String& mode)
{
    if (mode == "w") {
        officeLamp.onWhite();
    } else if (mode == "y") {
        officeLamp.onYellow();
    } else if (mode == "g") {
        officeLamp.onGreen();
    } else if (mode == "b") {
        officeLamp.onBlue();
    } else if (mode == "r") {
        officeLamp.onRed();
    } else if (mode == "p") {
        officeLamp.onPink();
    } else if (mode == "o") {
        officeLamp.off();
    }
    return mode;
}
