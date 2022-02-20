#include <Arduino.h>
#include "MQTTClientHandler.h"
#include "WifiController.h"
#include "OTAHandler.h"
#include "OfficeCeilLightController.h"
#include "StatusDiodeController.h"

MQTTClientHandler mqttClientHandler {};
WifiController wifiController {};
OTAHandler otaHandler {};
StatusDiodeController statusDiodeController {};

PhysicalToyController::OfficeCeilLightController officeCeilLightController {};

void messageHandler(String& topic, String& payload)
{
    if (payload == *officeCeilLightController.currentModePtr) {
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

    statusDiodeController.init();
    statusDiodeController.setBrightness(60);
    statusDiodeController.red();

    wifiController.connect();

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
        statusDiodeController.red();
        wifiController.disconnect();
        wifiController.connect();
    } else {statusDiodeController.green();}

    if (!mqttClientHandler.client.connected()) {
        statusDiodeController.yellow();
        mqttClientHandler.reconnect();
    }
    otaHandler.maintainConnection();
}
