#include "OfficeCeilLight.h"

Toy::OfficeCeilLight::OfficeCeilLight() = default;

void Toy::OfficeCeilLight::on()
{
    digitalWrite(togglePin, LOW);
}

void Toy::OfficeCeilLight::off()
{
    digitalWrite(togglePin, HIGH);
}
