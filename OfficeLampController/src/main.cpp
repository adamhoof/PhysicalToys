#include <Arduino.h>
#include "OfficeLampController.h"
#include "certs.h"
#include "../.pio/libdeps/pico32/OTAHandler/include/OTAHandler.h"
#include "../.pio/libdeps/pico32/WifiController/include/WifiController.h"
#include "../.pio/libdeps/pico32/MQTTClientHandler/include/MQTTClientHandler.h"

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
    if (payload == *officeLampController.currentModePtr) {
        return;
    }
    String mode = officeLampController.changeMode(payload);
    mqttClientHandler.publish(mode);
}

void setup()
{
    btStop();

    officeLampController.init();

    Serial.begin(115200);

    char id [] = "office_lamp";
    String pubTopic  = "reply/officelamp";
    String subTopic  = "set/officelamp";

    wifiController.connect(id);

    wifiController.setCertificates(CA_CERT, CLIENT_CERT, CLIENT_KEY);
    mqttClientHandler.start(wifiController.wiFiClientSecure());
    mqttClientHandler.setPublishTopic(pubTopic);
    mqttClientHandler.client.onMessage(messageHandler);
    mqttClientHandler.connect(id);
    mqttClientHandler.setSubscribeTopic(subTopic);

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
