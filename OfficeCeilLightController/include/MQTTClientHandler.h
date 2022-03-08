#pragma once

#include <MQTT.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <pgmspace.h>

class MQTTClientHandler
{
private:
    const char* officeLampPub {"reply/officeceillight"};
    const char* officeLampSub {"set/officeceillight"};
    const char* clientID {"office_ceil_light_controller"};
public:
    MQTTClientHandler();

    MQTTClient client {};

    void start(WiFiClientSecure* wifiClientSecure);

    void connect();

    void setSubscriptions();

    void publish(const String& payload);

    void reconnect();

    void maintainConnection();
};
