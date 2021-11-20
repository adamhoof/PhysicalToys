#include <Arduino.h>
#include "MQTTClientHandler.h"
#include "WifiConnector.h"
#include "OTAHandler.h"
#include "OfficeLampController.h"

MQTTClientHandler mqttClientHandler {};
WifiConnector wifiConnector {};
OTAHandler otaHandler {};

ApplianceController::OfficeLampController officeLampController {};

void messageHandler(String& topic, String& payload)
{
    String mode = officeLampController.changeMode(payload);
    mqttClientHandler.publish(mode);
}

void setup()
{
    officeLampController.setup();

    Serial.begin(115200);

    wifiConnector.activateDisconnectHandler();
    wifiConnector.connect();

    mqttClientHandler.setCertificates();
    mqttClientHandler.start();
    mqttClientHandler.client.onMessage(messageHandler);
    mqttClientHandler.connect();
    mqttClientHandler.setSubscriptions();

    otaHandler.setEvents();
    otaHandler.init();
}

void loop()
{
    otaHandler.maintainConnection();
    mqttClientHandler.maintainConnection();
}
