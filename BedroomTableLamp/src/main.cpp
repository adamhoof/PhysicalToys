#include <Arduino.h>
#include "MQTTClientHandler.h"
#include "WifiController.h"
#include "OTAHandler.h"
#include "LampController.h"

MQTTClientHandler mqttClientHandler {};
WifiController wifiConnector {};
OTAHandler otaHandler {};

ApplianceController::LampController lampController {};

void messageHandler(String& topic, String& payload)
{
    if (payload == *lampController.getCurrentModePtr()) {
        return;
    }
    Serial.println(payload);
    String mode = lampController.changeMode(payload);
    mqttClientHandler.publish(mode);
}

void setup()
{
    lampController.init();
    lampController.setBrightness(80);

     btStop();

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
