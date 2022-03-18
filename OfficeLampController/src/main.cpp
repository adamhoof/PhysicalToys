#include <Arduino.h>
#include "OfficeLampController.h"
#include "certs.h"
#include <WifiController.h>
#include <MQTTClientHandler.h>
#include <OTAHandler.h>

MQTTClientHandler mqttClientHandler {};
WifiController wifiController {};

ApplianceController::OfficeLampController officeLampController {};

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

void messageHandler(char* topic, byte* payload, unsigned int length)
{
    Serial.write(payload, length);
}

void setup()
{
    btStop();

    officeLampController.init();

    Serial.begin(115200);

    char host[] = "office_lamp";
    char pub[] = "reply/officelamp";
    char sub[] = "set/officelamp";

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
    wifiController.maintainConnection();
    mqttClientHandler.maintainConnection();
    delay(10);
}
