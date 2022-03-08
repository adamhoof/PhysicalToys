#include <Arduino.h>
#include <MQTTClientHandler.h>
#include <WifiController.h>
#include <OTAHandler.h>
#include "ShadesController.h"
#include "StepperMotorController.h"

MQTTClientHandler mqttClientHandler {};
WifiController wifiController {};

StepperMotorController stepperMotorController {};
PhysicalToyController::ShadesController shadesController {};

void maintainOTAConnection(void* params)
{
    OTAHandler otaHandler {};
    otaHandler.setEvents();
    otaHandler.init();

    for (;;) {
        otaHandler.maintainConnection();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void maintainServicesConnection(void* params)
{
    for (;;) {
        wifiController.maintainConnection();
        mqttClientHandler.maintainConnection();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void messageHandler(String& topic, String& payload)
{
    if (mqttClientHandler.isFirstMessageAfterBoot) {

        for (int i = 0; i < 250; ++i) {
            stepperMotorController.stepperMotor.clockwiseStep();
            if (!digitalRead(32)) {
                break;
            }
        }

        bool switchNotPresent = digitalRead(32);

        for (int i = 0; i < 250; ++i) {
            stepperMotorController.stepperMotor.antiClockwiseStep();
        }

        uint8_t posToSet;
        switchNotPresent ? posToSet = OPEN : posToSet = CLOSE;

        mqttClientHandler.publish(String(posToSet) + " " + String(mqttClientHandler.isFirstMessageAfterBoot));

        stepperMotorController.setCurrPos(posToSet);
        stepperMotorController.setReqPos(posToSet);

        mqttClientHandler.isFirstMessageAfterBoot = false;
        return;
    }
    stepperMotorController.setReqPosFromString(payload);
}

void setup()
{
    Serial.begin(115200);

    btStop();

    pinMode(32, INPUT_PULLUP);

    stepperMotorController.setupPins(18, 19, 21, 22);
    stepperMotorController.setDelayBetweenSteps(3);

    wifiController.connect();

    Serial.println("Connected to wifi");

    Serial.println("Ota initiated");

    Serial.println("Setting certs");
    wifiController.setCertificates();
    Serial.println("Certificates ok");
    mqttClientHandler.start(wifiController.wiFiClientSecure());
    Serial.println("Client started");
    mqttClientHandler.client.onMessage(messageHandler);
    mqttClientHandler.connect();
    mqttClientHandler.setSubscriptions();

    Serial.println("MQTT client connected");

    xTaskCreatePinnedToCore(
            maintainServicesConnection,
            "KeepServicesAlive",
            3500,
            nullptr,
            1,
            nullptr,
            CONFIG_ARDUINO_RUNNING_CORE
    );

    xTaskCreatePinnedToCore(
            maintainOTAConnection,
            "KeepOTAAlive",
            3500,
            nullptr,
            2,
            nullptr,
            CONFIG_ARDUINO_RUNNING_CORE
    );
}

void loop()
{
    if (POSITIONS_EQUAL) {
        delay(10);
        return;
    }

    String status {};
    stepperMotorController.getReqPos() == OPEN ? status = "opening" : status = "closing";

    mqttClientHandler.publish(status);

    REQ_POS_GREATER_THAN_CURR ? shadesController.open(stepperMotorController)
                              : shadesController.close(stepperMotorController);

    status == "opening" ? status = "open" : status = "close";
    mqttClientHandler.publish(status);
}
