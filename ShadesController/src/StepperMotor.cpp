
#include "StepperMotor.h"

StepperMotor::StepperMotor() = default;

void StepperMotor::setupPins(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4)
{
    pin1 = in1;
    pin2 = in2;
    pin3 = in3;
    pin4 = in4;

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);
}

void StepperMotor::pin1QuarterStep()
{
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
}

void StepperMotor::pin2QuarterStep()
{
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
}

void StepperMotor::pin3QuarterStep()
{
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, LOW);
}

void StepperMotor::pin4QuarterStep()
{
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, HIGH);
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
