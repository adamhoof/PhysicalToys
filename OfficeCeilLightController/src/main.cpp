#include <Arduino.h>
#include "MQTTClientHandler.h"
#include "WifiController.h"
#include "OTAHandler.h"
#include "OfficeCeilLightController.h"

MQTTClientHandler mqttClientHandler {};
WifiController wifiController {};
PhysicalToyController::OfficeCeilLightController officeCeilLightController {};

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
    if (payload == *officeCeilLightController.currentModePtr){
        return;
    }
    String mode = officeCeilLightController.changeMode(payload);
    mqttClientHandler.publish(mode);
}

void setup()
{
    btStop();

    officeCeilLightController.setTogglePin(18);
    officeCeilLightController.init();

    wifiController.connect();

    wifiController.setCertificates();
    mqttClientHandler.start(wifiController.wiFiClientSecure());
    mqttClientHandler.client.onMessage(messageHandler);
    mqttClientHandler.connect();
    mqttClientHandler.setSubscriptions();

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
