#include <Arduino.h>
#include <MQTTClientHandler.h>
#include <WifiConnector.h>
#include <OTAHandler.h>
#include "StepperMotorController.h"

MQTTClientHandler mqttClientHandler {};
WifiConnector wifiConnector {};
OTAHandler otaHandler {};

PhysicalToyController::StepperMotorController stepperMotorController {};

void messageHandler(String& topic, String& payload)
{
    Serial.println("payload");
    Serial.println(payload);
    stepperMotorController.posToMoveTo(payload);
}

void setup()
{
    btStop();

    pinMode(32, INPUT_PULLUP);

    stepperMotorController.stepperMotor.setupPins(18, 19, 21, 22);

    Serial.begin(115200);

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

    stepperMotorController.getRequiredPos() > stepperMotorController.getPos() ? stepperMotorController.open()
                                                                              : stepperMotorController.close();

    mqttClientHandler.publish(String(stepperMotorController.getPos()));
}
