#include <Arduino.h>
#include <MQTTClientHandler.h>
#include <WifiConnector.h>
#include <OTAHandler.h>
#include "ShadesController.h"
#include "StepperMotorController.h"

MQTTClientHandler mqttClientHandler {};
WifiConnector wifiConnector {};
OTAHandler otaHandler {};

PhysicalToyController::ShadesController shadesController {};
StepperMotorController stepperMotorController {};

void messageHandler(String& topic, String& payload)
{
    stepperMotorController.setReqPosFromString(payload);
}

void setup()
{
    btStop();

    pinMode(32, INPUT_PULLUP);

    stepperMotorController.setupPins(18, 19, 21, 22);

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
    if (POSITIONS_EQUAL) {
        otaHandler.maintainConnection();
        mqttClientHandler.maintainConnection();
        return;
    }

    REQ_POS_GREATER ? shadesController.open(mqttClientHandler, stepperMotorController)
                    : shadesController.close(mqttClientHandler, stepperMotorController);

    mqttClientHandler.publish("Done");
}
