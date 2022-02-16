#include <Arduino.h>
#include "MQTTClientHandler.h"
#include "WifiController.h"
#include "OTAHandler.h"
#include "OfficeCeilLightController.h"
#include "TimeKeeper.h"

MQTTClientHandler mqttClientHandler {};
WifiController wifiController {};
OTAHandler otaHandler {};
TimeKeeper timeKeeper{};

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
