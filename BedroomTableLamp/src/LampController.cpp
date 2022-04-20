#include "LampController.h"

ApplianceController::LampController::LampController(uint8_t controlPin, uint8_t numOfLeds) :
        controlPin(controlPin),
        numberOfLeds(numOfLeds)
{}

void ApplianceController::LampController::init()
{
    arrayOfLedPixels.begin();
}

void ApplianceController::LampController::setBrightness(uint8_t brightness)
{
    arrayOfLedPixels.setBrightness(brightness);
}

void ApplianceController::LampController::changeMode(const char* modeToSet)
{
    for (int i = 0; i < arrayOfLedPixels.numPixels(); ++i) {
        arrayOfLedPixels.setPixelColor(i, availableModes[modeToSet]);
    }
    arrayOfLedPixels.show();
}
