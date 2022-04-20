#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <map>

namespace ApplianceController
{
    class LampController
    {
    private:
        uint8_t controlPin {};
        uint8_t numberOfLeds {};

    private:
        Adafruit_NeoPixel arrayOfLedPixels = Adafruit_NeoPixel(numberOfLeds, controlPin, NEO_RBG + NEO_KHZ800);

        std::map<const std::string, const uint32_t> availableModes = {
                {"yellow", Adafruit_NeoPixel::Color(127, 0, 255) },
                {"orange", Adafruit_NeoPixel::Color(70, 0, 255) },
                {"green", Adafruit_NeoPixel::Color(255, 0, 0) },
                {"blue", Adafruit_NeoPixel::Color(0, 255, 0) },
                {"red", Adafruit_NeoPixel::Color(0, 0, 255) },
                {"pink", Adafruit_NeoPixel::Color(0, 255, 255) },
                {"off", Adafruit_NeoPixel::Color(0, 0, 0) },
        };

    public:
        LampController(uint8_t controlPin, uint8_t numOfLeds);

        void init();

        void setBrightness(uint8_t brightness);

        void changeMode(const char* modeToSet);
    };
}
