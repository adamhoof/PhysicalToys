#include <Arduino.h>
#include <MQTTClientHandler.h>
#include <WifiClientHandler.h>
#include <OTAHandler.h>
#include "ShadesController.h"
#include "StepperMotorController.h"

MQTTClientHandler mqttClientHandler {};
WifiClientHandler wifiClientHandler {};
OTAHandler otaHandler {};

StepperMotorController stepperMotorController {};
PhysicalToyController::ShadesController shadesController {};

void messageHandler(String& topic, String& payload)
{
    if (mqttClientHandler.isFirstMessageAfterBoot) {

        for (int i = 0; i < 150; ++i) {
            stepperMotorController.stepperMotor.clockwiseStep();
        }

        bool switchNotPresent = digitalRead(32);

        for (int i = 0; i < 150; ++i) {
            stepperMotorController.stepperMotor.antiClockwiseStep();
        }

        uint8_t posToSet;
        switchNotPresent ? posToSet = OPEN : posToSet = CLOSE;

        stepperMotorController.setCurrPos(posToSet);
        stepperMotorController.setReqPos(posToSet);

        mqttClientHandler.isFirstMessageAfterBoot = false;
        return;
    }
    stepperMotorController.setReqPosFromString(payload);
}

void setup()
{
    btStop();

    pinMode(32, INPUT_PULLUP);

    stepperMotorController.setupPins(18, 19, 21, 22);
    stepperMotorController.setDelayBetweenSteps(3);

    wifiClientHandler.connect();

    otaHandler.setEvents();
    otaHandler.init();

    mqttClientHandler.setCertificates();
    mqttClientHandler.start();
    mqttClientHandler.client.onMessage(messageHandler);
    mqttClientHandler.connect();
    mqttClientHandler.setSubscriptions();
}

void loop()
{
    wifiClientHandler.maintainConnection();

    if (POSITIONS_EQUAL) {
        otaHandler.maintainConnection();
        mqttClientHandler.maintainConnection();
        delay(12); //the guy here talking bout keepalive: https://esp32.com/viewtopic.php?t=3851
        return;
    }

    String status {};
    stepperMotorController.getReqPos() == OPEN ? status = "opening" : status = "closing";

    mqttClientHandler.publish(status);
    delay(20);
    mqttClientHandler.disconnect();
    delay(20);
    wifiClientHandler.disconnect();

    REQ_POS_GREATER_THAN_CURR ? shadesController.open(stepperMotorController)
                              : shadesController.close(stepperMotorController);

    wifiClientHandler.connect();
    mqttClientHandler.reconnect();

    status == "opening" ? status = "open" : status = "close";
    mqttClientHandler.publish(status);
}
