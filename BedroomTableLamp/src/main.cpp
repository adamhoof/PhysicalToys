#include <Arduino.h>
#include "LampController.h"
#include "certs.h"
#include <WifiController.h>
#include <MQTTClientHandler.h>
#include <OTAHandler.h>

MQTTClientHandler mqttClientHandler {};
WifiController wifiController {};

ApplianceController::LampController lampController {};

void keepOTACapability(void* params)
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
bool shouldPublish = false;

void messageHandler(char* topic, const byte* payload, unsigned int length)
{
    for (int i = 0; i < length; i++) {
        payloadToSend[i] = char(payload[i]);
    }
    payloadToSend[length] = '\0';

    /*lampController.changeMode(payloadToSend);*/
    shouldPublish = true;
}

void setup()
{
    btStop();

    pinMode(25,OUTPUT);

    Serial.begin(115200);

    lampController.init();
    lampController.setBrightness(150);

    wifiController.setHostname(host).setSSID(wifiSSID).setPassword(wifiPassword);
    wifiController.connect();
    wifiController.setCertificates(CA_CERT, CLIENT_CERT, CLIENT_KEY);

    mqttClientHandler.setHostname(host).setServerAndPort(server, port);
    mqttClientHandler.setWiFiClient(wifiController.wiFiClientSecure());
    mqttClientHandler.setSubscribeTopic(sub).setPublishTopic(pub);
    mqttClientHandler.connectAndSubscribe();
    mqttClientHandler.setCallback(messageHandler);

    xTaskCreatePinnedToCore(
            keepOTACapability,
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
    delay(10);
}
