#include <Arduino.h>
#include "ShadesController.h"
#include "StepperMotorController.h"
#include <certs.h>
#include <WifiController.h>
#include <MQTTClientHandler.h>
#include <OTAHandler.h>


MQTTClientHandler mqttClientHandler {};
WifiController wifiController {};

StepperMotorController stepperMotorController {};
ToyController::ShadesController shadesController {};

void OTACapability(void* params)
{
    OTAHandler otaHandler {};

    otaHandler.setEvents();
    otaHandler.init();
    delay(10);

    for (;;) {
        otaHandler.maintainConnection();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

char payloadToSend[10];
bool receivedChangeModeRequest = false;

void messageHandler(char* topic, const byte* payload, unsigned int length)
{
    for (int i = 0; i < length; i++) {
        payloadToSend[i] = char(payload[i]);
    }
    payloadToSend[length] = '\0';

    receivedChangeModeRequest = true;
}

void setup()
{
    btStop();

    pinMode(32, INPUT_PULLUP);

    stepperMotorController.setupPins(18, 19, 21, 22);
    stepperMotorController.setDelayBetweenSteps(3);
    shadesController.setMotorController(stepperMotorController);

    wifiController.setHostname(host).setSSID(wifiSSID).setPassword(wifiPassword);
    wifiController.connect();
    wifiController.setCertificates(CA_CERT, CLIENT_CERT, CLIENT_KEY);

    mqttClientHandler.setHostname(host).setServerAndPort(server, port);
    mqttClientHandler.setWiFiClient(wifiController.wiFiClientSecure());
    mqttClientHandler.setSubscribeTopic(sub).setPublishTopic(pub);
    mqttClientHandler.connectAndSubscribe();
    mqttClientHandler.setCallback(messageHandler);

    xTaskCreatePinnedToCore(
            OTACapability,
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
    wifiController.maintainConnection();
    mqttClientHandler.maintainConnection();
    delay(10);

    if (receivedChangeModeRequest) {
        shadesController.changeMode(payloadToSend);
        mqttClientHandler.publish(payloadToSend);
        receivedChangeModeRequest = false;
    }
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
