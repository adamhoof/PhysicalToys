
#include "StepperMotor.h"

StepperMotor::StepperMotor() = default;

void StepperMotor::setupPins(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4)
{
    pins[IN1] = in1;
    pins[IN2] = in2;
    pins[IN3] = in3;
    pins[IN4] = in4;

    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
}

void StepperMotor::pin1QuarterStep()
{
    digitalWrite(pins[IN1], HIGH);
    digitalWrite(pins[IN2], LOW);
    digitalWrite(pins[IN3], LOW);
    digitalWrite(pins[IN4], LOW);
}

void StepperMotor::pin2QuarterStep()
{
    digitalWrite(pins[IN1], LOW);
    digitalWrite(pins[IN2], HIGH);
    digitalWrite(pins[IN3], LOW);
    digitalWrite(pins[IN4], LOW);
}

void StepperMotor::pin3QuarterStep()
{
    digitalWrite(pins[IN1], LOW);
    digitalWrite(pins[IN2], LOW);
    digitalWrite(pins[IN3], HIGH);
    digitalWrite(pins[IN4], LOW);
}

void StepperMotor::pin4QuarterStep()
{
    digitalWrite(pins[IN1], LOW);
    digitalWrite(pins[IN2], LOW);
    digitalWrite(pins[IN3], LOW);
    digitalWrite(pins[IN4], HIGH);
}

void StepperMotor::clockwiseStep()
{
    pin1QuarterStep();
    delay(motorDelay);
    pin2QuarterStep();
    delay(motorDelay);
    pin3QuarterStep();
    delay(motorDelay);
    pin4QuarterStep();
    delay(motorDelay);
}

void StepperMotor::antiClockwiseStep()
{
    pin4QuarterStep();
    delay(motorDelay);
    pin3QuarterStep();
    delay(motorDelay);
    pin2QuarterStep();
    delay(motorDelay);
    pin1QuarterStep();
    delay(motorDelay);
}
