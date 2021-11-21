#include <Arduino.h>
#include "MQTTClientHandler.h"
#include "WifiConnector.h"
#include "OTAHandler.h"
#include "OfficeCeilLightController.h"

MQTTClientHandler mqttClientHandler {};
WifiConnector wifiConnector {};
OTAHandler otaHandler {};

PhysicalToyController::OfficeCeilLightController officeCeilLightController {};

void messageHandler(String& topic, String& payload)
{
    String mode = officeCeilLightController.changeMode(payload);
    mqttClientHandler.publish(mode);
}

void setup()
{
    btStop();

    officeCeilLightController.setup();

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
