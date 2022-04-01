#include <Arduino.h>
#include "OfficeLampController.h"
#include "credentials.h"
#include <WifiController.h>
#include <MQTTClientHandler.h>
#include <OTAHandler.h>

MQTTClientHandler mqttClientHandler {};
WifiController wifiController {};

ApplianceController::OfficeLampController officeLampController {};

char payloadToSend[10];
bool shouldPublish = false;

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

void messageHandler(char* topic, const byte* payload, unsigned int length)
{
    for (int i = 0; i < length; i++) {
        payloadToSend[i] = char(payload[i]);
    }
    payloadToSend[length] = '\0';

    officeLampController.changeMode(payloadToSend);
    shouldPublish = true;
}

void setup()
{
    btStop();

    officeLampController.init();

    Serial.begin(115200);

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
            "OTACapability",
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

    if (shouldPublish){
        mqttClientHandler.publish(payloadToSend);
        shouldPublish = false;
    }
}
