#include "OfficeCeilLight.h"

PhysicalToy::OfficeCeilLight::OfficeCeilLight() = default;

void PhysicalToy::OfficeCeilLight::on()
{
    digitalWrite(togglePin, LOW);
}

void PhysicalToy::OfficeCeilLight::off()
{
    digitalWrite(togglePin, HIGH);
}
