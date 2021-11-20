#include "OfficeLampController.h"

ApplianceController::OfficeLampController::OfficeLampController() = default;

void ApplianceController::OfficeLampController::setup()
{
    irCodeSender.setup();
}

String ApplianceController::OfficeLampController::changeMode(String& mode)
{

    if (mode == "w") {
        irCodeSender.onWhite();
    } else if (mode == "y") {
        irCodeSender.onYellow();
    } else if (mode == "g") {
        irCodeSender.onGreen();
    } else if (mode == "b") {
        irCodeSender.onBlue();
    } else if (mode == "r") {
        irCodeSender.onRed();
    } else if (mode == "p") {
        irCodeSender.onPink();
    } else if (mode == "o") {
        irCodeSender.off();
    }
    return mode;
}
