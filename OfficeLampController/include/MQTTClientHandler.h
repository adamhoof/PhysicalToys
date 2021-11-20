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
    const char* officeLampPub {"officelamp/espReply"};
    const char* officeLampSub {"officelamp/rpiSet"};
    const char* clientID {"Office_lamp_controller"};
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
