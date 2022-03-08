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

void IRCodeSender::onWhite()
{
    send(onSignal);
    send(whiteSignal);
}

void IRCodeSender::onYellow()
{
    send(onSignal);
    send(yellowSignal);
}

void IRCodeSender::onGreen()
{
    send(onSignal);
    send(greenSignal);
}

void IRCodeSender::onBlue()
{
    send(onSignal);
    send(blueSignal);
}

void IRCodeSender::onRed()
{
    send(onSignal);
    send(redSignal);
}

void IRCodeSender::onPink()
{
    send(onSignal);
    send(pinkSignal);
}


void IRCodeSender::off()
{
    send(offSignal);
}
