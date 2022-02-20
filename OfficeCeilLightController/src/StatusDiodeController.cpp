#include "StatusDiodeController.h"

StatusDiodeController::StatusDiodeController() :
        ledPin(27),
        numberOfLeds(1),
        currentMode{""}
{}

void StatusDiodeController::setBrightness(uint8_t brightness)
{
    pixelMatrix.setBrightness(brightness);
}

void StatusDiodeController::init()
{
    pixelMatrix.begin();
}

void StatusDiodeController::yellow()
{
    if (currentMode == "yellow"){
        return;
    }
    lightUpAll(yellowC);
    currentMode = "yellow";
}

void StatusDiodeController::green()
{
    if (currentMode == "green"){
        return;
    }
    lightUpAll(greenC);
    currentMode = "green";
}

void StatusDiodeController::red()
{
    if (currentMode == "red"){
        return;
    }
    lightUpAll(redC);
    currentMode = "red";
}

void StatusDiodeController::lightUpAll(uint32_t color)
{
    for (int i = 0; i < pixelMatrix.numPixels(); ++i) {
        pixelMatrix.setPixelColor(i, color);
    }
    pixelMatrix.show();
}
