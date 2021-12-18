#pragma once

#include <Arduino.h>

class StepperMotor
{
public:
    uint8_t delayBetweenSteps = 3;
    uint8_t pin1{};
    uint8_t pin2{};
    uint8_t pin3{};
    uint8_t pin4{};
public:
    StepperMotor();

    void clockwiseStep();

    void antiClockwiseStep();

    void pin1QuarterStep();

    void pin2QuarterStep();

    void pin3QuarterStep();

    void pin4QuarterStep();
};
