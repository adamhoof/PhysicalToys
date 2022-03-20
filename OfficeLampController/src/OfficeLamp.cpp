#include "OfficeLamp.h"


PhysicalToy::OfficeLamp::OfficeLamp() = default;

void PhysicalToy::OfficeLamp::on()
{
    irCodeSender.send(0x00F7C03F);
}

void PhysicalToy::OfficeLamp::off()
{
    irCodeSender.send(0x00F740BF);
}

void PhysicalToy::OfficeLamp::mode(uint32_t mode)
{
    on();
    irCodeSender.send(mode);
}


