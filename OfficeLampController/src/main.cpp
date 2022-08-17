#include <Arduino.h>
#include "OfficeLampController.h"
#include "credentials.h"
#include <WifiController.h>
#include <PubSubClient.h>
#include <OTAHandler.h>

WifiController wifiController = WifiController();
WiFiClient wifiClient = WiFiClient();

PubSubClient mqttClient = PubSubClient();

OfficeLampController officeLampController {};
IRsend irSend = IRsend(25);

char payloadToSend[10];
bool receivedChangeModeRequest = false;

void KeepOTAAlive(void* params)
{
    OTAHandler::setEvents();
    OTAHandler::init();

    for (;;) {
        OTAHandler::maintainConnection();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

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

    Serial.begin(115200);

    irSend.begin();

    wifiController.setHostname(hostname).setSSID(wifiSSID).setPassword(wifiPassword);
    wifiController.connect();

    xTaskCreatePinnedToCore(
            KeepOTAAlive,
            "KeepOTAAlive",
            3500,
            nullptr,
            2,
            nullptr,
            CONFIG_ARDUINO_RUNNING_CORE
    );

    mqttClient.setServer(server, port);
    mqttClient.setClient(wifiClient);
    mqttClient.connect(hostname);
    mqttClient.subscribe(subscribeTopic);
    mqttClient.setCallback(messageHandler);
}

void loop()
{
    wifiController.maintainConnection();
    if (!mqttClient.loop()) {
        mqttClient.connect(hostname);
    }
    delay(10);

    if (receivedChangeModeRequest) {
        officeLampController.changeMode(&irSend, payloadToSend);
        mqttClient.publish(publishTopic, payloadToSend, true);
        receivedChangeModeRequest = false;
    }
}
