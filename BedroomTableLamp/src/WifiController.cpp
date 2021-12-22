#include "WifiController.h"

WifiController::WifiController() = default;

void WifiController::connect()
{
    if (!WiFi.config(staticIP, gateway, subnet, dns, dns)) {
        Serial.println("Wifi config failed :(");
    }

    WiFiClass::mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("Connecting to Wi-Fi");

    WiFi.waitForConnectResult();

    Serial.println("Wifi connected");
    Serial.println(WiFi.localIP());
}

void WifiController::disconnect()
{
    WiFi.disconnect();
}
