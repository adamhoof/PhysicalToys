#include <Arduino.h>
#include "MQTTClientHandler.h"
#include "WifiController.h"
#include "OTAHandler.h"
#include "OfficeLampController.h"
#include "TimeKeeper.h"

MQTTClientHandler mqttClientHandler {};
WifiController wifiController {};
OTAHandler otaHandler {};
TimeKeeper timeKeeper{};

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
    if (!timeKeeper.unitsOfTimePassed(240, MINUTES)){
        wifiController.maintainConnection();
        otaHandler.maintainConnection();
        mqttClientHandler.maintainConnection();
        return;
    }
    ESP.restart();
}
