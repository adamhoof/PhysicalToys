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
    delay(12); //the guy here talking bout keepalive: https://esp32.com/viewtopic.php?t=3851
}
