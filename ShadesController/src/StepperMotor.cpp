
#include "StepperMotor.h"

StepperMotor::StepperMotor() = default;

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
