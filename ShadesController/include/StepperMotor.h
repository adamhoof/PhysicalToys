#pragma once

#include <Arduino.h>

#define IN1 0
#define IN2 1
#define IN3 2
#define IN4 3

class StepperMotor
{
public:
    const uint8_t motorDelay = 3;
public:
    StepperMotor();

    uint8_t pins [4]{};

    void setupPins(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4);

    void clockwiseStep();

    void antiClockwiseStep();

    void pin1QuarterStep();

    void pin2QuarterStep();

    void pin3QuarterStep();

    void pin4QuarterStep();
};
