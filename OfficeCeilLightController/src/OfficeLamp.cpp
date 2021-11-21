#include "OfficeLamp.h"

Toy::OfficeLamp::OfficeLamp() = default;

void Toy::OfficeLamp::on()
{
    digitalWrite(togglePin, LOW);
}

void Toy::OfficeLamp::off()
{
    digitalWrite(togglePin, HIGH);
}
