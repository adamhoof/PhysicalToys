#include "LampController.h"

ApplianceController::LampController::LampController() :
        currentMode {""},
        currentModePtr {&currentMode},
        ledPin(32),
        numberOfLeds(8)
{}

void ApplianceController::LampController::setBrightness(uint8_t brightness)
{
    pixelMatrix.setBrightness(brightness);
}

void ApplianceController::LampController::init()
{
    pixelMatrix.begin();
}

void ApplianceController::LampController::yellow()
{
    lightUpAll(yellowC);
}

void ApplianceController::LampController::orange()
{
    lightUpAll(orangeC);
}

void ApplianceController::LampController::green()
{
    lightUpAll(greenC);
}

void ApplianceController::LampController::blue()
{
    lightUpAll(blueC);
}

void ApplianceController::LampController::red()
{
    lightUpAll(redC);
}

void ApplianceController::LampController::pink()
{
    lightUpAll(pinkC);
}

void ApplianceController::LampController::off()
{
    lightUpAll(offC);
}

void ApplianceController::LampController::lightUpAll(uint32_t color)
{
    for (int i = 0; i < pixelMatrix.numPixels(); ++i) {
        pixelMatrix.setPixelColor(i, color);
    }
    pixelMatrix.show();
}

String ApplianceController::LampController::changeMode(String& mode)
{
    if (mode == "yellow") {
        yellow();
    } else if (mode == "orange") {
        orange();
    } else if (mode == "green") {
        green();
    } else if (mode == "blue") {
        blue();
    } else if (mode == "red") {
        red();
    } else if (mode == "pink") {
        pink();
    } else if (mode == "off") {
        off();
    }
    *currentModePtr = mode;
    return mode;
}

String* ApplianceController::LampController::getCurrentModePtr() const
{
    return currentModePtr;
}
