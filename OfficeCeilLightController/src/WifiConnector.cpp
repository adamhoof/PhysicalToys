#include "WifiConnector.h"

WifiConnector::WifiConnector() = default;

void WifiConnector::connect()
{
    if (!WiFi.config(staticIP, gateway, subnet, dns, dns)) {
        Serial.println("Wifi config failed :(");
    }

    WiFiClass::mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    WiFi.waitForConnectResult();
}

void WifiConnector::disconnect()
{
    WiFi.disconnect();
}

