#include <Arduino.h>
#include <MQTTClientHandler.h>
#include <WifiConnector.h>
#include <OTAHandler.h>
#include "ShadesController.h"
#include "StepperMotorController.h"

MQTTClientHandler mqttClientHandler {};
WifiConnector wifiConnector {};
OTAHandler otaHandler {};

StepperMotorController stepperMotorController {};
PhysicalToyController::ShadesController shadesController {};

void messageHandler(String& topic, String& payload)
{
    stepperMotorController.setReqPosFromString(payload);
}

void setup()
{
    btStop();

    pinMode(32, INPUT_PULLUP);

    stepperMotorController.setupPins(18, 19, 21, 22);
    stepperMotorController.setDelayBetweenSteps(3);

    shadesController.close(stepperMotorController);

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

    if (POSITIONS_EQUAL) {
        otaHandler.maintainConnection();
        mqttClientHandler.maintainConnection();
        return;
    }

    mqttClientHandler.publish("Set: " + String(stepperMotorController.getReqPos()));
    delay(20);
    mqttClientHandler.disconnect();
    delay(20);
    wifiConnector.disconnect();

    REQ_POS_GREATER ? shadesController.open(stepperMotorController)
                    : shadesController.close(stepperMotorController);

    wifiConnector.connect();
    mqttClientHandler.reconnect();

    mqttClientHandler.publish("Done");
}
