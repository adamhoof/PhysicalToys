#include <Arduino.h>
#include <MQTTClientHandler.h>
#include <WifiConnector.h>
#include <OTAHandler.h>
#include "ShadesController.h"
#include "StepperMotorController.h"

MQTTClientHandler mqttClientHandler {};
WifiConnector wifiConnector {};
OTAHandler otaHandler {};

PhysicalToyController::ShadesController shadesController{};
StepperMotorController stepperMotorController {};

void messageHandler(String& topic, String& payload)
{
    stepperMotorController.posToMoveTo(payload);
}

void setup()
{
    btStop();

    pinMode(32, INPUT_PULLUP);

    stepperMotorController.setupPins(18, 19, 21, 22);

    stepperMotorController.calibrate();

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
    if (POS_EQUAL) {
        otaHandler.maintainConnection();
        mqttClientHandler.maintainConnection();
        return;
    }

    stepperMotorController.getRequiredPos() > stepperMotorController.getPos() ? shadesController.open(mqttClientHandler, stepperMotorController)
                                                                              : shadesController.close(mqttClientHandler, stepperMotorController);

    mqttClientHandler.publish(String(stepperMotorController.getPos()));
}
