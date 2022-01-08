#include "WifiConnector.h"

WifiConnector::WifiConnector() = default;

void WifiConnector::connect()
{
    WiFiClass::mode(WIFI_STA);

    String wifiHostname = "OfficeCeilLight";
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(wifiHostname.c_str());

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    WiFi.waitForConnectResult();
}

void WifiConnector::disconnect()
{
    WiFi.disconnect();
}

