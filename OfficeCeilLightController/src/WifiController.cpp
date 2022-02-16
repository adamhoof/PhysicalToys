#include "WifiController.h"

WifiController::WifiController() = default;

void WifiController::connect()
{
    WiFiClass::mode(WIFI_STA);

    String wifiHostname = "OfficeCeilLight";
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(wifiHostname.c_str());

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    WiFi.waitForConnectResult();
}

void WifiController::disconnect()
{
    WiFi.disconnect();
}

void WifiController::maintainConnection()
{
    if (!WiFi.isConnected()) {
        disconnect();
        connect();
    }
}

