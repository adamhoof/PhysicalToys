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
    const char* officeLampPub {"officeceil/espReply"};
    const char* officeLampSub {"officeceil/rpiSet"};
    const char* clientID {"Office_ceil_light_controller"};
public:
    MQTTClientHandler();

    MQTTClient client {};

    WiFiClientSecure wifiClientSecure {};

    void setTimeForCertValidation();

    void setCertificates();

    void start();

    void connect();

    void setSubscriptions();

    void publish(const String& mode);

    void reconnect();

    void maintainConnection();
};
