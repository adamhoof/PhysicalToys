#include "WifiClientHandler.h"

WifiClientHandler::WifiClientHandler() = default;

void WifiClientHandler::connect()
{
    WiFiClass::mode(WIFI_STA);

    String wifiHostname = "BedroomShades";
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(wifiHostname.c_str());

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    WiFi.waitForConnectResult();
}

void WifiClientHandler::maintainConnection()
{
    if (!WiFi.isConnected()) {
        ESP.restart();
    }
}

void WifiClientHandler::disconnect()
{
    WiFi.disconnect();
}
