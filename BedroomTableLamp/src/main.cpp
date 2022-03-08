#include <Arduino.h>
#include "certs.h"
#include "../.pio/libdeps/m5stick-c/OTAHandler/include/OTAHandler.h"
#include "../.pio/libdeps/m5stick-c/WifiController//include/WifiController.h"
#include "../.pio/libdeps/m5stick-c/MQTTClientHandler/include/MQTTClientHandler.h"
#include "LampController.h"

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
    if (payload == *lampController.getCurrentModePtr()) {
        return;
    }
    Serial.println(payload);
    String mode = lampController.changeMode(payload);
    mqttClientHandler.publish(mode);
}

void setup()
{
    btStop();

    lampController.init();
    lampController.setBrightness(150);

    char id [] = "bedroom_lamp";
    String pubTopic  = "reply/bedroomlamp";
    String subTopic  = "set/bedroomlamp";

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
