#include "OfficeLampController.h"

OfficeLampController::OfficeLampController() = default;

void OfficeLampController::changeMode(IRsend* irCodeSender, char* modeToSet)
{
    if (strcmp(modeToSet, "off") == 0) {
        irCodeSender->sendNEC(modes["off"]);
        return;
    }
    irCodeSender->sendNEC(modes["on"]);
    irCodeSender->sendNEC(modes[modeToSet]);
}
