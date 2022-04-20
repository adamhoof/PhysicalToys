#include "LampController.h"

ApplianceController::LampController::LampController(uint8_t controlPin, uint8_t numOfLeds) :
        controlPin(controlPin),
        numberOfLeds(numOfLeds)
{}

void ApplianceController::LampController::setBrightness(uint8_t brightness)
{
    pixelMatrix.setBrightness(brightness);
}

void ApplianceController::LampController::init()
{
    pixelMatrix.begin();
}

void ApplianceController::LampController::changeMode(const char* modeToSet)
{
    for (int i = 0; i < pixelMatrix.numPixels(); ++i) {
        pixelMatrix.setPixelColor(i, availableModes[modeToSet]);
    }
    pixelMatrix.show();
}
