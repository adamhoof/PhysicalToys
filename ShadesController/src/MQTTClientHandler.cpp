#include "MQTTClientHandler.h"

MQTTClientHandler::MQTTClientHandler() = default;

void MQTTClientHandler::setTimeForCertValidation()
{
    time_t now;
    configTime(-5 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    now = time(nullptr);
    while (now < 1510592825) {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
}

void MQTTClientHandler::setCertificates()
{
    setTimeForCertValidation();

    wifiClientSecure.setCACert(CA_CERT);
    wifiClientSecure.setCertificate(CLIENT_CERT);
    wifiClientSecure.setPrivateKey(CLIENT_KEY);
}

void MQTTClientHandler::start()
{
    client.begin("proteccmqtt.medunka.cz", 8883, wifiClientSecure);
}

void MQTTClientHandler::connect()
{
    Serial.println("Connecting to server");

    while (!client.connect(clientID)) {}

    Serial.println("Server connection established");
}

void MQTTClientHandler::setSubscriptions()
{
    client.subscribe(BedroomShadesSub, 0);
}

void MQTTClientHandler::publish(
        const String& mode)
{
    client.publish(BedroomShadesPub, mode, false, 0);
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
