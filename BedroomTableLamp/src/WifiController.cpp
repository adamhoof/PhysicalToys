#include "WifiController.h"

WifiController::WifiController() = default;

void WifiController::connect()
{
    WiFiClass::mode(WIFI_STA);

    String wifiHostname = "BedroomTableLamp";
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(wifiHostname.c_str());

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
