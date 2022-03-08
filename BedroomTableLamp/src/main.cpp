#include <Arduino.h>
#include "MQTTClientHandler.h"
#include "WifiController.h"
#include "OTAHandler.h"
#include "LampController.h"
#include "TimeKeeper.h"

MQTTClientHandler mqttClientHandler {};
WifiController wifiController {};
OTAHandler otaHandler {};
TimeKeeper timeKeeper{};
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
    btStop();

    lampController.init();
    lampController.setBrightness(150);

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
    if (!timeKeeper.unitsOfTimePassed(180, MINUTES)) {
        wifiController.maintainConnection();
        otaHandler.maintainConnection();
        mqttClientHandler.maintainConnection();
        return;
    }
    ESP.restart();
}
