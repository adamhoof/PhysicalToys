#pragma once

#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

class OTAHandler
{
public:
    OTAHandler();

    void setEvents();

    void init();

    void maintainConnection();
};
