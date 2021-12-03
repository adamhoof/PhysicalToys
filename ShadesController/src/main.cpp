#include <Arduino.h>
#include <MQTTClientHandler.h>
#include <WifiConnector.h>
#include <OTAHandler.h>
#include "StepperMotorController.h"

MQTTClientHandler mqttClientHandler {};
WifiConnector wifiConnector {};
OTAHandler otaHandler {};

PhysicalToyController::StepperMotorController stepperMotorController {};

void setup()
{
    btStop();

    pinMode(39, INPUT_PULLUP);

    stepperMotorController.stepperMotor.setupPins(18, 19, 21, 22);

    Serial.begin(115200);

    wifiConnector.activateDisconnectHandler();
    wifiConnector.connect();


        for (int i = 0; i < 500; ++i) {
            stepperMotorController.moveMotor(CLOCKWISE);
        }
        for (int i = 0; i < 500; ++i) {
            stepperMotorController.moveMotor(ANTI_CLOCKWISE);
        }

    otaHandler.setEvents();
    otaHandler.init();
}

void loop()
{
    otaHandler.maintainConnection();
}
