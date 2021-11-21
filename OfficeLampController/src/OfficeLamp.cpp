#include "OfficeLamp.h"


PhysicalToy::OfficeLamp::OfficeLamp() = default;

void PhysicalToy::OfficeLamp::onWhite()
{
    irCodeSender.onWhite();
}

void PhysicalToy::OfficeLamp::onYellow()
{
    irCodeSender.onYellow();
}

void PhysicalToy::OfficeLamp::onBlue()
{
    irCodeSender.onBlue();
}

void PhysicalToy::OfficeLamp::onGreen()
{
    irCodeSender.onGreen();
}

void PhysicalToy::OfficeLamp::onRed()
{
    irCodeSender.onRed();
}

void PhysicalToy::OfficeLamp::onPink()
{
    irCodeSender.onPink();
}

void PhysicalToy::OfficeLamp::off()
{
    irCodeSender.off();
}
