#include <Arduino.h>
#include <MQTTClientHandler.h>
#include <WifiController.h>
#include <OTAHandler.h>
#include "ShadesController.h"
#include "StepperMotorController.h"
#include "TimeKeeper.h"

MQTTClientHandler mqttClientHandler {};
WifiController wifiController {};
OTAHandler otaHandler {};
TimeKeeper timeKeeper {};

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

    wifiController.connect();

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
    if (!timeKeeper.unitsOfTimePassed(180, MINUTES)) {

        wifiController.maintainConnection();
        mqttClientHandler.maintainConnection();

        if (POSITIONS_EQUAL) {
            otaHandler.maintainConnection();
            mqttClientHandler.maintainConnection();
            delay(12);
            return;
        }

        String status {};
        stepperMotorController.getReqPos() == OPEN ? status = "opening" : status = "closing";

        mqttClientHandler.publish(status);
        delay(20);
        mqttClientHandler.disconnect();
        delay(20);
        wifiController.disconnect();

        REQ_POS_GREATER_THAN_CURR ? shadesController.open(stepperMotorController)
                                  : shadesController.close(stepperMotorController);

        wifiController.connect();
        mqttClientHandler.reconnect();

        status == "opening" ? status = "open" : status = "close";
        mqttClientHandler.publish(status);
        return;
    }
    ESP.restart();
}
