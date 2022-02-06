#include <Arduino.h>
#include "MQTTClientHandler.h"
#include "WifiClientHandler.h"
#include "OTAHandler.h"
#include "OfficeLampController.h"

MQTTClientHandler mqttClientHandler {};
WifiClientHandler wifiClientHandler {};
OTAHandler otaHandler {};

ApplianceController::OfficeLampController officeLampController {};

void messageHandler(String& topic, String& payload)
{
    if (payload == *officeLampController.currentModePtr){
        return;
    }
    String mode = officeLampController.changeMode(payload);
    mqttClientHandler.publish(mode);
}

void setup()
{
    btStop();

    officeLampController.init();

    Serial.begin(115200);

    wifiClientHandler.connect();

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
    wifiClientHandler.maintainConnection();
    otaHandler.maintainConnection();
    mqttClientHandler.maintainConnection();
}
