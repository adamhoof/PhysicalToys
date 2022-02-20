#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

    class StatusDiodeController
    {
    private:
        uint8_t ledPin {};
        uint8_t numberOfLeds {};

        Adafruit_NeoPixel pixelMatrix = Adafruit_NeoPixel(numberOfLeds, ledPin, NEO_RBG + NEO_KHZ800);

        const uint32_t yellowC {Adafruit_NeoPixel::Color(127, 0, 255)};
        const uint32_t greenC {Adafruit_NeoPixel::Color(255, 0, 0)};
        const uint32_t redC {Adafruit_NeoPixel::Color(0, 0, 255)};


    public:
        StatusDiodeController();

        String currentMode;

        void setBrightness(uint8_t brightness);

        void init();

        void yellow();

        void green();

        void red();

        void lightUpAll(uint32_t color);
    };
