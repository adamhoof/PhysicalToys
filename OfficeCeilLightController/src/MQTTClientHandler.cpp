#include "MQTTClientHandler.h"

MQTTClientHandler::MQTTClientHandler() = default;

void MQTTClientHandler::start(WiFiClientSecure* wifiClientSecure)
{
    client.begin("proteccmqtt.medunka.cz", 8883, *wifiClientSecure);
}

void MQTTClientHandler::connect()
{
    while (!client.connect(clientID)) {delay(100);}
}

void MQTTClientHandler::setSubscriptions()
{
    client.subscribe(officeLampSub, 0);
}

void MQTTClientHandler::publish(
        const String& mode)
{
    client.publish(officeLampPub, mode, true, 0);
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
        delay(10);
    }
}
