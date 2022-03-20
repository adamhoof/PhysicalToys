#include "IRCodeSender.h"

IRCodeSender::IRCodeSender() = default;

void IRCodeSender::setup()
{
    irSend.begin();
}

void IRCodeSender::send(uint32_t rawDataToSend)
{
    irSend.sendNEC(rawDataToSend);
}
