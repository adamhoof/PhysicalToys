#include <Arduino.h>
#include "LampController.h"
#include "credentials.h"
#include <WifiController.h>
#include <MQTTClientHandler.h>
#include <OTAHandler.h>

MQTTClientHandler mqttClientHandler {};
WifiController wifiController {};

ApplianceController::LampController lampController {32, 8};

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
bool receivedModeChangeRequest = false;

void messageHandler(char* topic, const byte* payload, unsigned int length)
{
    for (int i = 0; i < length; i++) {
        payloadToSend[i] = char(payload[i]);
    }
    payloadToSend[length] = '\0';

    receivedModeChangeRequest = true;
}

void setup()
{
    btStop();

    lampController.init();
    lampController.setBrightness(115);

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

    if (receivedModeChangeRequest){
        lampController.changeMode(payloadToSend);
        mqttClientHandler.publish(payloadToSend);
        receivedModeChangeRequest = false;
    }
}
