#pragma once

#include <MQTT.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <pgmspace.h>

class MQTTClientHandler
{
private:
    const char* BedroomShadesPub {"reply/bedroomshades"};
    const char* BedroomShadesSub {"set/bedroomshades"};
    const char* clientID {"bedroom_shades_controller"};
public:
    MQTTClientHandler();

    MQTTClient client {};

    bool isFirstMessageAfterBoot{true};

    void start(WiFiClientSecure* wifiClientSecure);

    void connect();

    void setSubscriptions();

    void publish(const String& payload);

    void reconnect();

    void maintainConnection();

    void disconnect();
};
