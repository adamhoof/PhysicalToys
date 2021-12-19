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
    if (payload == *officeCeilLightController.currentModePtr){
        return;
    }
    String mode = officeCeilLightController.changeMode(payload);
    mqttClientHandler.publish(mode);
}

void setup()
{
    btStop();

    officeCeilLightController.setTogglePin(18);
    officeCeilLightController.init();

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
    if (!WiFi.isConnected()) {
        wifiConnector.disconnect();
        wifiConnector.connect();
    }
    otaHandler.maintainConnection();
    mqttClientHandler.maintainConnection();
}
