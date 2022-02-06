#pragma once

#include <MQTT.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <pgmspace.h>
#include <time.h>
#include "certs.h"

class MQTTClientHandler
{
private:
    const char* BedroomShadesPub {"reply/bedroomshades"};
    const char* BedroomShadesSub {"set/bedroomshades"};
    const char* clientID {"bedroom_shades_controller"};
public:
    MQTTClientHandler();

    MQTTClient client {};

    WiFiClientSecure wifiClientSecure {};

    bool isFirstMessageAfterBoot{true};

    void setTimeForCertValidation();

    void setCertificates();

    void start();

    void connect();

    void setSubscriptions();

    void publish(const String& payload);

    void reconnect();

    void maintainConnection();

    void disconnect();
};
