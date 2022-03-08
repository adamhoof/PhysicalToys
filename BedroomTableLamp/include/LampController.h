#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

namespace ApplianceController
{
    class LampController
    {
    private:
        String currentMode;
        String* currentModePtr;

        uint8_t ledPin {};
        uint8_t numberOfLeds {};

        Adafruit_NeoPixel pixelMatrix = Adafruit_NeoPixel(numberOfLeds, ledPin, NEO_RBG + NEO_KHZ800);

        const uint32_t yellowC {Adafruit_NeoPixel::Color(127, 0, 255)};
        const uint32_t orangeC {Adafruit_NeoPixel::Color(70, 0, 255)};
        const uint32_t greenC {Adafruit_NeoPixel::Color(255, 0, 0)};
        const uint32_t blueC {Adafruit_NeoPixel::Color(0, 255, 0)};
        const uint32_t redC {Adafruit_NeoPixel::Color(0, 0, 255)};
        const uint32_t pinkC {Adafruit_NeoPixel::Color(0, 255, 255)};
        const uint32_t offC {Adafruit_NeoPixel::Color(0, 0, 0)};

    public:
        LampController();

        void setBrightness(uint8_t brightness);

        void init();

        void yellow();

        void orange();

        void green();

        void blue();

        void red();

        void pink();

        void off();

        void lightUpAll(uint32_t color);

        String changeMode(String& mode);

        String* getCurrentModePtr() const;
    };
}
