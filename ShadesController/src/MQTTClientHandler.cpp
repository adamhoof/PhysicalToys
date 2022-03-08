#include "MQTTClientHandler.h"

MQTTClientHandler::MQTTClientHandler() = default;

void MQTTClientHandler::start(WiFiClientSecure *wifiClientSecure)
{
    client.begin("proteccmqtt.medunka.cz", 8883, *wifiClientSecure);
}

void MQTTClientHandler::connect()
{
    Serial.println("Connecting to server");

    while (!client.connect(clientID)) {delay(100);}

    Serial.println("Server connection established");
}

void MQTTClientHandler::setSubscriptions()
{
    client.subscribe(BedroomShadesSub, 0);
}

void MQTTClientHandler::publish(const String& payload)
{
    client.publish(BedroomShadesPub, payload, true, 0);
}

void MQTTClientHandler::reconnect()
{
    connect();
    setSubscriptions();
}

void MQTTClientHandler::maintainConnection()
{
    if (!client.loop()) { //returns false if client is not connected
        reconnect();
    }
}

void MQTTClientHandler::disconnect()
{
    client.disconnect();
}
